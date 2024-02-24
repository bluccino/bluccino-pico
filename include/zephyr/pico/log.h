// pico/log.h - pico log API
#ifndef __PICO_LOG__
#define __PICO_LOG__

#include "pico/console.h"
#include "pico/time.h"
#include "pico/version.h"

//==============================================================================
// helper: set verbose level
// - usage: *_pico_verbose_() = 2        // set verbose level
//          verbose = *_pico_verbose_()  // get verbose level
//==============================================================================

static inline int *_pico_verbose_(void)
{
  static int verbose = 1;  // initial verbose level = 1
  return &verbose;
}

//==============================================================================
// set verbose level  // API function
// - usage: pico_verbose(lvl)           // set verbose level (if lvl >= 0)
//          verbose = pico_verbose(-1)  // get verbose level, don't change lvl
//==============================================================================

static inline int pico_verbose(int lvl)
{
  int old = *_pico_verbose_();
  if (lvl >= 0) *_pico_verbose_() = lvl;  // change verbose lvl for lvl >= 0
  return old;
}

//==============================================================================
// variable arg list based formatted logging with log level
// - usage: pico_vlog('#',lvl,"here we go",ap); // log text if lvl<=verbose lvl.
//          err = pico_vlog('#',0,NULL,ap);     // get ready state of console
//          ready = !pico_vlog('#',0,NULL,ap);  // is console ready?
// - return value:
//   1) err = pico_vlog(0,NULL,ap)  // err=0 no err/ready, err:non-zero err code
//   2) else: err=0 if log performed, err=1 if log suppressed
//==============================================================================

static inline int pico_vlog(char tag,int lvl,pico_txt fmt,va_list ap)
{
  if (!fmt)
    return pico_console(false); // set non-block-console, return err ifn't ready
  else if (lvl <= *_pico_verbose_()) {
    int h,min,s,ms,us;
    pico_now(&h,&min,&s,&ms,&us);
    pico_print("%c%d[%d:%02d:%02d:%03d.%03d] ",tag,lvl,h,min,s,ms,us);
    for (int i=0;i < lvl;i++) pico_print("  ");
    if (*fmt) {
      pico_vprint(fmt,ap);
      pico_print("\n" _0_);
    }
    return 0; // log OK
  }
  return 1; // log suppressed
}

//==============================================================================
// formatted logging with log level
// - usage: pico_log(lvl,"here we go"); // log text if lvl <= verbose level
//          err = pico_log(0,NULL);     // get ready state of console
//          ready = !pico_log(0,NULL);  // is console ready
//==============================================================================

static inline int pico_log(int lvl,pico_txt fmt,...)
{
  va_list ap;  int err;
  va_start(ap,fmt); err = pico_vlog('#',lvl,fmt, ap); va_end(ap);
  return err;
}

//==============================================================================
// set log level and print hello message (while resetting clock)
// - print project/board info and Pico version number
// - usage: pico_hello(lvl,"");  // set verbose level, print project/board/version
//          pico_hello(lvl,"let's go ...");// set verbose level, add specific msg
//          old = pico_hello(lvl,NULL);    // get old/change verbose lvl, no print
//          verbose = pico_hello(-1,NULL); // get verbose level, no print
//==============================================================================

static inline int pico_hello(int lvl,pico_txt txt)
{
  int old = *_pico_verbose_();
  if (lvl >= 0) *_pico_verbose_() = lvl;  // set verbose level
  pico_clock(0);  // reset clock time
  if (txt) {
  	#if defined(PROJECT) && defined(CONFIG_BOARD)
    	pico_log(0,_R_ PROJECT" - %s (board %s, pico %s)" _0_,
           		txt, CONFIG_BOARD,PI_VERSION);
  	#else
			pico_log(1,_R_ "%s (pico %s)" _0_, txt,PI_VERSION);
		#endif
  }
  return old;
}
#endif // __PICO_LOG__
