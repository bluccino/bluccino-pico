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
    void (*print)(PI_txt fmt,...);
    void (*sleep)(PI_ms ms);
    PI_us (*us)(void);
    int (*log)(int lvl,PI_txt fmt,...);
    int (*hello)(int lvl,PI_txt txt);
    int (*led)(int i,int val);
    void (*button)(void(*cb)(int i,int on));
    int (*poll)(int i);

    PI_us (*clock)(PI_us us);
    void (*now)(int *ph, int *pmin, int *psec, int *pms, int *pus);
    int (*console)(bool wait);
    void (*vprint)(PI_txt fmt, va_list ap);
    int (*vlog)(char tag,int lvl,PI_txt fmt, va_list ap);
  } PI_api;  // pico API

  static inline PI_api* _pi_api_(void)
  {
    static PI_api pico = {
      .print=pi_print, .sleep=pi_sleep,
      .us=pi_us, .log=pi_log,
      .hello=pi_hello, .led=pi_led,
      .button=pi_button, .poll=pi_poll,
      .clock=pi_clock,
      .now=pi_now, .console=pi_console,
      .vprint=pi_vprint, .vlog=pi_vlog,
    };
    return &pico;
  }

  #define pico (*_pi_api_())
#ifdef __cplusplus
}
#endif
#endif // __PICO_API_H__
