// pico/log.h - pico log API
#ifndef __PICO_LOG__
#define __PICO_LOG__

#include "pico/console.h"
#include "pico/time.h"
#include "pico/version.h"

//==============================================================================
// helper: set verbose level
// - usage: *_pi_verbose_() = 2        // set verbose level
//          verbose = *_pi_verbose_()  // get verbose level
//==============================================================================

static inline int *_pi_verbose_(void)
{
  static int verbose = 0;
  return &verbose;
}

//==============================================================================
// variable arg list based formatted logging with log level
// - usage: pi_vlog('#',lvl,"here we go",ap); // log text if lvl <= verbose lvl.
//          err = pi_vlog('#',0,NULL,ap);     // get ready state of console
//          ready = !pi_vlog('#',0,NULL,ap);  // is console ready
// - return value:
//   1) err = pi_vlog(0,NULL,ap)  // err=0 no error/ready, err:non-zero err code
//   2) else: err=0 if log performed, err=1 if log suppressed
//==============================================================================

static inline int pi_vlog(char tag,int lvl,PI_txt fmt,va_list ap)
{
  if (!fmt)
    return pi_console(false); // return err if not ready
  else if (lvl <= *_pi_verbose_()) {
    int h,min,s,ms,us;
    pi_now(&h,&min,&s,&ms,&us);
    pi_print("%c%d[%d:%02d:%02d:%03d.%03d] ",tag,lvl,h,min,s,ms,us);
    for (int i=0;i < lvl;i++) pi_print("  ");
    if (*fmt) {
      pi_vprint(fmt,ap);
      pi_print("\n" _0_);
    }
    return 0; // log OK
  }
  return 1; // log suppressed
}

//==============================================================================
// formatted logging with log level
// - usage: pi_log(lvl,"here we go"); // log text if lvl <= verbose level
//          err = pi_log(0,NULL);     // get ready state of console
//          ready = !pi_log(0,NULL);  // is console ready
//==============================================================================

static inline int pi_log(int lvl,PI_txt fmt,...)
{
  va_list ap;  int err;
  va_start(ap,fmt); err = pi_vlog('#',lvl,fmt, ap); va_end(ap);
  return err;
}

//==============================================================================
// set log level and print hello message
// print project/board info and Pico version number
// - usage: pi_hello(lvl,"");  // set verbose level, print project/board/version
//          pi_hello(lvl,"let's go ...");// set verbose level, add specific msg
//          old = pi_hello(lvl,NULL);    // get old/change verbose lvl, no print
//          verbose = pi_hello(-1,NULL); // get verbose level, no print
//==============================================================================

static inline int pi_hello(int lvl,PI_txt txt)
{
  int old = *_pi_verbose_();
  if (lvl >= 0) *_pi_verbose_() = lvl;  // set verbose level
  if (txt) {
  	#if defined(PROJECT)  && defined(CONFIG_BOARD)
    	pi_log(0,_R_ PROJECT" - %s (board %s, pico %s)" _0_,
           		txt, CONFIG_BOARD,PI_VERSION);
  	#else
			pi_log(1,_R_ "%s (pico %s)" _0_, txt,PI_VERSION);
		#endif
  }
  return old;
}
#endif // __PICO_LOG__
