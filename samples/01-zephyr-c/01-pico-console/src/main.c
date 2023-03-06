// 01-pico-console
#include "pico/console.h"

int main(void)
{
  pi_console(true); // init/wait for console ready
  printk(PROJECT " (board %s)\n",CONFIG_BOARD);

	for (int i=0;;i++,k_msleep(500))
    printk("number: %d\n",i);
}
