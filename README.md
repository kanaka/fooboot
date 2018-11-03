# fooboot: boot your foo

A small kernel, C library, Makefile and launch script for building and
booting your program in QEMU or on real hardware.


## Prerequisites

- You will need a C compiler with i386/32-bit output support and the
  nasm assembler. 
- To build a bootable ISO you will also need Grub 2, the Grub PC/BIOS
  binary files (grub-pc-bin) and xorriso.


## Quick Start

1. Checkout the fooboot project
```
git clone https://github.com/kanaka/fooboot
```
2. Create a simple hello.c
```
#include <stdio.h>
int main() {
    printf("hello world\n");
}
```
3. Build a bootable ISO
```
make FOO_TARGETS="hello" boot.iso
```
4. Write the ISO to a USB device. Warning: This will destroy any
   content on the USB device. SECOND WARNING: make sure that
   MY\_USB\_DEVICE is actually your USB device and not some other device
   with critical data on it like your hard drive!!
```
sudo dd if=boot.iso of=/dev/MY_USB_DEVICE && sync
```
5. Boot using the USB device (you may need to go into your BIOS/boot
   loader menu to select your USB device for boot).


## Project with a Makefile

1. Create a project directory and add fooboot to it
```
mkdir myproj
cd myproj
git clone https://github.com/kanaka/fooboot
```
2. Create a project Makefile
```
FOO_TARGETS = myprog  # before the include
include fooboot/Makefile

myprog: mylib1.o mylib2.o myprog.o
```
3. Add project files myprog.c, mylib1.c, mylib2.c
4. Build myprog kernel
```
make
```
5. Boot in QEMU with command line argument using the launch script:
```
fooboot/runfoo myprog myarg1 myarg2
```

## fooboot C library

The C library included with fooboot includes a few basic functions
including: printf, snprintf, memset, memmove, strcmp, strlen, strtol,
etc. There is also a naive malloc function that will simply allocate
memory from the beginning of the heap. However, please note that the
free function is currently non-functional. Your program will need to
provide its own memory management within the memory that it gets using
fooboot's malloc.

## fooboot extras

- **readline**: fooboot provides a simple readline function
  `readline_buf` that reads a line from the console (serial or
  keyboard input) into a pre-existing buffer
  (`fooboot/util/readline_buf`).
- **in-memory file-system**: the fooboot build will look for
  a file named `mem_fs_files` that contains a list of files to include
  in the resulting binary. These files can then be "read" at runtime
  using `vfs_read_file` (`fooboot/util/vfs.c`). The in-memory file
  paths can be modified using a colon followed by in-memory path like
  this: `real_path_to_file:mem_path_to_file`.
- **file-system access via serial port**: when the program is run in
  QEMU using `fooboot/runfoo`, the program can read files via commands
  sent over the COM2 serial port using `vfs_read_file`
  (`fooboot/util/vfs.c`). The in-memory file-system is searched first
  for a path match before the file is attempted to be loaded over the
  serial port.
- **runtime symbol table**: fooboot-based programs are built with
  a simple flat symbol table. Symbols can be looked up by name
  using `sym_table_lookup` (util/sym\_table.c).


## License

fooboot is licensed under the MPL-2.0 (see LICENSE).

Some code in fooboot is included or derived from other open source
projects. 
