// button.h - BUTTON pico API
#ifndef __PICO_BUTTON_H__
#define __PICO_BUTTON_H__

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#define BUTTON0  DT_ALIAS(sw0)  // DT node ID for button @1
#define BUTTON1  DT_ALIAS(sw1)  // DT node ID for button @2
#define BUTTON2  DT_ALIAS(sw2)  // DT node ID for button @3
#define BUTTON3  DT_ALIAS(sw3)  // DT node ID for button @4

typedef struct {
  int ix;                       // button index
  const struct gpio_dt_spec ds; // button pin device spec
  struct gpio_callback context; // to assign IRS
  void (*cb)(int i, int on);    // application callback
} button_t;

static inline void _button_isr_(const struct device *dev,
  struct gpio_callback *ctx, uint32_t pins)
{
  button_t *p = CONTAINER_OF(ctx,button_t,context);
  int on = gpio_pin_get_dt(&p->ds);
  if (p->cb) p->cb(p->ix,on);
}

static inline int pi_button(void (*cb)(int i,int on))
{
  static button_t but[] = {
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

  int n = sizeof(but) / sizeof((but)[0]);
  for (int i=0; i < n; i++) {
    button_t *p = &but[i];
    if (!device_is_ready(p->ds.port)) {
      printk("error %d: BUTTON device not ready\n",-ENODEV);
      return -ENODEV;
    }
    p->cb = cb;  // store application callback
    gpio_pin_configure_dt(&p->ds,GPIO_INPUT);
    gpio_pin_interrupt_configure_dt(&p->ds,GPIO_INT_EDGE_BOTH);
    gpio_init_callback(&p->context, _button_isr_, BIT(p->ds.pin));
    gpio_add_callback(p->ds.port, &p->context);
  }
  return 0;
}

#endif // __PICO_BUTTON_H__
