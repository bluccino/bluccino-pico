// main.c - 03-pico-led (blinky like sample)
#include "pico/log.h"
#include "pico/led.h"

int main(void)
{
  pi_hello(4,"");

	for (bool on=1; ; on=!on, pi_sleep(500)) {
    pi_log(1,"%sLED flip",on?PI_G:PI_M);
  	pi_led(1,on); pi_led(2,!on);
    pi_led(3,!on); pi_led(4,on);
  }
}
