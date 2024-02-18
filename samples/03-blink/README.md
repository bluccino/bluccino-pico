# Sample 03-blink

## Description

* sample application to demonstrate LED control
* demonstration of setting LEDs on/off or LED toggling
* demonstration of how to examine the number of suppoerted LEDs
* parameters for LED gpio pin control are retrieved from devicetree
* the sample needs to provide an overlay file for each supported board to
  contribute to the specific device tree source DTS
* in addition a binding (file: ./dts/bindings/blinker-parameters.yaml) has to be
  provided for a devicetree node with compatibility "blinker-parameters". This
  is done in the Zephyr RTOS kernel


## Supported Boards

The sample has support for the following boards:
```
     1) nrf52dk_nrf52832         (Nordic 832 DK)
     2) nrf52840dk_nrf52840      (Nordic 840 DK)
     3) nrf52840dongle_nrf52840  (Nordic 840 dongle)
     4) nucleo_l053r8            (ST Nucleo L053 DK)
```

## The Sample Code

```
// main.c - 03-blink
#include "pico/pico.c"

int main(void)
{
  pico.hello(4,"");
  int n = pico.led(-1,0);  // all LEDs off
  pico.log(1,"supported LEDs: %d",n);

  pico.led(2,1); pico.led(3,-1); pico.led(4,0);
	for (bool on=1; ; on=!on, pico.sleep(500*1000)) {
    pico.log(1,"%sLED flip",on?_G_:_M_);
    pico.led(-1,-1);
  }
  return 0;
}
```

By including "pico/pico.h" the app utilizes the pico standard api. It requires
to link the implementation file pico/pico.c.

The first line in `main()` sets the maximum log level (4) and prints a hello
message with simultaneous resetting of the clock time. Since the second argument
(a specific hello message) is empty, the app logs the standard hello message,

```
   #0[0:00:00:000.000] 03-blink -  (board nrf52dk_nrf52832, pico v0.1.2)
```  

showing sample name (`03-blink`), board indentifier (in the specific case
`nrf52dk_nrf52832`) and Pico version (here `v0.1.2`).

The second line `int n = pico.led(-1,0);` is used to examine the number of
supporeted LEDs, which is printed in the following log line.

It follows a demonstration of how to use function `pico.led()` to turn a single
LED on/off or to toggle it. It is implicitely assumed that a standard number of
4 LEDs are supported, which are all turned off previously. For the blink appli-
cation we will start with two dark LEDs (@1, @4) and two bright LEDs (@2, @3),
which will then subsequently toggled in an endless loop incorporating a loop
delay of 500ms. For a 2x2 matrix arrangement of the 4 LEDs this creates a
'diagonal flip effect'.

LED @1 is already initialized as off, so we leave it as it is. LED @2 has to be
turned on, for which we use `pico.led(2,-1);`. LED @3 needs also to be turned on,
and this time we use the toggle operation `pico.led(3,-1);` for demonstartion.
Finally, for demonstration, we turn LED @4 explicitely off with `pico.led(4,0);`,
even we know this operation is redundant (since LED @4 was already off).

What is left is the blink loop, where a sleep of 500 ms (`pico.sleep(500*1000)`)
is performed between each iteration. The call `pico.led(-1,-1);` in the loop
body is used to toggle all supported LEDs.     

Notably only one single API `pico.led()` function is needed to perform a variety
of different operations, which are summarized below:

```
    int n = pico.led(-1,0);  // all LEDs off,    return number of supported LEDs
    int n = pico.led(-1,1);  // all LEDs on,     return number of supported LEDs
    int n = pico.led(-1,-1); // all LEDs toggle, return number of supported LEDs
    pico.led(i,0)            // turn LED @i off
    pico.led(i,1)            // turn LED @i on
    pico.led(i,-1)           // toggle LED @i
```


## Hardware Access

The following steps need to be performed
   1) identify the (devicetree) `LED node` for the LED to be controlled
   2) define a node identifier for the LED node
   3) define an initialized GPIO spec
   4) check if the GPIO device has been initialized
   5) configure the GPIO pin
   6) control (in our case toggle) the GPIO pin

1) The LED we are using is represented by node /leds/led_0, which is labeled
   `led0:`

```
	leds {
		compatible = "gpio-leds";
		led0: led_0 {
			gpios = < &gpio0 0xd 0x1 >;
			label = "Green LED 0";
		};
    ...
	};
```

2) Thus we define a node identifer LED for node /leds/led_0 as follows

```
   #define LED  DT_NODELABEL(led0)
```

3) Now we can define (and statically initialize) a GPIO spec for the LED pin.

```
   static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED, gpios);
```

4) At runtime first thing to check is whether the GPIO device has initialized
   properly.

```
  if (!device_is_ready(led.port)) {
    printk("error %d: LED device not ready\n", -ENODEV);
    return;
  }
```

5) Configure the GPIO as active output

```
	 gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
```

6) Control (in our case toggle) the LED pin (periodically)

```
	for (;;k_msleep(500)) {
		gpio_pin_toggle_dt(&led);
	}
```
