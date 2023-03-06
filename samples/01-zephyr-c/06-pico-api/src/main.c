// main.c - 06-pico-api
#include "pico/api.h"

static bool enable[4] = {1,1,1,1};

static void clicked(int i, int on)
{
  log(1,"%sclick: @%d,%d", on?PI_G:PI_M,i,on);
  if (on) enable[i%4] = !enable[i%4];  // toggle LED @i
}

static void now(void)  // print current time
{
  int min,s,ms,us;
  pico.now(&min,&s,& ms,&us);
  prt("time: [%d:%02d:%03d.%03d]\n",min,s,ms,us);
}

static void wait(PI_us due) // wait until due
{
  pico.sleep(due-pico.ms()-1);  // sleep 1 ms less
  while(pico.us() < 1000*due);
}

static void leds(bool on)   // set enabled LEDs
{
  for (int i=1;i<=4;i++) pico.led(i,enable[i%4]?on:0);
}

void main(void)
{
  pico.hello(4,"click any button");
  pico.button(clicked);  // setup button callback

  PI_ms time = 0;
	for (bool on=0;;time+=500,on=!on)
  {
    wait(time);  // wait until die
    now();       // print current time
    leds(on);    // toggle enabled LEDs
  }
}
