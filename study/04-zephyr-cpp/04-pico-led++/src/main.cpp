// main.cpp - 04-pico-led++
#include "pico/api.h"

int main(void)
{
  pico.prt(PI_R PROJECT " (board %s)\n" PI_0,CONFIG_BOARD);

	for (bool on=1; ; on=!on, pico.sleep(500*1000)) {
    pico.log(1,"%sLED flip",on?PI_G:PI_M);
  	pico.led(1,on); pico.led(2,!on);
    pico.led(3,!on); pico.led(4,on);
  }
}
