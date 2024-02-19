// main.c - 02-log
#include "pico/api.h"

int main(void)
{
  pico_us time = 0;
  pico_txt color[] = {_G_,_M_,_Y_,_C_,""};

  pico.hello(2,"let's go");  // log level 2 max

	for (int i=0;;i++,time+=500*1000) {
    pico.delay(time-pico.usec());
    pico.log(i%5, "%shave a nice day!",color[i%5]);
  }
  return 0;
}
