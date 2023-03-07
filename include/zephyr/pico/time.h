// pico/time.h - deal with system clock time
#ifndef __PICO_TIME_H__
#define __PICO_TIME_H__

#include "pico/rtos.h"

typedef int64_t PI_us;  // micro seconds
typedef int64_t PI_ms;  // mili seconds

static inline PI_us pi_clock(PI_us us)  // set us clock time
{
  return *_pi_us_offset_() = _rtos_us_clock_() - us;
}

static inline PI_us pi_us(void) // get current us-clock time
{
  PI_us us = _rtos_us_clock_();
  PI_us offset = *_pi_us_offset_();
  if (!offset) offset = pi_clock((PI_us)0);
  return us  - offset;  // return us clock time
}

static inline void pi_now(int *pmin, int *psec, int *pms, int *pus)
{
  static int min = 0;
  static int sec = 0;
  static PI_ms offset = 0;
  PI_us us = pi_us();   // clock time now in us

  *pus = us % 1000;     // map us to range 0 .. 999
  *pms = us/1000 - offset;

    // calculate trace time tick

  for (; *pms >= 1000; offset += 1000, sec++)
    *pms -= 1000;

  for (; sec >= 60; min++)
    sec -= 60;

  *pmin = min;  *psec = sec;
}

static inline void pi_sleep(PI_us us)              // deep sleep for given milliseconds
{
  if (us > 0)
    _rtos_sleep_us_((int)us);
}
#endif // __PICO_TIME_H__
