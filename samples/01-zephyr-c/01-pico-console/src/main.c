// 01-pico-console
#include "pico/console.h"

int main(void)
{
  pi_console(true); // init/wait for console ready
  pi_prt(PI_R PROJECT " (board %s)\n" PI_0,CONFIG_BOARD);

	for (int i=0;;i++,k_msleep(500))
    pi_prt("number: %s%d\n" PI_0,i%5?PI_G:PI_R,i);
}
