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

  typedef struct {
    int (*console)(bool wait);
    void (*vprt)(PI_txt fmt, va_list ap);
    void (*prt)(PI_txt fmt,...);
    void (*sleep)(PI_ms ms);
    PI_us (*us)(void);
    PI_ms (*ms)(void);
    PI_us (*clock)(PI_us us);
    void (*now)(int *min,int *s,int *ms,int *us);
    void (*log)(int lvl,PI_txt fmt,...);
    void (*vlog)(int lvl,PI_txt fmt, va_list ap);
    void (*hello)(int lvl,PI_txt txt);
    void (*led)(int i,int val);
    int (*button)(void(*cb)(int i,int on));
  } PI_api;  // pico API

  static inline PI_api* _pi_api_(void)
  {
    static PI_api pico = {
      .console=pi_console, .vprt=pi_vprt, .prt=pi_prt,
      .sleep=pi_sleep, .us=pi_us, .ms=pi_ms, .clock=pi_clock,
      .now=pi_now, .log=pi_log, .vlog=pi_vlog,
      .hello=pi_hello, .led=pi_led, .button=pi_button,
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
      Pico(bool wait=true) { console(wait); }
      int console(bool wait) { return _PICO_.console(wait); }
      void prt(PI_txt fmt,...)
        { va_list ap; va_start(ap,fmt); _PICO_.vprt(fmt,ap); va_end(ap); }
      void sleep(PI_ms ms) { _PICO_.sleep(ms); }
      PI_us us() { return _PICO_.us(); }
      PI_us ms() { return _PICO_.ms(); }
      PI_us clock(PI_us us) { return pi_clock(us); }
      void now(int *min,int *s,int *ms,int *us) { _PICO_.now(min,s,ms,us); }
      void log(int lvl,PI_txt fmt,...)
        { va_list ap; va_start(ap,fmt); _PICO_.vlog(lvl,fmt,ap); va_end(ap); }
      void hello(int lvl,PI_txt txt) { _PICO_.hello(lvl,txt); }
      void led(int i, int val) { _PICO_.led(i,val); }
      int button(void (*cb)(int i,int on)) { return _PICO_.button(cb); }
  };
#else
  #define pico (*_pi_api_())
#endif // __cplusplus
#endif // __PICO_API_H__
