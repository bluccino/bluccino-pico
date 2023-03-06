// main.cpp 02-pico-time++
#include "pico/api.h"

Pico pico;

int main(void)
{
  prt(PROJECT " (board %s)\n",CONFIG_BOARD);

	for (PI_ms time=0;;time+=1010)
  {
    int min,s,ms,us;
    pico.sleep(time-pi_ms()-1);  // sleep 1 ms less
    while(pico.us() < 1000*time);
    pico.now(&min,&s,& ms,&us);
    prt("time: [%d:%02d:%03d.%03d]\n",min,s,ms,us);
  }
}
