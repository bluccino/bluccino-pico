// main.c - 03-poll
#include "pico/api.h"

void main(void)
{
  for(;pico.console(0);pico.sleep(250*1000))
    pico.led(0,-1);

	for (int i=0;;i++,pico.sleep(1000*1000))
  {
    pico.led(-1,0);    // all LEDs off
    pico.led(id,1); // one LED on
  }
}
