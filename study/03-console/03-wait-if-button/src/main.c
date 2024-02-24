//==============================================================================
// main.c - 03-wait-if-button
//==============================================================================

#include "pico/pico.h"

int tab[20];                           // table to store return codes
int cnt = 0;

//==============================================================================
// - usage: wait_if_button(ms) // ms > 0
// - waits given ms-delay with blinking status LED, if no button is pressed
//   and contuous processing
// - if button is pressed and hold while dongle is pressed, execution enters
//   a permanent waiting mode with status blinking, which can be terminated
//   with any button press
//==============================================================================

static void wait_if_button(pico_ms ms)
{
  pico.log(0,NULL);                    // init console as non-blocking
  if (pico.poll(-1)) {                 // if initial button pressed
    while (pico.poll(-1)) pico.led(1,1);
    for (;pico.log(0,NULL) && !pico.poll(-1); pico.delay(250*1000))
      pico.led(1,-1);                  // blink until console ready
  }
  else  // if no button is initially pressed then wait for due initial delay
  {
    for (;pico.log(0,NULL) && !pico.poll(-1) && pico.usec() < 1000*ms;) {
      pico.led(1,-1);                   // blink until console ready
      pico.delay(250*1000);
    }
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
  wait_if_button(2000);      // wait for console ready or any button press
  pico.hello(4,"");          // verbose level, hello msg
  show();                    // show
  blink();                   // RGB flashing
  return 0;
}
