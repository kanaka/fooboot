#include <stdint.h>
#include <string.h>
#include <io.h>
#include <fb.h>

static uint16_t *fb = (uint16_t *) FB_MEMORY;

uint8_t fb_cursor_x = 0;
uint8_t fb_cursor_y = 0;
uint8_t fb_color = 0x80;

// Move hardware cursor to given position
void fb_move_cursor(uint8_t x, uint8_t y)
{
    fb_cursor_x = x;
    fb_cursor_y = y;
    uint16_t pos = fb_cursor_y*80 + fb_cursor_x;
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT,    (pos >> 8) & 0xFF);
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT,    (pos) & 0xFF);
}

// Set the current color
void fb_set_color(uint8_t foreground, uint8_t background) {
    fb_color = ((background & 0x0F) << 4) | (foreground & 0x0F);
}

// Write single character at xy
void fb_put_xy(unsigned char c, uint8_t x, uint8_t y) {
    fb[y*80 + x] = (fb_color << 8) + c;
}

// Write single character at current position
void fb_put(unsigned char c) {
    fb_put_xy(c, fb_cursor_x, fb_cursor_y);
}

// Clear the screen
void fb_clear() {
    uint8_t x, y;
    fb_set_color(FB_WHITE, FB_BLACK);
    for (x=0; x < 80; x++) {
        for (y=0; y < 80; y++) {
            fb_put_xy(FB_SPACE, x, y);
        }
    }
    fb_move_cursor(0,0);
}

void fb_scroll() {
    // copy lines 1-24 -> 0-23
    memmove(fb, fb+80, 80*24*2);
    memset(fb+24*80, 0, 80*2);
    fb_move_cursor(0, 24);
}

// Write single charatcter at current position advancing the current position
void fb_putc(unsigned char c) {
    if (c == '\n') {
        fb_cursor_x = 0;
        fb_cursor_y += 1;
    } else if (c == '\r') {
        fb_cursor_x = 0;
    } else if (c == 0x08 && fb_cursor_x > 0) {
        fb_cursor_x -= 1;
    } else {
        fb_put(c);
        fb_cursor_x += 1;
    }
    // Wrap
    if (fb_cursor_x > 79) {
        fb_cursor_y += 1;
        fb_cursor_x = 0;
    }
    // Scroll
    if (fb_cursor_y > 24) {
        fb_scroll();
    }
    // TODO: do we really want to do this always?
    fb_move_cursor(fb_cursor_x, fb_cursor_y);
}

// Write null terminated string to FB at current position
int fb_write(const char *buf) {
    uint16_t offset = 0;
    while (buf[offset] != 0) {
        fb_putc(buf[offset]);
        offset += 1;
    }
    return offset;
}
