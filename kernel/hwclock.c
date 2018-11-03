#include <stdint.h>
#include <io.h>
#include <hwclock.h>

// From: https://kernel.googlesource.com/pub/scm/utils/util-linux/util-linux/+/v2.7.1/sys-utils/hwclock.c

static inline unsigned char 
hclock_read(unsigned char reg) {
/*---------------------------------------------------------------------------
  Relative byte <reg> of the Hardware Clock value.
---------------------------------------------------------------------------*/
  register unsigned char ret;
  __asm__ volatile ("cli");
  /* & 0x7f ensures that we are not disabling NMI while we read.
     Setting on Bit 7 here would disable NMI
     */
  outb(reg & 0x7f, CLOCK_CTL_ADDR);
  ret = inb(CLOCK_DATA_ADDR);
  __asm__ volatile ("sti");
  return ret;
}


static inline int 
hclock_read_bcd (int addr) {
  int b;
  b = hclock_read(addr);
  return (b & 15) + (b >> 4) * 10;
}


void
read_hardware_clock_isa(struct tm *tm) {
  tm->tm_sec = hclock_read_bcd(0);
  tm->tm_min = hclock_read_bcd(2);
  tm->tm_hour = hclock_read_bcd(4);
  tm->tm_wday = hclock_read_bcd(6);
  tm->tm_mday = hclock_read_bcd(7);
  tm->tm_mon = hclock_read_bcd(8);
  tm->tm_year = hclock_read_bcd(9);

  tm->tm_mon--;             /* DOS uses 1 base */
  tm->tm_wday -= 3;         /* DOS uses 3 - 9 for week days */
  tm->tm_isdst = -1;        /* don't know whether it's daylight */
}
