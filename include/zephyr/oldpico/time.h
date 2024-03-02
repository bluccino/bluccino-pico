// pico/time.h - deal with system clock time
#ifndef __PICO_TIME_H__
#define __PICO_TIME_H__

#include "pico/rtos.h"
#include "pico/type.h"

static inline pico_us pico_clock(pico_us us)  // preset us clock time
{
  return *_rtos_us_offset_() = _rtos_us_clock_() - us;
}

static inline pico_us pico_usec(void) // get current us-clock time
{
  pico_us us = _rtos_us_clock_();
  pico_us offset = *_rtos_us_offset_();
  if (!offset) offset = pico_clock((pico_us)0);
  return us - offset;  // return us clock time
}

static inline void pico_now
  (int *ph, int *pmin, int *psec, int *pms, int *pus)
{
  static int min = 0; static int sec = 0;
  static pico_ms offset = 0;
  pico_us us = pico_usec();   // clock time now in us

  *pus = us % 1000;     // map us to range 0 .. 999
  *pms = us/1000 - offset;

    // calculate trace time tick

  for (; *pms >= 1000; offset += 1000, sec++)
    *pms -= 1000;

  for (; sec >= 60; min++)
    sec -= 60;

  *ph = min/60;  *pmin = min%60;  *psec = sec;
}

static inline void pico_delay(pico_us us)  // deep sleep for given microseconds
{
  if (us > 0)
    _rtos_sleep_us_((int)us);
}
#endif // __PICO_TIME_H__
