#ifndef STDINT_H
#define STDINT_H

#define INT64_MIN   -9223372036854775807LL-1
#define INT64_MAX    9223372036854775807LL
#define UINT64_MAX   18446744073709551615ULL
#define INT32_MIN   -2147483648
#define INT32_MAX    2147483647
#define UINT32_MAX   4294967295

typedef unsigned long long   uint64_t;
typedef          long long   int64_t;
typedef          int         int32_t;
typedef unsigned int         uint32_t;
typedef          int         int32_t;
typedef unsigned short       uint16_t;
typedef          short       int16_t;
typedef unsigned char        uint8_t;
typedef          char        int8_t;

typedef unsigned int         size_t;

#endif // STDINT_H
