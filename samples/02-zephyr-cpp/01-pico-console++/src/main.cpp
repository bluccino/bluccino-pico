// main.cpp - 01-pico-console++
#include "pico/api.h"
Pico pico;

int main(void)
{
  pico.prt(PROJECT " (board %s)\n",CONFIG_BOARD);

	for (int i=0;;i++,pico.sleep(500))
    pico.prt("number: %s%d\n" PI_0,i%5?PI_G:PI_R,i);
}
