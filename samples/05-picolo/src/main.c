// main.c - 05-picolo
#include "pico/api.h"

static PI_txt txt[] = {"red","green","blue"};
static PI_txt col[] = {PI_R, PI_G, PI_B};
static int index[]  = {0,1, 1,2, 2,0, 0,1,2};
static int mode = 3;

static void pressed(int i, int on)
{
  if (!pico.log(2,"")) {
    pico.print("button states:");
    for (int i=1; i <= 4; i++) {
      int state = pico.poll(i);
      pico.print(" %0d",state);
    }
    pico.print("\n");
  }
  if (on && i == 1) mode = (mode+1) % 4;
    else if (on) mode = (i-2) % 4;
}

void main(void)
{
  for(;pico.log(0,NULL);pico.sleep(250*1000))
    pico.led(1,-1); // blink until console ready

  pico.hello(4,""); // verbose level, hello msg
  pico.button(pressed); // init/setup button cb

  PI_us time = 0;
	for (int i=0;; i++, time += 500*1000)
  {
    pico.sleep(time-pico.us());
    int k = index[2*mode + i % (mode==3?3:2)];
    pico.log(1,"%s%s",col[k],txt[k]);
    pico.led(-1,0);    // all LEDs off
    pico.led(2+k,1);   // one LED on
  }
}
