#ifndef FB_H
#define FB_H

#include <stdint.h>

// FB video memory address
#define FB_MEMORY               0x000B8000

// FB video memory colors
#define FB_BLACK                0x0
#define FB_BLUE                 0x1
#define FB_GREEN                0x2
#define FB_CYAN                 0x3
#define FB_RED                  0x4
#define FB_MAGENTA              0x5
#define FB_BROWN                0x6
#define FB_LIGHT_GRAY           0x7
#define FB_DARK_GRAY            0x8
#define FB_LIGHT_BLUE           0x9
#define FB_LIGHT_GREEN          0xA
#define FB_LIGHT_CYAN           0xB
#define FB_LIGHT_RED            0xC
#define FB_PINK                 0xD
#define FB_YELLOW               0xE
#define FB_WHITE                0xF

#define FB_SPACE                0x20

// The I/O ports
#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5

// The I/O port commands
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

void fb_move_cursor(uint8_t x, uint8_t y);

void fb_set_color(uint8_t foreground, uint8_t background);

void fb_clear();

void fb_put_xy(unsigned char c, uint8_t x, uint8_t y);

void fb_put(unsigned char c);

void fb_putc(unsigned char c);

int fb_write(const char *buf);

void fb_write_num(int32_t num, uint8_t base);

#endif // FB_H
