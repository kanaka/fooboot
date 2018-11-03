#ifndef VFS_H
#define VFS_H

#include <stdint.h>

char *mem_fs_read_file(char *name, int *len);

char *serial_read_file(char *name, int *len);

int vfs_file_size(char *name);

int vfs_read_file(char *name, char *buf);

#endif // VFS_H
