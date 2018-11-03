#include <stdint.h>
#include <stdarg.h>
#include <mini-printf.h>
#include <console.h>
#include <stdio.h>

//FILE *stdin = 0;
//FILE *stdout = 0;
//FILE *stderr = 0;
//struct _IO_FILE *stdin = 0;
//struct _IO_FILE *stdout = 0;
//struct _IO_FILE *stderr = 0;
FILE *stdin = 0;
FILE *stdout = 0;
FILE *stderr = 0;

int putchar(int c) {
    console_putc(c);
    return c;
}

int fputs(const char *s, FILE *stream) {
    (void)stream;
    for (int i = 0; s[i] != 0; i++) {
        putchar(s[i]);
    }
    return 1;
}

int sprintf(char *str, const char *fmt, ...) {
    int ret;
    va_list va;
    va_start(va, fmt);
    ret = mini_vsnprintf(str, 2048, fmt, va);
    va_end(va);

    return ret;
}

int snprintf(char *str, size_t size, const char *fmt, ...) {
    int ret;
    va_list va;
    va_start(va, fmt);
    ret = mini_vsnprintf(str, size, fmt, va);
    va_end(va);

    return ret;
}

int printf(const char *fmt, ...) {
    char buffer[2048];
    int ret;
    va_list va;
    va_start(va, fmt);
    ret = mini_vsnprintf(buffer, 2048, fmt, va);
    va_end(va);

    if (ret > 0) {
        console_write(buffer);
    }

    return ret;
}

int fprintf(FILE *stream, const char *fmt, ...) {
    (void)stream;
    char buffer[2048];
    int ret;
    va_list va;
    va_start(va, fmt);
    ret = mini_vsnprintf(buffer, 2048, fmt, va);
    va_end(va);

    if (ret > 0) {
        console_write(buffer);
    }

    return ret;
}

