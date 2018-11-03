#include <stdint.h>

void memset(void *dest, uint8_t val, uint32_t len) {
    uint32_t i;
    uint8_t *p = (uint8_t*) dest;
    for(i=0; i < len; i++) {
        p[i] = val;
    }
}

void memmove(void *dest, const void *src, uint32_t len) {
    uint32_t i;
    if (dest == src) { return; }
    for (i=0; i < len; i++) {
        ((uint8_t *)dest)[i] = ((uint8_t *)src)[i];
    }
}

void memcpy(void *dest, const void *src, uint32_t len) {
    memmove(dest, src, len);
}

void strncpy(void *dest, const void *src, uint32_t len) {
    memmove(dest, src, len);
}

int strcmp(const char *s1, const char *s2) {
    for (;*s1 != 0 && *s2 != 0 && *s1 == *s2; s1++, s2++);
    return *s1 == *s2 ? 0 : *s1 < *s2 ? -1 : 1;
}

int strncmp(const char *s1, const char *s2, uint32_t len) {
    uint32_t i = 0;
    if (len == 0) return 0;
    for (;i < len && s1[i] != 0 && s1[i] == s2[i];i += 1);
    return i== len || s1[i] == s2[i] ? 0 : s1[i] < s2[i] ? -1 : 1;
}

size_t strlen(const char *s) {
    int len = 0;
    while (s[len] != '\0') len++;
    return len;
}

// Based on https://stackoverflow.com/a/25705264/471795
// This could be made much more efficient
char *strstr(const char *haystack, const char *needle)
{
    int i;
    size_t needle_len = strlen(needle);
    size_t len = strlen(haystack);

    if (0 == needle_len) {
        return (char *)haystack;
    }

    for (i=0; i<=(int)(len-needle_len); i++)
    {
        if ((haystack[0] == needle[0]) &&
            (0 == strncmp(haystack, needle, needle_len))) {
            return (char *)haystack;
        }
        haystack++;
    }
    return NULL;
}

