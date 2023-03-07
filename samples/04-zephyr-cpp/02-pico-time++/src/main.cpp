// main.cpp - 02-pico-time++
#include "pico/api.h"
Pico pico;  // create Pico class instance

int main(void)
{
  pico.prt(PI_R PROJECT " (%s)\n" PI_0,CONFIG_BOARD);

	for (PI_us time=0;;time+=1010*1000)
  {
    pico.sleep(time-pico.us());

    int min,s,ms,us;
    pico.now(&min,&s,& ms,&us);
    pico.prt(PI_Y"time: " PI_0 "[%d:%02d:%03d.%03d]\n",
             min,s,ms,us);
  }
}
