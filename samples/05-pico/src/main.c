// main.c - 05-pico
#include "pico/api.h"

static pi_txt txt[] = {"red","green","blue"};
static pi_txt col[] = {_R_, _G_, _B_};
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

int main(void)
{
  for(;pico.console(0) && !pico.poll(-1); pico.sleep(250000))
    pico.led(1,-1); // blink until console ready

  pico.hello(4,""); // verbose level, hello msg
  pico.button(pressed); // init/setup button cb

  pi_us time = 0;
	for (int i=0;; i++, time += 500*1000) {
    pico.sleep(time-pico.usec());
    int k = index[2*mode + i % (mode==3?3:2)];
    pico.log(1,"%s%s",col[k],txt[k]);
    pico.led(-1,0);    // all LEDs off
    pico.led(2+k,1);   // one LED on
  }
  return 0;
}
