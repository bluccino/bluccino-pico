// main.c - 02-picolo++
#include "pico/api.h"

static bool enable[4] = {1,1,1,1};
PI_us due = 0;

static void clicked(int i, int on)
{
  pico.log(1,"%sclick: @%d,%d", on?PI_G:PI_M,i,on);
  if (on) enable[i%4] = !enable[i%4];  // toggle LED @i
}

int main(void)
{
  for(;pico.console(0);pico.sleep(150*1000))
    pico.led(0,-1);

  pico.hello(4,"");
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
