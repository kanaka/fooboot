#ifndef KERNEL_HWCLOCK_H
#define KERNEL_HWCLOCK_H

#include <stdint.h>

#define CLOCK_CTL_ADDR 0x70
#define CLOCK_DATA_ADDR 0x71

struct tm {
  int tm_sec;                   /* Seconds.     [0-60] (1 leap second) */
  int tm_min;                   /* Minutes.     [0-59] */
  int tm_hour;                  /* Hours.       [0-23] */
  int tm_mday;                  /* Day.         [1-31] */
  int tm_mon;                   /* Month.       [0-11] */
  int tm_year;                  /* Year - 1900.  */
  int tm_wday;                  /* Day of week. [0-6] */
  int tm_yday;                  /* Days in year.[0-365] */
  int tm_isdst;                 /* DST.         [-1/0/1]*/
};


void read_hardware_clock_isa(struct tm *tm);

#endif /* KERNEL_HWCLOCK_H */
