// pico/console.h - pico CONSOLE API
#ifndef __PICO_CONSOLE__
#define __PICO_CONSOLE__
#include "pico/rtos.h"

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

typedef void (*_PI_vprint_)(PI_txt fmt, va_list ap);
static inline void pi_print(PI_txt fmt,...);
static inline void _vprint_init_(PI_txt fmt, va_list ap);

static inline _PI_vprint_* _vprint_(void)
{
  static _PI_vprint_ vprint = _vprint_init_;
  return &vprint;
}

static inline void _vprint_init_(PI_txt fmt, va_list ap)
{
  *_vprint_() = vprintk; // use vprintk from now
  pi_console(true);      // wait for ready
  vprintk(fmt,ap);       // our original task
}

static inline void pi_vprint(PI_txt fmt,va_list ap)
{
  (*_vprint_())(fmt, ap);
}

static inline void pi_print(PI_txt fmt,...)
{
  va_list ap;
	va_start(ap,fmt); pi_vprint(fmt, ap);	va_end(ap);
}
#endif // __PICO_CONSOLE__
