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

// public pico functions not included in pico API


  pico_us pico_clock(pico_us us);
  void pico_now(int *ph, int *pmin, int *psec, int *pms, int *pus);
  int pico_console(bool wait);
  void pico_vprint(pico_txt fmt, va_list ap);
  int pico_vlog(char tag,int lvl,pico_txt fmt, va_list ap);
  int pico_vsnprint(char *buf,int size,pico_txt fmt,va_list ap);
  int pico_verbose(int lvl);

// pico API

  typedef struct pico_api {
    int (*print)(pico_txt fmt,...);
    void (*delay)(pico_us ms);
    pico_us (*usec)(void);
    int (*log)(int lvl,pico_txt fmt,...);
    int (*hello)(int lvl,pico_txt txt);
    int (*led)(int i,int val);
    int (*button)(void(*isr)(int i,int on));
    int (*poll)(int i);
  } pico_api;  // pico API

  #define PICO_API() {              \
            .print=pico_print,      \
            .delay=pico_delay,      \
            .usec=pico_usec,        \
            .log=pico_log,          \
            .hello=pico_hello,      \
            .led=pico_led,          \
            .button=pico_button,    \
            .poll=pico_poll,        \
          }

  static inline pico_api* _pico_api_(void)
  {
    static pico_api pico = PICO_API();
    return &pico;
  }

  #define pico (*_pico_api_())
#ifdef __cplusplus
}
#endif
#endif // __PICO_API_H__
