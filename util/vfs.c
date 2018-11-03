#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <serial.h>

#include "sym_table.h"

int mem_fs_file_size(char *name) {
    char sym[100];
    int *lenptr;
    sprintf(sym, "%s_size", name);
    lenptr = (int *)sym_table_lookup(sym);
    if (lenptr) {
        return *lenptr;
    }
    return -1;
}

char *mem_fs_read_file(char *name, int *len) {
    if (len) {
        *len = mem_fs_file_size(name);
    }
    return sym_table_lookup(name);
}


int serial_file_size(char *name) {
    char buf[101];
    serial_write(SERIAL_COM2, "size: ");
    serial_write(SERIAL_COM2, name);
    serial_write(SERIAL_COM2, "\n");
    serial_read(SERIAL_COM2, buf, 7);
    if (strcmp("fdata: ", buf) == 0) {
        serial_read_until(SERIAL_COM2, buf, 10, '\n');
        int len = strtol(buf, NULL, 10);
        //printf("got fdata, len: %d\n", len);
        return len;
    } else if (strcmp("error: ", buf) == 0) {
        serial_read_until(SERIAL_COM2, buf, 100, '\n');
        fprintf(stderr, "got error: %s\n", buf);
        return -1;
    } else {
        fprintf(stderr, "got unknown response: '%s'\n", buf);
        return -1;
    }
}

int serial_read_file(char *name, char *buf) {
    serial_write(SERIAL_COM2, "read: ");
    serial_write(SERIAL_COM2, name);
    serial_write(SERIAL_COM2, "\n");
    serial_read(SERIAL_COM2, buf, 7);
    if (strcmp("fdata: ", buf) == 0) {
        serial_read_until(SERIAL_COM2, buf, 10, '\n');
        uint32_t len = strtol(buf, NULL, 10);
        //printf("got fdata, len: %d\n", len);
        serial_read(SERIAL_COM2, buf, len);
        //printf("fdata len: %d\n", len);
        //printf("file data:\n%s\n", buf);
        return len;
    } else if (strcmp("error: ", buf) == 0) {
        serial_read_until(SERIAL_COM2, buf, 1024, '\n');
        fprintf(stderr, "got error: %s\n", buf);
        return -1;
    } else {
        fprintf(stderr, "got unknown response: '%s'\n", buf);
        return -1;
    }
}

// First attempt the embedded file system,
// then try over the serial port COM2

int vfs_file_size(char *name) {
    int len = mem_fs_file_size(name);
    if (len >= 0) {
        return len;
    }
    return serial_file_size(name);
}

int vfs_read_file(char *name, char *buf) {
    int len = 0;
    char *tbuf = mem_fs_read_file(name, &len);
    if (tbuf) {
        memmove(buf, tbuf, len);
        buf[len] = '\0';
        return len+1;
    }
    return serial_read_file(name, buf);
}
