#include <stdint.h>
#include <serial.h>
#include <kbd.h>
#include <fb.h>
#include <console.h>

#include <stdarg.h>

void console_putc(uint8_t c) {
    fb_putc(c);
    serial_putc(SERIAL_COM1, c);
}

uint8_t console_getc() {
    uint8_t c = 0;
    while (1) {
        if (kbd_received()) {
            c = kbd_getc();
// TODO: fix on real hardware. Reads in noise. 
       } else if (serial_received(SERIAL_COM1)) {
            c = serial_getc(SERIAL_COM1);
        }
        if (c) {
            // Translate carriage return to newlines
            if (c == '\r') { c = '\n'; }
            return c;
        }
        // Loop until c is a valid character (not 0)
    }
}

void console_write(const char * buf) {
    serial_write(SERIAL_COM1, buf);
    fb_write(buf);
}

