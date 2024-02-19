# Sample 01-console-study

## Description

* The app starts with an initial flashing of the status LED and continues
  this mode by waiting for console readiness and logging the return codes
  of function pico.console(). Once the console is ready (by successfully
  connecting a terminal program to the USB interface) the app logs the
  recorded return codes and continues with an RGB blink sequence.

* If console readiness cannot be detected for some reason, the user has the
  possibility to terminate the initial waiting loop with a button press.

* note that in this startup mode none of the functions `pico.console`,
  `pico.hello`, `pico.print` or `pico.log` will block.

## Supported Boards

The sample provides in-situ support for the following board:
```
     1) nrf52840dongle_nrf52840  (Nordic 840 dongle)
```
There is also support for three other ports,
```
     2) nrf52dk_nrf52832         (Nordic 832 DK)
     3) nrf52840dk_nrf52840      (Nordic 840 DK)
     4) nucleo_l053r8            (ST Nucleo L053 DK)
```
allthough the interesting board to study is only the Nordic dongle, since for
the SEGGER-interface supported boards 2-4 the console function pico.console()
is a dummy function which always pretends to be rready.

To support additional boards proper files `<board>.overlay` and `<board>.conf`
have to be created and located in the `./boards` folder.

## Experimenting with a Dongle

### 1) Startup without terminal connection:

* make sure that the dongle-USB-interface is not connected with a terminal
* flash and startup dongle with sample software
* the status LED of the dongle should be blinking (as the terminal is not ready)
* after about 5s blinking connect a terminal (e.g. tio)
* the terminal shows the logs beginning with the hello message
* the sequence of ones after 'return codes ...' displays the return values
  of pico.log(0,NULL) function while waiting for conSole readiness
* the dongle terminates the status blink loop and enters the RGB blinking
  loop with related console logging
```
01-console-study -  (board nrf52840dongle_nrf52840, pico v0.1.3)
#1[0:00:00:000.519]   return codes of pico.console(): 1 1 1 1 1 1 1 1 1 1 1 ...
#1[0:00:00:001.373]   red
#1[0:00:00:500.122]   green
#1[0:00:01:000.153]   blue
```

### 2) Startup with an already established terminal connection:

* flash and startup dongle with sample software
* start a terminal program (e.g. tio) and connect with the dongle's USB
  interface
* unplug the dongle
* when the dongle is replugged the dongle skips the status blink loop imme-
  diately and enters the RGB blinking loop with related console logging
* the terminal shows the logs beginning with the hello message
* the text after 'return codes ...' shows a few ones of pico.log(0,NULL),
  which indicate that the software needed some time to recognize a ready
  terminal connection, even the terminal was already connected before software
  startup.


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
