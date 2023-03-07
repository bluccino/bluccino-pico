// pico/log.h - pico log API
#ifndef __PICO_LOG__
#define __PICO_LOG__

#include "pico/ansi.h"
#include "pico/console.h"
#include "pico/time.h"

static inline int *pi_verbose(void)
{
  static int verbose = 0;
  return &verbose;
}

static inline void pi_vlog(int lvl,PI_txt fmt,va_list ap)
{
  if (lvl <= *pi_verbose()) {
    int min,s,ms,us;
    pi_now(&min,&s,&ms,&us);
    pi_prt("#%d[%05d:%02d:%03d.%03d] ",lvl,min,s,ms,us);
    for (int i=0;i < lvl;i++) pi_prt("  ");
    pi_vprt(fmt,ap);
    pi_prt("\n" PI_0);
  }
}

static inline void pi_log(int lvl,PI_txt fmt,...)
{
  va_list ap;
  va_start(ap,fmt); pi_vlog(lvl,fmt, ap);	va_end(ap);
}

static inline void pi_hello(int lvl,const char *txt)
{
  *pi_verbose() = lvl;  // set verbose level
  //pi_console(true);     // init console
  #if defined(PROJECT)  && defined(CONFIG_BOARD)
    pi_log(0,PI_R PROJECT" - %s (board %s)" PI_0,
           txt, CONFIG_BOARD);
  #else
    pi_log(1,PI_R "%s" PI_0, txt);
  #endif
}
#endif // __PICO_LOG__
