// main.cpp - 04-pico-led++
#include "pico/api.h"

Pico pi;

int main(void)
{
  prt(PROJECT " (board %s)\n",CONFIG_BOARD);

	for (bool on=1; ; on=!on, pi.sleep(500)) {
    log(1,"%sLED flip",on?PI_G:PI_M);
  	pi.led(1,on); pi.led(2,!on);
    pi.led(3,!on); pi.led(4,on);
  }
}
