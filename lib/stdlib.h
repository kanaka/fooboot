#ifndef STDLIB_H
#define STDLIB_H

#include <stdint.h>

double atof(const char *nptr);
long int strtol(const char *nptr, char **endptr, int base);
unsigned long int strtoul(const char *nptr, char **endptr, int base);
unsigned long long int strtoull(const char *nptr, char **endptr, int base);

void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);

void exit(int status);

#endif /* STDLIB_H */
