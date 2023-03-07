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
    static bool nowait = false; // toggle if !wait
    static uint32_t dtr = 0xff; // UART line ctrl DTR
    static const struct device *dev =
        DEVICE_DT_GET(DT_CHOSEN(zephyr_console));

    if (dtr == 0xff) {  // if not enabled
      if (usb_enable(NULL) || !device_is_ready(dev))
        return -ENODEV;
    }
    for (dtr=0; dtr == 0; k_msleep(250)) {
      uart_line_ctrl_get(dev, UART_LINE_CTRL_DTR, &dtr);
      if (!wait || nowait) {
        nowait = true;  return (dtr == 0);
      }
    }
    return (dtr == 0);  // return 0 if console ready
  }
#else                             // DKs, using Segger RTT
  static inline int pi_console(bool wait) { return 0; }
#endif

typedef void (*_PI_vprt_)(PI_txt fmt, va_list ap);
static inline void pi_prt(PI_txt fmt,...);
static inline void _vprt_init_(PI_txt fmt, va_list ap);

static inline _PI_vprt_* _vprt_(void)
{
  static _PI_vprt_ vprt = vprintk; // _vprt_init_;
  return &vprt;
}

static inline void _vprt_init_(PI_txt fmt, va_list ap)
{
  *_vprt_() = vprintk; // use now vprintk
  pi_console(true);  // wait for ready
pi_prt(PI_B "console initialized!\n");
}

static inline void pi_vprt(PI_txt fmt,va_list ap)
{
  (*_vprt_())(fmt, ap);
}

static inline void pi_prt(PI_txt fmt,...)
{
  va_list ap;
	va_start(ap,fmt); pi_vprt(fmt, ap);	va_end(ap);
}

#endif // __PICO_CONSOLE__
