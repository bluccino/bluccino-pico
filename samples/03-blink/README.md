# Sample 03-blink

## Description

* sample application to demonstrate cntrol of a GPIO pin on very deep level
* control is implemented by utilizing `GPIO` driver API
* parameters for gpio pin control are retrieved from devicetree
* the sample needs to provide an overlay file for each support to contribute
  to the specific DTS
* in addition a binding (file: ./dts/bindings/blinker-parameters.yaml) has to be
  provided for a devicetree node with compatibility "blinker-parameters"


## Supported Boards

The sample has support for the following boards:
```
     1) nrf52dk_nrf52832         (Nordic 832 DK)
     2) nrf52840dk_nrf52840      (Nordic 840 DK)
     3) nrf52840dongle_nrf52840  (Nordic 840 dongle)
     4) nucleo_l053r8            (ST Nucleo L053 DK)
```

## The Sample Code

### Mini LED API
```
   // led.h - mini LED API
   #ifndef __LED_H__
   #define __LED_H__

   #include <zephyr/kernel.h>
   #include <zephyr/drivers/gpio.h>

   #define LED  DT_NODELABEL(led0)
   typedef const struct gpio_dt_spec led_t; // shorthand

   static inline led_t *led_init(void)
   {
     static led_t ds = GPIO_DT_SPEC_GET(LED, gpios);

     if (!device_is_ready(ds.port)) {
       printk("error %d: LED device not ready\n",ENODEV);
       return NULL;
     }

     gpio_pin_configure_dt(&ds, GPIO_OUTPUT_ACTIVE);
     return &ds;
   }

   static inline void led_toggle(led_t *led)
   {
     gpio_pin_toggle_dt(led);
   }

   #endif // __LED_H__
```

### Main Program

```
   // main.c - 03-blinker
   #include "led0.h"

   void main(void)
   {
     printk("03-blinker (board %s)\n",CONFIG_BOARD);
     led_t *led = led_init();

	  for (;led;k_msleep(500))
  	    led_toggle(led);
   }
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
