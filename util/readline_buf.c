#include <console.h>

#include <stdio.h>
#include <stdbool.h>

// Returns true if line successfully read into buf, false for EOF
bool readline_buf(const char *prompt, char *buf, int cnt) {
    char c;
    int idx = 0;
    console_write(prompt);
    while (idx < cnt) {
        c = console_getc();
        if (c == 0x4) {
            if (idx == 0) return false;
            continue;
        }
        // Backspace (0x08 from FB console, 0x7f from serial console)
        if (c == 0x08 || c == 0x7f) {
            if (idx > 0) {
                idx--;
                console_putc(0x08);
                console_putc(' ');
                console_putc(0x08);
            }
            continue;
        }
        console_putc(c);
        if (c == '\n') {
            break;
        }
        buf[idx++] = c;
    };
    buf[idx] = '\0';
    return true;
}
