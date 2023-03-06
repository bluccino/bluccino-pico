// 03-pico-log
#include "pico/log.h"

int main(void)
{
  PI_ms time = 0;
  PI_txt color[] = {PI_G,PI_M,PI_Y,PI_C,""};

  pi_hello(2,"let's go");  // log level 2 max

	for (int i=0;;i++,time+=500)
  {
    pi_sleep(time-pi_ms());
    pi_log(i%5, "%shave a nice day!",color[i%5]);
  }
}
