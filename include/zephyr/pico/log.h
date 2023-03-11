// pico/log.h - pico log API
#ifndef __PICO_LOG__
#define __PICO_LOG__

#include "pico/console.h"
#include "pico/time.h"
#include "pico/version.h"

static inline int *pi_verbose(void)
{
  static int verbose = 0;
  return &verbose;
}

static inline int pi_vlog(int lvl,PI_txt fmt,va_list ap)
{
  if (!fmt)
    return pi_console(false); // return err if not ready
  else if (lvl <= *pi_verbose()) {
    int min,s,ms,us;
    pi_now(&min,&s,&ms,&us);
    pi_print("#%d[%05d:%02d:%03d.%03d] ",lvl,min,s,ms,us);
    for (int i=0;i < lvl;i++) pi_print("  ");
    if (*fmt) {
      pi_vprint(fmt,ap);
      pi_print("\n" PI_0);
    }
    return 0; // log OK
  }
  return 1; // log suppressed
}

static inline int pi_log(int lvl,PI_txt fmt,...)
{
  va_list ap;  int err;
  va_start(ap,fmt); err = pi_vlog(lvl,fmt, ap); va_end(ap);
  return err;
}

static inline void pi_hello(int lvl,const char *txt)
{
  *pi_verbose() = lvl;  // set verbose level
  #if defined(PROJECT)  && defined(CONFIG_BOARD)
    pi_log(0,PI_R PROJECT" - %s (board %s, pico %s)" PI_0,
           txt, CONFIG_BOARD,PI_VERSION);
  #else
    pi_log(1,PI_R "%s (pico %s)" PI_0, txt,PI_VERSION);
  #endif
}
#endif // __PICO_LOG__
