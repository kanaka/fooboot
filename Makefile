# User settings

# Default to any *.bin targets
FOO_TARGETS ?= $(patsubst run-%,%,$(filter %.bin,$(MAKECMDGOALS)))
$(warning FOO_TARGETS: $(FOO_TARGETS))

FOO_CMDLINE ?=

# Files to include in
# Syntax "name1:path1 name2:path2 ..."
MEM_FS_FILES ?= $(shell grep -v '^\#' mem_fs_files 2>/dev/null|| true)

# 64 bits is not supported yet
ABI_BITS = 32

###

SHELL := bash

FOOBOOT_MK := $(abspath $(lastword $(MAKEFILE_LIST)))
FOOBOOT_TOP := $(dir $(shell readlink -f $(FOOBOOT_MK)))
VPATH = $(FOOBOOT_TOP):

AS = nasm
FOOBOOT_ASFLAGS = $(if $(filter 32,$(ABI_BITS)),-f elf,-f elf64)

FOO_AS = $(AS) $(FOOBOOT_ASFLAGS) $(ASFLAGS)
FOO_CC = $(CC) $(FOOBOOT_CFLAGS) $(CFLAGS)
FOO_LD = $(LD) $(FOOBOOT_LDFLAGS) $(LDFLAGS)

BASE_DEPS = libkernel.a libc.a libutil.a

CFLAGS += $(if $(filter 32,$(ABI_BITS)),-m32)
FOOBOOT_CFLAGS = -nostdlib -nostdinc -I$(FOOBOOT_TOP) \
		 -isystem $(FOOBOOT_TOP)/include \
		 -isystem $(FOOBOOT_TOP)/kernel \
		 -isystem $(FOOBOOT_TOP)/lib \
		 -isystem $(FOOBOOT_TOP)/util \
		 -include $(FOOBOOT_TOP)/include/stddef.h \
		 -fno-builtin -fno-stack-protector

LDFLAGS += $(if $(filter 32,$(ABI_BITS)),-melf_i386)
FOOBOOT_LDFLAGS = -T $(FOOBOOT_TOP)/kernel/link.ld \
		  --no-as-needed

KOBJECTS = kernel/gdt.o kernel/io.o kernel/memory.o kernel/serial.o \
	   kernel/kbd.o kernel/fb.o kernel/hwclock.o \
	   kernel/boot.o kernel/entry.o

LIBC_OBJECTS = lib/string.o lib/mini-printf.o lib/console.o \
	       lib/stdlib.o lib/stdio.o lib/math.o lib/ctype.o \
	       lib/atof.o lib/strtol.o lib/strtoul.o lib/strtoull.o

UTIL_OBJECTS = util/vfs.o util/sym_table.o util/readline_buf.o \
	       util/time.o

###

$(shell mkdir -p kernel lib util)

.PHONY: foo
foo: $(FOO_TARGETS)

libkernel.a: $(KOBJECTS)
	$(AR) rcs $@ $^

libc.a: $(LIBC_OBJECTS)
	$(AR) rcs $@ $^

libutil.a: $(UTIL_OBJECTS)
	$(AR) rcs $@ $^

%: %.c  # cancel implicit rule

%.o: %.c
	$(FOO_CC) -c $(filter %.c,$^) -o $@

%.o: %.s
	$(FOO_AS) $(filter %.s,$^) -o $@

clean::
	rm -f *.d *.o *.a *.bin *.iso $(FOO_TARGETS)
	rm -f examples/*.d examples/*.o examples/*.iso
	rm -f kernel/*.d kernel/*.o lib/*.d lib/*.o util/*.d util/*.o
	rm -f *.syms.c *.mem_fs_files.s
	rm -f examples/*.syms.c examples/*.mem_fs_files.s
	rmdir kernel lib util 2>/dev/null || true
	rm -f isodir/boot/grub/grub.cfg
	rmdir isodir/boot/grub 2>/dev/null || true
	rm -f isodir/boot/*
	rmdir -p isodir/boot 2>/dev/null || true

################################################################################
# embedded file-system

# Build three times:
#   1. empty symbol table to get symbols names
#   2. symbol table with symbol names to get final address layout
#   3. symbol table with symbol names and final symbol addresses
define make-bin-target
$1: $$(BASE_DEPS) $1.mem_fs_files.o $1.o
	cat /dev/null > $$@
	for i in 1 2 3; do \
	  $$(FOOBOOT_TOP)/gen_syms.sh $$@ > $1.syms.c; \
	  $$(FOO_CC) -c $1.syms.c -o $1.syms.o; \
	  $$(FOO_LD) --start-group $1.syms.o $$^ --end-group -o $$@; \
	done
endef
$(foreach b,$(FOO_TARGETS),$(eval $(call make-bin-target,$(b))))


################################################################################
# embedded file-system

MEM_FS_PATHS = $(foreach f,$(MEM_FS_FILES),$(word 1,$(subst :, ,$(f))))

define make-fs-target
$1.mem_fs_files.s: $$(MEM_FS_PATHS)
	$$(FOOBOOT_TOP)/gen_files.sh $$(MEM_FS_FILES) > $$@
endef
$(foreach b,$(FOO_TARGETS),$(eval $(call make-fs-target,$(b))))

################################################################################
# bootable ISO

_NOT = $(if $1,,true)
$(if $(and $(filter boot.iso,$(MAKECMDGOALS)),$(call _NOT,$(FOO_TARGETS))),\
    $(error boot.iso requires FOO_TARGETS))
boot.iso: grub-base.cfg $(FOO_TARGETS)
	mkdir -p isodir/boot/grub
	cp $< isodir/boot/grub/grub.cfg
	for f in $(wordlist 2,$(words $^),$^); do \
	  n=$$(basename $$f); \
	  grub-file --is-x86-multiboot $$f; \
	  cp $$f isodir/boot/$$n; \
	  echo "menuentry '$$n ${FOO_CMDLINE}' { multiboot /boot/$$n $$n $(FOO_CMDLINE) }" >> isodir/boot/grub/grub.cfg; \
	done
	grub-mkrescue -o $@ isodir

.PHONY:
run-%: %
	fooboot/runfoo $< $(FOO_CMDLINE)

