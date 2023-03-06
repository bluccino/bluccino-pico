// main.c - 07-picolo
#include "pico/api.h"

static bool enable[4] = {1,1,1,1};
static PI_ms time = 0;

static void clicked(int i, int on)
{
  pico.log(1,"%sclick: @%d,%d", on?PI_G:PI_M,i,on);
  if (on) enable[i%4] = !enable[i%4];  // toggle LED @i
}

int main(void)
{
  pico.hello(4,"click any button");
  pico.button(clicked);  // setup button callback

	for (bool on=0;;on=!on,time+=500)
  {
    while(pico.ms() < time);  // wait until due
    for (int i=1;i<=4;i++) pico.led(i,enable[i%4]?on:0);
  }
  return 0;
}
