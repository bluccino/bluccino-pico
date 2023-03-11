// button.h - BUTTON pico API
#ifndef __PICO_BUTTON_H__
#define __PICO_BUTTON_H__

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#include "pico/console.h"
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#define BUTTON0  DT_ALIAS(sw0)  // DT node ID for button @1
#define BUTTON1  DT_ALIAS(sw1)  // DT node ID for button @2
#define BUTTON2  DT_ALIAS(sw2)  // DT node ID for button @3
#define BUTTON3  DT_ALIAS(sw3)  // DT node ID for button @4

typedef struct {
  int ix;                       // button index
  const struct gpio_dt_spec ds; // button pin device spec
  struct gpio_callback context; // to assign IRS
  void (*cb)(int i, int on);    // application callback
} PI_button;

static inline void _button_isr_(const struct device *dev,
  struct gpio_callback *ctx, uint32_t pins)
{
  PI_button *p = CONTAINER_OF(ctx,PI_button,context);
int on=0;pi_print("button @%d: %d (%p)\n",p->ix,on,p->cb);
return;
  //int on = gpio_pin_get_dt(&p->ds);
  if (p->cb) p->cb(p->ix,on);
}

static inline PI_button *
  _pi_button_ptr_(int i,void (*cb)(int i,int on))
{
  static PI_button but[] = {
    #if DT_NODE_HAS_STATUS(BUTTON0, okay)
      {.ix=1, .ds=GPIO_DT_SPEC_GET_OR(BUTTON0,gpios,{0})},
    #endif
    #if DT_NODE_HAS_STATUS(BUTTON1, okay)
      {.ix=2, .ds=GPIO_DT_SPEC_GET_OR(BUTTON1,gpios,{0})},
    #endif
    #if DT_NODE_HAS_STATUS(BUTTON2, okay)
      {.ix=3, .ds=GPIO_DT_SPEC_GET_OR(BUTTON2,gpios,{0})},
    #endif
    #if DT_NODE_HAS_STATUS(BUTTON3, okay)
      {.ix=4, .ds=GPIO_DT_SPEC_GET_OR(BUTTON3,gpios,{0})},
    #endif
  };

  static int n = 0; // number of initialized LEDs
	for (; n < sizeof(but)/sizeof(but[0]); n++) {
    PI_button *p = but + n;
    if (!device_is_ready(p->ds.port)) {
      printk("error %d: BUTTON device not ready\n",-ENODEV);
      continue;
    }
pi_print("set button @%d callback (%d)\n",n+1,p-but);
    p->cb = cb;  // store application callback
    gpio_pin_configure_dt(&p->ds,GPIO_INPUT);
    gpio_pin_interrupt_configure_dt(&p->ds,GPIO_INT_EDGE_BOTH);
    gpio_init_callback(&p->context, _button_isr_, BIT(p->ds.pin));
    gpio_add_callback(p->ds.port, &p->context);
	}
  return (i<1 || i>n) ? NULL : but + (i-1);
}

static inline void pi_button(void (*cb)(int i,int on))
{
//>>>>>>>>>>>>>>>>>>>>>>>
cb(88,66);
//<<<<<<<<<<<<<<<<<<<<<<<
  _pi_button_ptr_(0,cb);
}

static inline int pi_poll(int i)
{
  PI_button *p = _pi_button_ptr_(i,NULL);
  return gpio_pin_get_dt(&p->ds);
}

#endif // __PICO_BUTTON_H__
