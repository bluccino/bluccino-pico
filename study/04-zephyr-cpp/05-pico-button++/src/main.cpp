// main.cpp - 05-pico-button++
#include "pico/api.h"

static void clicked(int i, int on)
{
  pico.log(1,"%sclick: @%d,%d", on?PI_G:PI_M,i,on);
  if (on) pico.led(i,-1);  // toggle LED @i
}

int main(void)
{
  pico.hello(4,"click any button");
  pico.button(clicked);  // init buttons and setup callback
  return 0;
}
