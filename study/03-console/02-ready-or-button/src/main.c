//==============================================================================
// main.c - 02-ready-or-button
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

static void ready_or_button(void)
{
   for (;pico.log(0,NULL) && !pico.poll(-1); pico.delay(250*1000))
      pico.led(1,-1);                    // blink until console ready
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
  static pico_txt txt[] = {"red","green","blue"};
  static pico_txt col[] = {_R_, _G_, _B_};

  pico_us time = 0;
	for (int i=0;; i++, time += 500*1000) {
    pico.delay(time-pico.usec());
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
  ready_or_button();         // wait for console ready or any button press
  pico.hello(4,"");          // verbose level, hello msg
  show();                    // show
  blink();                   // RGB flashing
  return 0;
}
