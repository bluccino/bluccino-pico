// led.h - LED pico API (supporting 4 LEDs)
#ifndef __PICO_LED_H__
#define __PICO_LED_H__

#include "pico/rtos.h"
#define LED0  DT_ALIAS(led0)
#define LED1  DT_ALIAS(led1)
#define LED2  DT_ALIAS(led2)
#define LED3  DT_ALIAS(led3)

typedef const struct gpio_dt_spec PI_led; // shorthand

static inline PI_led *_pi_led_ptr_(int i) // helper
{
  static PI_led ds[] = {
    #if DT_NODE_HAS_STATUS(LED0, okay)
      GPIO_DT_SPEC_GET(LED0, gpios),
    #endif
    #if DT_NODE_HAS_STATUS(LED1, okay)
      GPIO_DT_SPEC_GET(LED1, gpios),
    #endif
    #if DT_NODE_HAS_STATUS(LED2, okay)
      GPIO_DT_SPEC_GET(LED2, gpios),
    #endif
    #if DT_NODE_HAS_STATUS(LED3, okay)
      GPIO_DT_SPEC_GET(LED3, gpios),
    #endif
  };

  static int n = 0; // number of initialized LEDs
	for (; n<4; n++) {
	  if (!device_is_ready(ds[n].port)) {
	    printk("error %d: LED device not ready\n",ENODEV);
	  }
	  gpio_pin_configure_dt(ds+n, GPIO_OUTPUT_INACTIVE);
	}
  return (i<0 || i>n) ? NULL : ds + (i>0?i-1:0);
}

static inline void pi_led(int i, int val)
{
  PI_led *p = _pi_led_ptr_(i);
  if (i < 0)  // apply val to all LEDs
    for (int k=1; k<=4; k++) pi_led(k,val);
  else if (val < 0)  // led(i,-1) toggles LED @i
    { if (p) gpio_pin_toggle_dt(p); }
  else  // led(i,0) or led(i,1) clears/sets LED @i
    { if (p) gpio_pin_set_dt(p,val); }
}
#endif // __PICO_LED_H__
