#ifndef KERNEL_SERIAL_H
#define KERNEL_SERIAL_H

#include <stdint.h>

/* The I/O ports */

/* All the I/O ports are calculated relative to the data port. This is because
 * all serial ports (COM1, COM2, COM3, COM4) have their ports in the same
 * order, but they start at different values.
 */

#define SERIAL_COM1                         0x3F8      /* COM1 base port */
#define SERIAL_COM2                         0x2F8      /* COM2 base port */

#define SERIAL_DATA_PORT(base)              (base)
#define SERIAL_INT_PORT(base)               (base + 1)
#define SERIAL_FIFO_COMMAND_PORT(base)      (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base)      (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base)     (base + 4)
#define SERIAL_LINE_STATUS_PORT(base)       (base + 5)

/* The I/O port commands */

/* SERIAL_LINE_ENABLE_DLAB:
 * Tells the serial port to expect first the highest 8 bits on the data port,
 * then the lowest 8 bits will follow
 */
#define SERIAL_LINE_ENABLE_DLAB             0x80

void serial_init(uint16_t com, uint16_t divisor);
//void serial_configure_baud_rate(unsigned short com, unsigned short divisor);
//void serial_configure_line(unsigned short com);
void serial_putc(uint16_t com, char c);
int serial_received(uint16_t com);
char serial_getc(uint16_t com);

int serial_write(uint16_t com, const char *buf);
void serial_read_until(uint16_t com, char *buf, uint16_t len, char until);
void serial_read(uint16_t com, char *buf, uint16_t len);

#endif /* KERNEL_SERIAL_H */
