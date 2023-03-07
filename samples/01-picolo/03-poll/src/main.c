// main.c - 03-poll
#include "pico/console.h"
#include "pico/api.h"

void main(void)
{
/*
  for(;pico.console(0);pico.sleep(250*1000))
    pico.led(0,-1);
*/
pi_console(true); pico.hello(4,"");

	for (int i=0;;i++,pico.sleep(1000*1000))
  {
    pico.led(-1,0);    // all LEDs off
pico.sleep(1000*1000);
int id = 2+(i%3);
pico.log(1,"LED %d on",id);
    pico.led(id,1); // one LED on
  }
}
