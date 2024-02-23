// pico/console.h - pico CONSOLE API

#ifndef __PICO_CONSOLE__
#define __PICO_CONSOLE__
#include "pico/rtos.h"
#include "pico/type.h"

typedef void (*_pico_vprint_)(pico_txt fmt, va_list ap);
static inline void _vprint_init_(pico_txt fmt, va_list ap);

//==============================================================================
// PICO console function
// - usage: err = pico_console(true)  // wait for console ready, then return 0
//          err = pico_console(false) // check console status, ready if err=0
// - if CONFIG_USB_DEVICE_PRODUCT is undefined then pico_console() runs as dummy
//   function that never waits for readiness and always returns err=0 (ready)
// - once the second form (pico_console(false)) has been called, any further
//   pico_console() call will never again wait, just return console status.
// - in this sense call pico_console(false) before any call to pico_print() or
//   pico_vprint() to deactivate the implicit console waiting mechanism.
//==============================================================================
#ifdef CONFIG_USB_DEVICE_PRODUCT  // USB/COM

  static inline int pico_console(bool wait)
  {
    static bool nowait = false; // toggle if !wait
    static uint32_t dtr = 0xff; // UART line ctrl DTR
    static const struct device *dev =
        DEVICE_DT_GET(DT_CHOSEN(zephyr_console));

    if (!device_is_ready(dev)) return -ENODEV;           // err code -19
    if (dtr == 0xff) { // for the very first time
      int err = usb_enable(NULL);
      if (err && err != -EALREADY) return err;  // usb_enable() with error
    }

    for (dtr=0; dtr == 0; k_msleep(250)) {
      uart_line_ctrl_get(dev, UART_LINE_CTRL_DTR, &dtr); // get console status
      if (!wait || nowait) {
        nowait = true;  return (dtr == 0); // return 1 if console not ready
      }
    }
    return (dtr == 0);  // return 0 if console ready
  }

#else                             // DKs, using Segger RTT
  static inline int pico_console(bool wait) { return 0; }
#endif
//==============================================================================
// static sorage of PICO vprint vector
// - usage: _PI_vpint_ vprint = *_vprint_();  vprint(fmt,ap);  // call vprint()
//          *_vprint_() = vprintk;  // redirect vprint() to Zephyr vprintk()
//==============================================================================

//typedef void (*_pico_vprint_)(pico_txt fmt, va_list ap);
//static inline void pico_print(pico_txt fmt,...);
//static inline void _vprint_init_(pico_txt fmt, va_list ap);

static inline _pico_vprint_* _vprint_(void)
{
  static _pico_vprint_ vprint = _vprint_init_;
  return &vprint;
}

//==============================================================================
// initial vprint() function, redirecting further calls to Zephyr vprintk()
// - usage: _vprint_init_(fmt,fa);  // wait for console, redirect & vprintk()
// - to disable waiting for console call pico_console(false) before
//==============================================================================

static inline void _vprint_init_(pico_txt fmt, va_list ap)
{
  *_vprint_() = vprintk; // use vprintk from now
  pico_console(true);      // wait for ready (if console waiting is not disabled)
  vprintk(fmt,ap);       // our original task
}

//==============================================================================
// PICO vprint() function, 1x forward to _vprint_init_(), then fwd. to vprintk()
// - usage: pico_vprint(fmt,fa);  // wait for console, redirect & vprintk()
// - to disable waiting for console call pico_console(false) before
//==============================================================================

static inline void pico_vprint(pico_txt fmt,va_list ap)
{
  (*_vprint_())(fmt, ap);
}

//==============================================================================
// PICO print() function, convert variable arg list into vprint() compatible
// - usage: pico_print(fmt,...);  // wait for console, redirect & vprintk()
// - to disable waiting for console call pico_console(false) before
//==============================================================================

static inline int pico_print(pico_txt fmt,...)
{
  va_list ap;
	va_start(ap,fmt); pico_vprint(fmt, ap);	va_end(ap);
  return 0;
}

#endif // __PICO_CONSOLE__
