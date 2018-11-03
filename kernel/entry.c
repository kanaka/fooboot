#include <multiboot.h>
#include <gdt.h>
#include <io.h>
#include <serial.h>
#include <kbd.h>
#include <fb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hwclock.h>

extern uint8_t *heap_start;
extern uint8_t *heap_end;

char *argv[100];

int main();

#include <console.h>
int __entry(struct multiboot_header *mboot_hdr,
            struct multiboot_info *mboot_info) {
    // Init segmentation GDT
    init_descriptor_tables();

    serial_init(SERIAL_COM1, 1); // 115200 baud
    serial_init(SERIAL_COM2, 1); // 115200 baud
    kbd_init();

    // Clear the frame buffer text console
    fb_clear();

    /*
    printf("mboot_hdr: %p\n", mboot_hdr);
    printf("mboot_hdr->flags: 0x%x\n", mboot_hdr->flags);
    printf("mboot_hdr->header_addr: %p\n", mboot_hdr->header_addr);
    printf("mboot_hdr->load_addr (code): 0x%x\n", mboot_hdr->load_addr);
    printf("mboot_hdr->load_end_addr (bss): 0x%x\n", mboot_hdr->load_end_addr);
    printf("mboot_hdr->bss_end_addr: 0x%x\n", mboot_hdr->bss_end_addr);
    printf("mboot_hdr->entry_addr: 0x%x\n", mboot_hdr->entry_addr);

    printf("mboot_info: %p\n", mboot_info);
    printf("mboot_info->flags: 0x%x\n", mboot_info->flags);
    printf("mboot_info->mem_lower: 0x%x\n", mboot_info->mem_lower);
    printf("mboot_info->mem_upper: 0x%x\n", mboot_info->mem_upper);
    printf("mboot_info->cmdline: 0x%x\n", mboot_info->cmdline);
    printf("cmdline text: '%s'\n", mboot_info->cmdline);
    printf("mboot_info->mods_count: 0x%x\n", mboot_info->mods_count);
    printf("mboot_info->mods_addr: 0x%x\n", mboot_info->mods_addr);
    printf("mboot_info->u.elf_sec.num: 0x%x\n", mboot_info->u.elf_sec.num);
    printf("mboot_info->u.elf_sec.size: 0x%x\n", mboot_info->u.elf_sec.size);
    printf("mboot_info->u.elf_sec.addr: 0x%x\n", mboot_info->u.elf_sec.addr);
    printf("mboot_info->u.elf_sec.shndx: 0x%x\n", mboot_info->u.elf_sec.shndx);
    printf("mboot_info->mmap_length: 0x%x\n", mboot_info->mmap_length);
    printf("mboot_info->mmap_addr: 0x%x\n", mboot_info->mmap_addr);
    multiboot_memory_map_t *mmaps = (void *)mboot_info->mmap_addr;
    for (uint32_t i = 0; i < mboot_info->mmap_length/sizeof(multiboot_memory_map_t); i++) {
        multiboot_memory_map_t *mmap = mmaps+i;
        printf("  mmap->addr: 0x%x\n", mmap->addr);
        printf("  mmap->len: 0x%x\n", mmap->len);
        printf("  mmap->type: 0x%x\n", mmap->type);
    }
    printf("mboot_info->boot_loader_name: 0x%x\n", mboot_info->boot_loader_name);
    printf("mboot_info->boot_loader_name: '%s'\n", mboot_info->boot_loader_name);
    */

    /*
    struct tm tim;
    read_hardware_clock_isa(&tim);
    printf("tim->tm_sec: %d\n", tim.tm_sec);
    printf("tim->tm_min: %d\n", tim.tm_min);
    printf("tim->tm_hour: %d\n", tim.tm_hour);
    */

    // set heap to next nearest 4096 boundary after BSS
    heap_start = (void *)mboot_hdr->bss_end_addr +
        0x1000 - (mboot_hdr->bss_end_addr%0x1000);
    heap_end = heap_start;

    /*
    printf("heap_start: %p\n", heap_start);
    printf("heap_end: %p\n", heap_end);
    */

    // Setup the command line arguments
    int argc = 0;
    if (mboot_info->flags & MULTIBOOT_INFO_CMDLINE) {
        // move cmdline string to top of heap
        char *cmdline = (char *)mboot_info->cmdline;
        int cmdline_len = strlen(cmdline)+1;
        if (cmdline != (char *)heap_start) {
            memmove(heap_start, cmdline, cmdline_len);
        }
        cmdline = (char *)heap_start;
        heap_start += cmdline_len;
        heap_end = heap_start;

        // Split the command line into argv array
        argv[argc++] = cmdline;

        for (int i = 1; cmdline[i] != '\0'; i += 1) {
            if (cmdline[i-1] == ' ') {
                cmdline[i-1] = '\0';
                argv[argc++] = cmdline + i;
            }
        }
    }
    argv[argc] = NULL;

    int res = main(argc, argv);
    exit(res);
    // Should not reach here
    printf("Failure to exit!!!\n");
    return res;
}
