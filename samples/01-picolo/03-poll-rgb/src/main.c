// main.c - 03-poll-rgb
#include "pico/api.h"

void main(void)
{
  PI_txt txt[] = {"red","green","blue"};
  PI_txt col[] = {PI_R, PI_G, PI_B};

  for(;pico.console(0);pico.sleep(250*1000))
    pico.led(0,-1);

  pico.hello(4,"");
	for (int i=0;;i++,pico.sleep(1000*1000))
  {
    pico.log(1,"%s%s",col[i%3],txt[i%3]);
    pico.led(-1,0);    // all LEDs off
    pico.led(2+i%3,1); // one LED on
  }
}
