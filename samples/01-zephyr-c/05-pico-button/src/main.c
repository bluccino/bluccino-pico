// main.c - 05-pico-button
#include "pico/log.h"
#include "pico/led.h"
#include "pico/button.h"

static void clicked(int i, int on)
{
  pi_log(1,"%sclick: @%d,%d", on?PI_G:PI_M,i,on);
  if (on) pi_led(i,-1);  // toggle LED @i
}

int main(void)
{
  pi_hello(4,"click any button");
  pi_button(clicked);  // init buttons and setup callback
  return 0;
}
