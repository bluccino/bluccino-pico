// main.c - 03-blink
#include "pico/api.h"

int main(void)
{
  pico.hello(4,"");
  int n = pico.led(-1,0);  // all LEDs off
  pico.log(1,"supported LEDs: %d",n);

  pico.led(2,1); pico.led(3,-1); pico.led(4,0);
	for (bool on=1; ; on=!on, pico.sleep(500*1000)) {
    pico.log(1,"%sLED flip",on?_G_:_M_);
    pico.led(-1,-1);
  }
  return 0;
}
