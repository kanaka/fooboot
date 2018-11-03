#ifndef STRING_H
#define STRING_H

#include <stdint.h>

void memset(void *dest, uint8_t val, size_t len);
void memmove(void *dest, const void *src, size_t len);
void memcpy(void *dest, const void *src, uint32_t len);
int strncpy(const char *dest, const char *src, size_t len);

int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, uint32_t len);


size_t strlen(const char *s);

char *strstr(const char *haystack, const char *needle);

char *strtok(char *str, const char *delim);

#endif /* STRING_H */
