// main.c - 05-pico
#include "pico/api.h"

static pico_txt txt[] = {"red","green","blue"};
static pico_txt col[] = {_R_, _G_, _B_};
static int index[]  = {0,1, 1,2, 2,0, 0,1,2};
static int mode = 3;

static void pressed(int i, int on)
{
  if (!pico.log(2,"")) {
    pico.print("button states:");
    for (int k=1; k <= 4; k++) {
      int state = pico.poll(k);
      pico.print(" %0d",state);
    }
    pico.print("\n");
  }
  if (on && i == 1) mode = (mode+1) % 4;
    else if (on) mode = (i-2) % 4;
}

int main(void)
{
  for(;pico.log(0,NULL) && !pico.poll(-1); pico.delay(250000))
    pico.led(1,-1); // blink until console ready

  pico.hello(4,""); // verbose level, hello msg
  pico.button(pressed); // init/setup button cb

  pico_us time = 0;
	for (int i=0;; i++, time += 500*1000) {
    pico.delay(time-pico.usec());
    int k = index[2*mode + i % (mode==3?3:2)];
    pico.log(1,"%s%s",col[k],txt[k]);
    pico.led(-1,0);    // all LEDs off
    pico.led(2+k,1);   // one LED on
  }
  return 0;
}
