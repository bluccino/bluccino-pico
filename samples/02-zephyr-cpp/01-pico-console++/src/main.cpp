// main.cpp - 01-pico-console++
#include "pico/api.h"
Pico pico;

int main(void)
{
  prt(PROJECT " (board %s)\n",CONFIG_BOARD);

	for (int i=0;;i++,pico.sleep(500))
    prt("number: %d\n",i);
}
