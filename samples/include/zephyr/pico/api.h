// pico/suite.h - complete C++ pico API
#ifndef __PICO_API_H__
#define __PICO_API_H__

#include "pico/rtos.h"

#ifdef __cplusplus
extern "C" {
#endif

  #include "pico/console.h"
  #include "pico/time.h"
  #include "pico/log.h"
  #include "pico/led.h"
  #include "pico/button.h"

  typedef struct {
    int (*console)(bool wait);
    void (*sleep)(PI_ms ms);
    PI_us (*us)(void);
    PI_ms (*ms)(void);
    void (*now)(int *min,int *s,int *ms,int *us);
    void (*hello)(int lvl,PI_txt txt);
    void (*led)(int i,int val);
    int (*button)(void(*cb)(int i,int on));
  } PI_api;  // pico API

  static inline PI_api* _pi_api_(void)
  {
    static PI_api pico = {
      .console=pi_console, .sleep=pi_sleep, .us=pi_us, .ms=pi_ms,
      .now=pi_now, .hello=pi_hello, .led=pi_led, .button=pi_button,
    };
    return &pico;
  }

#ifdef __cplusplus
}
#endif

#define prt(f,...)     pi_prt(f,##__VA_ARGS__)
#define log(lvl,f,...) pi_log(lvl,f,##__VA_ARGS__)

#ifdef __cplusplus
  #define _PI_ (*_pi_api_())

  class Pico {
    public:
      Pico(bool wait=true) { console(wait); }
      int console(bool wait) { return _PI_.console(wait); }
      void sleep(PI_ms ms) { _PI_.sleep(ms); }
      PI_us us() { return _PI_.us(); }
      PI_us ms() { return _PI_.ms(); }
      void now(int *min,int *s,int *ms,int *us) { _PI_.now(min,s,ms,us); }
      void hello(int lvl,PI_txt txt) { _PI_.hello(lvl,txt); }
      void led(int i, int val) { _PI_.led(i,val); }
      int button(void (*cb)(int i,int on)) { return _PI_.button(cb); }
  };
#else
  #define pico (*_pi_api_())
#endif // __cplusplus
#endif // __PICO_API_H__
