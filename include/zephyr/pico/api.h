// pico/suite.h - complete C++ pico API
#ifndef __PICO_API_H__
#define __PICO_API_H__

#include "pico/rtos.h"  // iclude first!

#ifdef __cplusplus
extern "C" {
#endif
  #include "pico/button.h"
  #include "pico/led.h"
  #include "pico/log.h"

  typedef struct pico_api {
    void (*print)(pico_txt fmt,...);
    void (*sleep)(pico_us ms);
    pico_us (*usec)(void);
    int (*log)(int lvl,pico_txt fmt,...);
    int (*hello)(int lvl,pico_txt txt);
    int (*led)(int i,int val);
    int (*button)(void(*cb)(int i,int on));
    int (*poll)(int i);

    pico_us (*_preset)(pico_us us);
    void (*_now)(int *ph, int *pmin, int *psec, int *pms, int *pus);
    int (*_console)(bool wait);
    void (*_vprint)(pico_txt fmt, va_list ap);
    int (*_vlog)(char tag,int lvl,pico_txt fmt, va_list ap);
  } pico_api;  // pico API

  #define PICO_API() {             \
            .print=pico_print,     \
            .sleep=pico_sleep,     \
            .usec=pico_usec,       \
            .log=pico_log,         \
            .hello=pico_hello,     \
            .led=pico_led,         \
            .button=pico_button,   \
            .poll=pico_poll,       \
            ._preset=pico_preset,   \
            ._now=pico_now,         \
            ._console=pico_console, \
            ._vprint=pico_vprint,   \
            ._vlog=pico_vlog,       \
          }

  static inline pico_api* _pico_apico_(void)
  {
    static pico_api pico = PICO_API();
    return &pico;
  }

  #define pico (*_pico_apico_())
#ifdef __cplusplus
}
#endif
#endif // __PICO_API_H__
