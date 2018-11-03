#ifndef SYM_TABLE_H
#define SYM_TABLE_H

struct sym_table_t {
    char *name;
    void *addr;
};

void sym_table_init();
void *sym_table_lookup (char *name);

#endif // SYM_TABLE_H
