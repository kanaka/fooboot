#ifndef KERNEL_KBD_H
#define KERNEL_KBD_H

#include <stdint.h>


#define KBD_DATA_PORT        0x60
#define KBD_STATUS_REGISTER  0x64

struct key_event_struct
{
   uint8_t  shift;
   uint8_t  ctrl;
   uint8_t  down;
   uint8_t  escaped;

   uint8_t  code;
   uint8_t  key;
};
typedef struct key_event_struct key_event_t;

void kbd_init();

int kbd_received();
char kbd_getc();
void kbd_read_key_event(key_event_t *ke);
uint8_t kbd_get_key();

#endif /* KERNEL_KBD_H */
