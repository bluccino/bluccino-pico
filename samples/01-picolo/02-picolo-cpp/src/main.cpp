// main.cpp - 02-picolo-c++
#include "pico/api.h"

Pico pico;   // Pico class instance
static bool enable[4] = {1,1,1,1};
PI_ms due = 0;

static void clicked(int i, int on)
{
  pico.log(1,"%sclick: @%d,%d", on?PI_G:PI_M,i,on);
  if (on) enable[i%4] = !enable[i%4];  // toggle LED @i
}

int main(void)
{
  pico.hello(4,"click any button");
  pico.button(clicked);  // setup button callback

	for (bool on=0;;on=!on,due+=500*1000)
  {
    pico.sleep(due-pico.us());
    for (int i=1;i<=4;i++) pico.led(i,enable[i%4]?on:0);
    if (due % 5000*1000 == 0)
      pico.log(1,PI_Y "click any button!");
  }
  return 0;
}