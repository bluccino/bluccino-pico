// pico/suite.h - complete C++ pico API
#ifndef __PICO_API_H__
#define __PICO_API_H__

#include "pico/rtos.h"

#ifdef __cplusplus
extern "C" {
#endif

  #include "pico/button.h"
  #include "pico/led.h"
  #include "pico/log.h"

  typedef struct PI_api {
    int (*console)(bool wait);
    void (*prt)(PI_txt fmt,...);
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
      .console=pi_console, .prt=pi_prt,
      .sleep=pi_sleep, .us=pi_us,
      .log=pi_log, .hello=pi_hello,
      .led=pi_led, .button=pi_button,
      .clock=pi_clock, .now=pi_now,
      .vprt=pi_vprt, .vlog=pi_vlog,
    };
    return &pico;
  }

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
  #define _PICO_ (*_pi_api_())

  class Pico {
    public:
      Pico(bool wait=true)
        { log(4,PI_B"console init ..."); console(wait); }
      int console(bool wait)
        { return _PICO_.console(wait); }
      void prt(PI_txt fmt,...)
        { va_list ap; va_start(ap,fmt); _PICO_.vprt(fmt,ap); va_end(ap); }
      void sleep(PI_ms ms) { _PICO_.sleep(ms); }
      PI_us us() { return _PICO_.us(); }
      void log(int lvl,PI_txt fmt,...)
        { va_list ap; va_start(ap,fmt); _PICO_.vlog(lvl,fmt,ap); va_end(ap); }
      void hello(int lvl,PI_txt txt) { _PICO_.hello(lvl,txt); }
      void led(int i, int val) { _PICO_.led(i,val); }
      int button(void (*cb)(int i,int on)) { return _PICO_.button(cb); }
      void now(int *min,int *s,int *ms,int *us)
        { _PICO_.now(min,s,ms,us); }
      PI_us clock(PI_us us)
        { return pi_clock(us); }
  };
#else
  #define pico (*_pi_api_())
#endif // __cplusplus
#endif // __PICO_API_H__
