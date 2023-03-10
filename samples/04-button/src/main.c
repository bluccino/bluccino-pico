// main.c - 04-button
#include "pico/api.h"

static void clicked(int i, int on)
{
  pico.log(1,"%sclick: @%d,%d", on?PI_G:PI_M,i,on);
  if (on) pico.led(i,-1);  // toggle LED @i
}

void main(void)
{
  pico.hello(4,"click any button");
  pico.button(clicked);  // init buttons and setup callback
}
