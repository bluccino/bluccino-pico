// 01-numbers
#include "pico/api.h"

void main(void)
{
  pico.console(true); // init/wait for console ready
  pico.prt(PI_R PROJECT " (board %s)\n" PI_0,CONFIG_BOARD);

	for (int i=0;;i++,pico.sleep(500*1000))
    pico.prt("number: %s%d\n" PI_0,i%5?PI_G:PI_R,i);
}
