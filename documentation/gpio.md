
# GPIO

```c

#include <thunder/gpio.h>

int main()
{
  gpio_pin_mode(0,GPIO_MODE_OUTPUT);
  gpio_pin_set(0);
  gpio_pin_reset(0);

  return 0;
}


```