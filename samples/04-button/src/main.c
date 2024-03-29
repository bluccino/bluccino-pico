// main.c - 04-button
#include "pico/api.h"

static void clicked(int i, int on)
{
  pico.log(1,"%sclick: @%d,%d", on?_G_:_M_,i,on);
  if (on) pico.led(i,-1);  // toggle LED @i
}

int main(void)
{
  pico.hello(4,"click any button");
  int n = pico.button(clicked);  // init buttons and setup callback
  pico.log(1,"supported buttons: %d",n);
  return 0;
}
