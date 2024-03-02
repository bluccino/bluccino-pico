// led.h - LED pico API (supporting 4 LEDs)
#ifndef __PICO_LED_H__
#define __PICO_LED_H__

#if !defined(__PICO_RTOS_H__)
  #include "pico/rtos.h"
#endif

#define PICO_LED0  DT_ALIAS(led0)
#define PICO_LED1  DT_ALIAS(led1)
#define PICO_LED2  DT_ALIAS(led2)
#define PICO_LED3  DT_ALIAS(led3)

static inline struct gpio_dt_spec *_pico_led_ptr_(int i) // helper
{
  static struct gpio_dt_spec ds[] = {
    #if DT_NODE_HAS_STATUS(PICO_LED0, okay)
      GPIO_DT_SPEC_GET(PICO_LED0, gpios),
    #endif
    #if DT_NODE_HAS_STATUS(PICO_LED1, okay)
      GPIO_DT_SPEC_GET(PICO_LED1, gpios),
    #endif
    #if DT_NODE_HAS_STATUS(PICO_LED2, okay)
      GPIO_DT_SPEC_GET(PICO_LED2, gpios),
    #endif
    #if DT_NODE_HAS_STATUS(PICO_LED3, okay)
      GPIO_DT_SPEC_GET(PICO_LED3, gpios),
    #endif
  };

  static int n = 0; // number of initialized LEDs
	for (; n < (int)(sizeof(ds)/sizeof(ds[0])); n++) {
	  if (!device_is_ready(ds[n].port)) {
	    printk("error %d: LED device not ready\n",ENODEV);
            continue;
	  }
	  gpio_pin_configure_dt(ds+n, GPIO_OUTPUT_INACTIVE);
	}
  return (i<0 || i>n) ? NULL : ds + (i>0?i-1:0);
}

//==============================================================================
// set one or all LEDs on/off or toggle one or all LEDs
// - usage: err = led(i,on);  // on=1/0: set LED @i on/off, on=-1: toggle LED @i
//          n = led(-1,on);   // on/off/toggle all LEDs, return number
//==============================================================================

static inline int pico_led(int i, int val)
{
  struct gpio_dt_spec *p = _pico_led_ptr_(i);
  if (i < 0) { // apply val to all LEDs
    for (int err=0, n=0; !err;) {
      err = pico_led(++n,val);
      if (err) return n==1 ? -2 : n-1;
    }
  }
  else if (val < 0)  // led(i,-1) toggles LED @i
    { if (p) gpio_pin_toggle_dt(p); }
  else  // led(i,0) or led(i,1) clears/sets LED @i
    { if (p) gpio_pin_set_dt(p,val); }
  return (!p) ? -1 : 0;
}
#endif // __PICO_LED_H__
