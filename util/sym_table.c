#include <string.h>

#include "sym_table.h"

extern struct sym_table_t sym_table[];

void *sym_table_lookup (char *name) {
    struct sym_table_t *s = &sym_table[0];

    for(; s->name; s++) {
        if(strcmp(s->name, name) == 0) {
            return s->addr;
        }
    }
    return NULL;
}
