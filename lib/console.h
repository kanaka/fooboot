#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdint.h>

void console_putc(uint8_t c);

uint8_t console_getc();

void console_write(const char * buf);

#endif /* CONSOLE_H */
