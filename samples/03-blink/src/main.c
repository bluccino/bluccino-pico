// main.c - 03-blink
#include "pico/api.h"

void main(void)
{
  pico.hello(4,"");
  pico.led(2,-1); pico.led(3,-1);

	for (bool on=1; ; on=!on, pico.sleep(500*1000)) {
    pico.log(1,"%sLED flip",on?PI_G:PI_M);
    pico.led(-1,-1);
  }
}
