// pico/log.h - pico log API
#ifndef __PICO_LOG__
#define __PICO_LOG__

#include "pico/console.h"
#include "pico/time.h"

  // ANSI color switching sequences

#define PI_R     "\x1b[31m"        // red
#define PI_G     "\x1b[32m"        // green
#define PI_Y     "\x1b[33m"        // yellow
#define PI_B     "\x1b[34m"        // blue
#define PI_M     "\x1b[35m"        // magenta
#define PI_C     "\x1b[36m"        // cyan
#define PI_0     "\x1b[0m"         // reset

static inline int *pi_verbose(void)
{
  static int verbose = 0;
  return &verbose;
}

static inline void _pi_log_now_(int lvl)
{
  int min,s,ms,us;
  pi_now(&min,&s,&ms,&us);
  pi_prt("#%d[%05d:%02d:%03d.%03d] ",lvl,min,s,ms,us);
  for (int i=0;i < lvl;i++) pi_prt("  ");
}

#define pi_log(lvl,fmt,...)               \
        do { if (lvl<=*pi_verbose()) {    \
               _pi_log_now_(lvl);         \
               pi_prt(fmt,##__VA_ARGS__); \
               pi_prt(PI_0 "\n");         \
           }} while(0)

static inline void pi_hello(int lvl,const char *txt)
{
  *pi_verbose() = lvl;  // set verbose level
  pi_console(true);     // init console
  #if defined(PROJECT)  && defined(CONFIG_BOARD)
    pi_log(0,PI_R PROJECT" - %s (board %s)" PI_0,
           txt, CONFIG_BOARD);
  #else
    pi_log(1,PI_R "%s" PI_0, txt);
  #endif
}
#endif // __PICO_LOG__
