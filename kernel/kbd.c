#include <stdint.h>
#include <io.h>
#include <kbd.h>

void kbd_init() {
   //int data = inb(KBD_STATUS_REGISTER);     
   //outb(KBD_STATUS_REGISTER,data | 0x80); //Disables the keyboard  
   //outb(KBD_STATUS_REGISTER,data & 0x7F); //Enables the keyboard  
}

int kbd_received() {
    return inb(KBD_STATUS_REGISTER) & 0x1;
}

char kbd_getc() {
    while (!kbd_received());
    return inb(KBD_DATA_PORT);
}

int shift_L = 0;
int shift_R = 0;
int ctrl_L  = 0;
int ctrl_R  = 0;

void kbd_translate_scan_code(key_event_t *ke) {
    char unshifted[] = "\377\3771234567890-=\b"    // 0x00-0x0e
                       "\tqwertyuiop[]\r"          // 0x0f-0x1c
                       "\377asdfghjkl;'`"          // 0x1d-0x29
                       "\377\\zxcvbnm,./\377"      // 0x2a-0x36
                       "\377\377 ";                // 0x37-0x39
    char shifted[]   = "\377\377!@#$%^&*()_+\b"    // 0x00-0x0e
                       "\tQWERTYUIOP{}\r"          // 0x0f-0x1c
                       "\377ASDFGHJKL:\"~"         // 0x1d-0x29
                       "\377|ZXCVBNM<>?\377"       // 0x2a-0x36
                       "\377\377 ";                // 0x37-0x39
    uint8_t base_code = (ke->code & 0x7f);
    if (base_code <= 0x39) {
        if (shift_L || shift_R) {
            ke->key = shifted[base_code];
        } else {
            ke->key = unshifted[base_code];
        }
        if (ke->key == 0377) {
            ke->key = 0;
        }
    } else {
        ke->key = 0;
    }
    return;
}

void kbd_read_key_event(key_event_t *ke) {
    ke->code = kbd_getc();
    ke->escaped = 0;

    switch (ke->code) {
        case 0x2a: shift_L = 1; break;
        case 0xaa: shift_L = 0; break;
        case 0x36: shift_R = 1; break;
        case 0xb6: shift_R = 0; break;
        case 0x1d: ctrl_L  = 1; break;
        case 0x9d: ctrl_L  = 0; break;
        case 0xe0: ke->escaped = 1; break;
        default: break;
    }
    ke->shift = shift_L || shift_R;
    ke->ctrl = ctrl_L || ctrl_R;
    ke->down = ke->code & 0x80 ? 0 : 1;
    kbd_translate_scan_code(ke);
    return;
}

//#include <console.h>
// Returns 0 for key down events and for other non-translatable key up events
uint8_t kbd_get_key() {
    key_event_t ke = {0};
    kbd_read_key_event(&ke);
    //console_printf("here1 code: 0x%x, key: 0x%x, down: %d\n", ke.code, ke.key, ke.down);

    // If it is a key down return 0 for the key (key up/break) is when we
    // return a translation
    if (!ke.down) { ke.key = 0; }
    return ke.key;
}
