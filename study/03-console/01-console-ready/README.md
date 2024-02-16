# Sample 01-console-ready

## Description

* The sample starts with an initial flashing of the status LED and continues
  this mode by waiting for console readiness. Once the console is ready (by
  successfully connecting a terminal program to the USB interface) the app
  continues with an RGB blink sequence.

* During waiting for console readiness the app flashes the stus LED and uses
  pico.print() to inform about the return valus from pico.console() function.

* If console readiness cannot be detected for some reason, the user has the
  possibility to terminate the initial waiting loop with a button press.


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
