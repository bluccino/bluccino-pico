// pico/console.h - pico CONSOLE API
#ifndef __PICO_CONSOLE__
#define __PICO_CONSOLE__

#include <zephyr/kernel.h>
#include <zephyr/usb/usb_device.h>
#include <zephyr/drivers/uart.h>
#include "pico/ansi.h"

typedef const char *PI_txt;

#ifdef CONFIG_USB_DEVICE_PRODUCT  // USB/COM
  static inline int pi_console(bool wait)
  {
    static uint32_t dtr = 0xff; // UART line ctrl DTR
    static const struct device *dev =
        DEVICE_DT_GET(DT_CHOSEN(zephyr_console));

    if (dtr == 0xff) {  // if not enabled
      if (usb_enable(NULL) || !device_is_ready(dev))
        return -ENODEV;
    }
    for (dtr=0; dtr == 0; k_msleep(250)) {
      uart_line_ctrl_get(dev, UART_LINE_CTRL_DTR, &dtr);
      if (!wait) return (dtr == 0);
    }
    return (dtr == 0);  // return 0 if console ready
  }
#else                             // DKs, using Segger RTT
  static inline int pi_console(bool wait) { return 0; }
#endif

static inline void pi_vprt(PI_txt fmt, va_list ap)
{
  vprintk(fmt, ap);
}

static inline void pi_prt(PI_txt fmt,...)
{
  va_list ap;
	va_start(ap,fmt); pi_vprt(fmt, ap);	va_end(ap);
}

#endif // __PICO_CONSOLE__
