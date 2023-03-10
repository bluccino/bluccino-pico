// main.c - 05-picolo
#include "pico/api.h"

static bool dir = 0;

static void pressed(int i, int on)
{
  if (pico.log(2,""))
    pico.print("button @%d %s\n",i,on?"pressed":"released");
  if (on) dir = !dir;  // change direction
}

void main(void)
{
  PI_txt txt[] = {"red","green","blue","green","red"};
  PI_txt col[] = {PI_R, PI_G, PI_B, PI_G, PI_R};
  int idx[] = {2,3,4,3,2};

  for(;pico.log(0,NULL);pico.sleep(250*1000))
    pico.led(1,-1); // blink until console ready

  pico.hello(4,""); // verbose level, hello msg
  pico.button(pressed); // init/setup button cb

	for (int i=0;;i++,pico.sleep(1000*1000))
  {
    int k = 2*dir + i%3;  // 0,1,2 or 2,3,4
    pico.log(1,"%s%s",col[k],txt[k]);
    pico.led(-1,0);       // all LEDs off
    pico.led(idx[k],1);   // one LED on
  }
}
