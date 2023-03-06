// 02-pico-time
#include "pico/console.h"
#include "pico/time.h"

int main(void)
{
  pi_console(true);
  pi_prt(PI_R PROJECT " (%s)\n" PI_0,CONFIG_BOARD);

	for (PI_ms time=0;;time+=1010)
  {
    int min,s,ms,us;
    pi_sleep(time-pi_ms()-1);  // sleep 1 ms less
    while(pi_us() < 1000*time);
    pi_now(&min,&s,& ms,&us);
    pi_prt(PI_Y "time: " PI_0 "[%d:%02d:%03d.%03d]\n",
           min,s,ms,us);
  }
}
