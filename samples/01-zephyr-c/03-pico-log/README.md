# Sample 03-pico-log




















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

```
   // 03-pico-console
   #include "pico/console.h"

   void main(void)
   {
     pi_console(true); // init/wait for console ready
     pi_prt(PROJECT " (board %s)\n",CONFIG_BOARD);

	   for (int i=0;;i++,k_msleep(500))
       pi_prt("number: %d\n",i);
   }
```


## The Console Pico API

```
   // pico/console.h - pico CONSOLE API
   #ifndef __PICO_CONSOLE__
   #define __PICO_CONSOLE__

   #include <zephyr/kernel.h>
   #include <zephyr/usb/usb_device.h>
   #include <zephyr/drivers/uart.h>

   #define pi_prt printk  // print function abstraction

   #ifdef CONFIG_USB_DEVICE_PRODUCT  // USB/COM
     static inline int pi_console(bool wait)
     {
       static uint32_t dtr = 0xff; // UART line ctrl DTR
       static const struct device *dev =
         DEVICE_DT_GET(DT_CHOSEN(zephyr_console));

       if (dtr == 0xff) {  // if not enabled
         if (usb_enable(NULL) || !device_is_ready(dev))
           return -ENODEV;
       }
       for (dtr=0; dtr == 0; k_msleep(250)) {
         uart_line_ctrl_get(dev, UART_LINE_CTRL_DTR, &dtr);
         if (!wait) return (dtr == 0);
       }
       return (dtr == 0);  // return 0 if console ready
     }
   #else                             // DKs, using Segger RTT
     static inline int pi_console(bool wait) { return 0; }
   #endif

   #endif // __PICO_CONSOLE__
```

## Conditional Macro Definition for `pi_prt` Symbol

```
   #ifdef CONFIG_USB_DEVICE_PRODUCT // USB dongle
     static inline int pi_console(void)
     {
        ...
     }
     #define pi_prt(fmt,...) do { \
       pi_console();  printk(fmt,##__VA_ARGS__); \
     } while (0)
   #else                 // DKs, using Segger RTT
     #define pi_prt printk
     static inline int pi_console(void) { return 0; }
   #endif
```


## Dongle Configuration

```
   # nrf52840dongle_nrf52840.conf

   #config USB/COM
   CONFIG_USB_DEVICE_STACK=y
   CONFIG_USB_DEVICE_PRODUCT="Dongle USB"
   CONFIG_USB_DEVICE_PID=0x00
   CONFIG_USB_DEVICE_VID=0x00

   #config console
   CONFIG_SERIAL=y
   CONFIG_CONSOLE=y
   CONFIG_UART_CONSOLE=y
   CONFIG_UART_LINE_CTRL=y
```

## 832/840 DK Configuration

```
# nrf52dk_nrf52832.conf / nrf52840dk_nrf52840.conf

# config Segger RTT
CONFIG_UART_CONSOLE=n
CONFIG_USE_SEGGER_RTT=y
CONFIG_RTT_CONSOLE=y
```


## Dongle Devicetree Overlay

```
// nrf52840dongle_nrf52840.overlay
// to enable logging via USB console

/ {
	  chosen {
		  zephyr,console = &cdc_acm_uart0;
	  };
  };

  &zephyr_udc0 {
	  cdc_acm_uart0: cdc_acm_uart0 {
		  compatible = "zephyr,cdc-acm-uart";
		  label = "CDC_ACM_0";
	  };
  };
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
