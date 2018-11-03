#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int errno;

extern uint32_t *heap_end;

void *malloc(size_t size) {
    uint32_t *ptr = heap_end;
    heap_end += (size+sizeof(*heap_end)-1)/sizeof(*heap_end);
    return ptr;
}

void free(void *ptr) {
    // TODO: implement
    (void)ptr;
}

void *calloc(size_t nmemb, size_t size) {
    char *res = malloc(nmemb*size);
    memset(res, 0, nmemb*size);
    return res;
}

#define __NR_exit 93
void exit(int status)
{
  // qemu: https://lists.gnu.org/archive/html/qemu-devel/2012-12/msg01635.html
  // requires: -device isa-debug-exit,iobase=0xf4,iosize=0x04
  outb(0xf4, status);
  for (;;) {}
}
