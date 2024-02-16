// main.c - 01-console-ready
#include "pico/api.h"

static PI_txt txt[] = {"red","green","blue"};
static PI_txt col[] = {_R_, _G_, _B_};

int main(void)
{
  int tab[20];
  int cnt = 0;

  int err = pico.console(0);           // get console status (no wait)
  for(int i=0; err; i++) {
    if (cnt < sizeof(tab)/sizeof(tab[0]))
       tab[cnt++] = err;

    pico.led(1,-1);                    // blink until console ready
    if (pico.poll(-1)) break;          // any butto press terminates waiting

    pico.sleep(250*1000);              // sleep 250ms

    err = pico.console(0);             // get console status (no wait)
  }

  pico.hello(4,""); // verbose level, hello msg
  pico.log(1,"");
  pico.print("return codes of pico.console():");
  for (int i=0; i < cnt; i++)
     pico.print(" %d",tab[i]);
  pico.print("\n");

  PI_us time = 0;
	for (int i=0;; i++, time += 500*1000) {
    pico.sleep(time-pico.us());
    int k = i % 3;
    pico.log(1,"%s%s",col[k],txt[k]);
    pico.led(-1,0);                    // all LEDs off
    pico.led(2+k,1);                   // LED @(2+k) on
  }
  return 0;
}
