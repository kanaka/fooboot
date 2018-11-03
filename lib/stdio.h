#ifndef STDIO_H
#define STDIO_H

#include <stdint.h>

#include <mini-printf.h>
#define vsnprintf mini_vsnprintf

struct _IO_FILE;
typedef struct _IO_FILE FILE;

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;


int fputs(const char *s, FILE *stream);

int putchar(int c);

int sprintf(char *str, const char *fmt, ...);

int snprintf(char *str, size_t size, const char *fmt, ...);

int printf(const char *fmt, ...);

int fprintf(FILE *stream, const char *fmt, ...);

#endif /* STDIO_H */
