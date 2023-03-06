# Pico

The Pico API provides "eight treasures" as basic interactions with an embedded hardware. The API is solely based on a suite of headerfiles.


![pico](./doc/image/pico.png)

## Pico Suite

 We call this “goodie” the Pico Suite. Each of these header files provides simple access to some hardware resource.
•	The Pico Console API (#include “pico/console.h”) declares pi_prt(), an abstraction of printk(), and provides an inline function pi_console() to enable a USB console for logging. This allows logging from a dongle to a USB connected terminal.

•	The Pico Time API (#include “pico/time.h”) defines types PI_us and PI_ms to deal with microseconds and milliseconds. It further declares pi_sleep() as an abstraction of k_msleep() and provides inline func¬tions pi_us() and pi_ms() to read microsecond or millisecond based realtime. Finally with function  pi_set_us() the realtime clock can be pre-set to a given value.

•	The Pico LED API (#include “pico/led.h”) declares inline function pi_led, which allows to turn on/off, or to toggle up to four LEDs (if provided by the board).

•	The Pico Button API (#include “pico/button.h”) provides inline function pi_button() to initialize up to four buttons (if provided by the hardware) and assign it with a button callback. 
All Pico APIs are provided by tiny, self-contained header files without related C-implementation files. They unburden the application from Zephyr details. Since the Pico Suite is so tiny, it can be easily ported to other real time operating systems like Free-RTOS, even CubeMX or other. The prefix “pi_” of the pico functions stands for “pico”. 
The Zephyr based Pico Suite is a key reference for the application of important Zephyr API functions. Together with Kconfig and devicetree it allows to use important basic control functions of over hundred hardware boards with an identical and compact code. Let us study some sample applications utilizing the Pico Suite.

## A Sample

The following sample utilizes all Pico API functions for demonstration.

```
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

```
