// main.cpp - 03-pico-log++
#include "pico/api.h"

Pico pico;

int main(void)
{
  PI_ms time = 0;
  PI_txt color[] = {PI_G,PI_M,PI_Y,PI_C,""};

  pico.hello(2,"let's go");  // log level 2 max

	for (int i=0;;i++,time+=500)
  {
    pico.sleep(time-pi_ms());
    pico.log(i%5, "%shave a nice day!",color[i%5]);
  }
}
