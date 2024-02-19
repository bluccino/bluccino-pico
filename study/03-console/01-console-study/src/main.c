//==============================================================================
// main.c - 01-console-study
//==============================================================================

#include "pico/pico.h"

int tab[20];                           // table to store return codes
int cnt = 0;

//==============================================================================
// wait for ready console
// - pico.console() is repeatedly called until no error code returned
// - error code is recorded for max 20 iterations
// - status LED toggles with 250ms period during this loop
// - any button press terminates initial waiting loop
// - note: pico.console() and subsequent pico.print/pico.log() statements
//   will never block
//==============================================================================

static void console(void)
{
  int err = pico.console(0);           // get console status (no wait)
  for(int i=0; err; i++) {
    if (cnt < sizeof(tab)/sizeof(tab[0]))
       tab[cnt++] = err;

    pico.led(1,-1);                    // blink until console ready
    if (pico.poll(-1)) break;          // any butto press terminates waiting

    pico.sleep(250*1000);              // sleep 250ms
    err = pico.console(0);             // get console status (no wait)
  }
}

//==============================================================================
// show error codes (return values of recent pico.console() calls)
//==============================================================================

static void show(void)
{
  pico.log(1,"");
  pico.print(_Y_"return codes of pico.console():");
  for (int i=0; i < cnt; i++)
     pico.print(" %d",tab[i]);
  pico.print("\n"_0_);
}

//==============================================================================
// RGB blinking
//==============================================================================

static void blink(void)
{
  static pi_txt txt[] = {"red","green","blue"};
  static pi_txt col[] = {_R_, _G_, _B_};

  pi_us time = 0;
	for (int i=0;; i++, time += 500*1000) {
    pico.sleep(time-pico.usec());
    int k = i % 3;
    pico.log(1,"%s%s",col[k],txt[k]);
    pico.led(-1,0);                    // all LEDs off
    pico.led(2+k,1);                   // LED @(2+k) on
  }
}

//==============================================================================
// main function:
// - wait for console readiness
// - print hello message
// - show return codes
// - RGB blinking
//==============================================================================

int main(void)
{
  console();                           // wait for console readiness
  pico.hello(4,"");                    // verbose level, hello msg
  show();                              // show
  blink();                             // RGB flashing
  return 0;
}
