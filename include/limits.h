#ifndef LIMITS_H
#define LIMITS_H

/* FIXME: It'd be nice to configure around these, but the include files are too
   painful.  These macros should at least be more portable than hardwired hex
   constants. */

#define CHAR_BIT   8

#ifndef ULONG_MAX
#define	ULONG_MAX	((unsigned long)(~0L))		/* 0xFFFFFFFF */
#endif

#ifndef ULLONG_MAX
#define	ULLONG_MAX	((unsigned long long)(~0L))	/* 0xFFFFFFFFFFFFFFFF */
#endif

#ifndef LONG_MAX
#define	LONG_MAX	((long)(ULONG_MAX >> 1))	/* 0x7FFFFFFF */
#endif

#ifndef LONG_MIN
#define	LONG_MIN	((long)(~LONG_MAX))		/* 0x80000000 */
#endif

#endif // LIMITS_H
