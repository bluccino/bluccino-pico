# Sample 05-picolo

## Description

* The Picolo sample (`05-picolo`) uses all eight (main) functions of the Pico-API

* When the app waits for a terminal connection it flashes the status LED
  (mono-color LED on dongle, or LED 1 on a DK) to indicate that the program
  waits for a connected terminal connection.

* Once the terminal is connected, the log time is resetted, a hello message with
  zero time stamp will be logged to the console, showing the project name
  (`05-picolo`), the board identifier and the Poico-API version number.

* After the hello-message has been logged the following LED
  blink pattern is executed:

  1) on a dongle: RED-GREEN-BLUE-RED-GREEN-BLUE...

  2) on a DK: LED2-LED3-LED4-LED2-LED3-LED4

* Pressing button 1 changes to pattern RED-GREEN-RED-GREEN ... on the dongle
  or LED2-LED3-LED2-LED3... on a DK

* Pressing button 1 again changes to pattern GREEN-BLUE-GREEN-BLUE ... on the
  dongle or LED3-LED4-LED3-LED4... on a DK

* Pressing button 1 again changes to pattern BLUE-RED-BLUE-RED ... on the
  dongle or LED4-LED2-LED4-LED2... on a DK

* Pressing button 1 another time switches back to the initial pattern with
  RED-GREEN-BLUE... on the dongle or LED2-LED3-LED4... on a DK

* On a DK there are more options

  1) pressing button 2 selects pattern LED2-LED3-LED2-LED3...

  2) pressing button 3 selects pattern LED3-LED4-LED3-LED4...

  3) pressing button 4 selects pattern LED4-LED2-LED4-LED2...

* In addition: when a button is pressed or released all button states are polled
  an logged


## Supported Boards

The sample provides in-situ support for the following boards:
```
     1) nrf52dk_nrf52832         (Nordic 832 DK)
     2) nrf52840dk_nrf52840      (Nordic 840 DK)
     3) nrf52840dongle_nrf52840  (Nordic 840 dongle)
     4) nucleo_l053r8            (ST Nucleo L053 DK)
```
To support additional boards proper files `<board>.overlay` and `<board>.conf`
have to be created and located in the `./boards` folder.



## Building and Flashing

* Depending on the board an according environment variable for the board
  identifier has to be defined as follows:

```
  1) on a nRF52832 DK:     $ export BOARD=nrf52dk_nrf52832
  2) on a nRF52840 DK:     $ export BOARD=nrf52840dk_nrf52840
  3) on a nRF52840 dongle: $ export BOARD=nrf52840dongle_nrf52840
```  
* After that run `west` for building and flashing (make sure that the current
  directory matches the project directory

```
   $ west build -p     # west pristine build
   $ west flash        # flash binary
```

## Output

* This sample output is from a nRF52840 dongle. After powering up, the dongle
  waits for a terminal connection while it flashes the (mono-color) status LED.
* Once the terminal program establishes a connection the system time is reset to
  zero and the first line is logged by `pico.hello()`, showing project name,
  board identifier and Pico version.
* Initially the blink sequence is LED @2,@3,@4,@2,@3,@4,@1 ..., which
  translate to the pattern red,green,blue, red,green,blue (R-G-B-R-G-B...) on
  the dongle.
* after about 3 seconds the button is pressed, which invokes the 'pressed()'
  callback, causing polling and printing of all button states. At the same time
  the blink sequence is changed from R-G-B... to R-G-R-G...
* About 200 ms later the button is released, which causes again polling and
  printing of all button states

```
   #0[0:00:00:000.000] 05-picolo -  (board nrf52840dongle_nrf52840, pico v0.1.0)
   #1[0:00:00:014.282]   red
   #1[0:00:00:500.091]   green
   #1[0:00:01:000.091]   blue
   #1[0:00:01:500.091]   red
   #1[0:00:02:000.091]   green
   #1[0:00:02:500.091]   blue
   #2[0:00:02:981.476]     button states: 1 -1 -1 -1
   #1[0:00:03:000.091]   red
   #2[0:00:03:172.180]     button states: 0 -1 -1 -1
   #1[0:00:03:500.091]   green
   #1[0:00:04:000.091]   red
   #1[0:00:04:500.061]   green
   #1[0:00:05:000.122]   red
```

#Appendix

## The Sample Code

```
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
```


## Main Pico-API


```
  typedef struct PI_api {
    void (*print)(PI_txt fmt,...);
    void (*sleep)(PI_ms ms);
    PI_us (*us)(void);
    int (*log)(int lvl,PI_txt fmt,...);
    void (*hello)(int lvl,PI_txt txt);
    int (*led)(int i,int val);
    void (*button)(void(*cb)(int i,int on));
    int (*poll)(int i);
    // ...
  } PI_api;  // pico API
```

## Auxiliary Pico-API


```
  typedef struct PI_api {
    // ...
    PI_us (*clock)(PI_us us);
    void (*now)(int*h,int*min,int*s,int*ms,int*us);
    int (*console)(bool wait);
    void (*vprint)(PI_txt fmt, va_list ap);
    int (*vlog)(int lvl,PI_txt fmt, va_list ap);
  } PI_api;  // pico API
```
