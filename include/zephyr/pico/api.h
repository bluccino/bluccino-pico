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

  typedef struct pi_api {
    void (*print)(pi_txt fmt,...);
    void (*sleep)(pi_us ms);
    pi_us (*usec)(void);
    int (*log)(int lvl,pi_txt fmt,...);
    int (*hello)(int lvl,pi_txt txt);
    int (*led)(int i,int val);
    int (*button)(void(*cb)(int i,int on));
    int (*poll)(int i);

    pi_us (*preset)(pi_us us);
    void (*now)(int *ph, int *pmin, int *psec, int *pms, int *pus);
    int (*console)(bool wait);
    void (*vprint)(pi_txt fmt, va_list ap);
    int (*vlog)(char tag,int lvl,pi_txt fmt, va_list ap);
  } pi_api;  // pico API

  #define PI_API() {             \
            .print=pi_print,     \
            .sleep=pi_sleep,     \
            .usec=pi_usec,       \
            .log=pi_log,         \
            .hello=pi_hello,     \
            .led=pi_led,         \
            .button=pi_button,   \
            .poll=pi_poll,       \
            .preset=pi_preset,   \
            .now=pi_now,         \
            .console=pi_console, \
            .vprint=pi_vprint,   \
            .vlog=pi_vlog,       \
          }

  static inline pi_api* _pi_api_(void)
  {
    static pi_api pico = PI_API();
    return &pico;
  }

  #define pico (*_pi_api_())
#ifdef __cplusplus
}
#endif
#endif // __PICO_API_H__
