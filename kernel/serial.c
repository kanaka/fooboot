#include <stdint.h>
#include <io.h>
#include <serial.h>

void serial_init(uint16_t com, uint16_t divisor) {
    outb(SERIAL_INT_PORT(com),          0x00);  // Disable all interrupts
    outb(SERIAL_LINE_COMMAND_PORT(com), 0x80);  // Enable DLAB (set baud rate divisor)
    outb(SERIAL_DATA_PORT(com), divisor&0xFF);  // Set divisor to 1 (lo byte) 115200 baud
    outb(SERIAL_INT_PORT(com),    divisor>>8);  //                  (hi byte)
    outb(SERIAL_LINE_COMMAND_PORT(com),  0x03);  // 8 bits, no parity, one stop bit
    outb(SERIAL_FIFO_COMMAND_PORT(com),  0xC7);  // Enable FIFO, clear them, with 14-byte threshold
    outb(SERIAL_MODEM_COMMAND_PORT(com), 0x0B);  // IRQs enabled, RTS/DSR set
}

int serial_transmit_ready(uint16_t com)
{
    return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

void serial_putc(uint16_t com, char c) {
    while (!serial_transmit_ready(com));
    outb(SERIAL_DATA_PORT(com), c);
}

int serial_received(uint16_t com) {
   return inb(SERIAL_LINE_STATUS_PORT(com)) & 1;
}
 
char serial_getc(uint16_t com) {
   while (serial_received(com) == 0);
   return inb(SERIAL_DATA_PORT(com));
}

int serial_write(uint16_t com, const char *buf) {
    uint16_t offset = 0;
    while (buf[offset] != 0) {
        serial_putc(com, buf[offset]);
        offset += 1;
    }
    return offset;
}

// buf must have len+1
void serial_read_until(uint16_t com, char *buf, uint16_t len, char until) {
    uint16_t offset = 0;
    char ch;
    while (offset < len) {
        ch = serial_getc(com);
        if (ch == until) { break; }
        buf[offset] = ch;
        offset += 1;
    }
    buf[offset] = '\0';
}

// buf must have len+1
void serial_read(uint16_t com, char *buf, uint16_t len) {
    uint16_t offset = 0;
    while (offset < len) {
        buf[offset++] = serial_getc(com);
    }
    buf[offset] = '\0';
}
