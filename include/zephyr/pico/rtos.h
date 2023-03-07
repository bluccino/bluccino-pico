// pico/rtos.h - ZEPHYR RTOS access
#ifndef __PICO_RTOS_H__
#define __PICO_RTOS_H__

#include <zephyr/kernel.h>
#include <zephyr/usb/usb_device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/uart.h>

#define _rtos_sleep_us_(us)  k_usleep((int32_t)us)

   // Zephyr RTOS us clock time

static inline int64_t _rtos_us_clock_(void)
{
  uint64_t cyc = k_uptime_ticks();
  uint64_t f = sys_clock_hw_cycles_per_sec();
  return (int64_t)((1000000*cyc)/f);
}

static inline int64_t*_pi_us_offset_(void)
{
  static int64_t offset = 0;
  return &offset;
}

#endif // __PICO_RTOS_H__
