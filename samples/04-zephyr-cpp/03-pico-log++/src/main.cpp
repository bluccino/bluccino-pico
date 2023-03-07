// main.cpp - 03-pico-log++
#include "pico/api.h"
Pico pico;
PI_us time = 0;
PI_txt color[] = {PI_G,PI_M,PI_Y,PI_C,""};

int main(void)
{
  pico.hello(2,"let's go");  // log level 2 max

	for (int i=0;;i++,time+=500*1000)
  {
    pico.sleep(time-pico.us());
    pico.log(i%5,"%shave a nice day!",color[i%5]);
  }
}
