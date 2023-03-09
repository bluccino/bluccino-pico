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

  typedef struct PI_api {
    int (*console)(bool wait);
    void (*print)(PI_txt fmt,...);
    void (*sleep)(PI_ms ms);
    PI_us (*us)(void);
    void (*log)(int lvl,PI_txt fmt,...);
    void (*hello)(int lvl,PI_txt txt);
    void (*led)(int i,int val);
    int (*button)(void(*cb)(int i,int on));

    PI_us (*clock)(PI_us us);
    void (*now)(int *min,int *s,int *ms,int *us);
    void (*vprt)(PI_txt fmt, va_list ap);
    void (*vlog)(int lvl,PI_txt fmt, va_list ap);
  } PI_api;  // pico API

  static inline PI_api* _pi_api_(void)
  {
    static PI_api pico = {
      .console=pi_console, .print=pi_print,
      .sleep=pi_sleep, .us=pi_us,
      .log=pi_log, .hello=pi_hello,
      .led=pi_led, .button=pi_button,
      .clock=pi_clock, .now=pi_now,
      .vprint=pi_vprint, .vlog=pi_vlog,
    };
    return &pico;
  }

  #define pico (*_pi_api_())

#ifdef __cplusplus
}
#endif
#endif // __PICO_API_H__
