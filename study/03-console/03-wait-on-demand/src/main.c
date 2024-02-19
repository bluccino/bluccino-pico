//==============================================================================
// main.c - 03-wait-on-demand
//==============================================================================

#include "pico/pico.h"

int tab[20];                           // table to store return codes
int cnt = 0;

//==============================================================================
// wait for ready console with option to break with button press
// - pico.console() is repeatedly called until no error code returned
// - error code is recorded for max 20 iterations
// - status LED toggles with 250ms period during this loop
// - any button press terminates initial waiting loop
// - note: pico.console() and subsequent pico.print/pico.log() statements
//   will never block
//==============================================================================

static void wait_on_demand(void)
{
   pico.console(0);    // init console as non-blocking
   if (pico.poll(-1)) {
     while (pico.poll(-1));
     for (;pico.console(0) && !pico.poll(-1); pico.sleep(250*1000))
       pico.led(1,-1);                    // blink until console ready
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
    pico.sleep(time-pico.us());
    int k = i % 3;
    pico.log(1,"%s%s",col[k],txt[k]);
    pico.led(-1,0);                    // all LEDs off
    pico.led(2+k,1);                   // LED @(2+k) on
  }
}

//==============================================================================
// main function:
// - wait for console ready or any button press
// - print hello message
// - show return codes
// - RGB blinking
//==============================================================================

int main(void)
{
  wait_on_demand();         // wait for console ready or any button press
  pico.hello(4,"");          // verbose level, hello msg
  show();                    // show
  blink();                   // RGB flashing
  return 0;
}
