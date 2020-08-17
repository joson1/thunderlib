
# GPIO

```c

#include <thunder/gpio.h>

#include <stdio.h>
#include <thunder/tty/tty.h>
#include <thunder/gpio.h>

int main()
{
	cmd_init();
	gpio_pin_mode(0,GPIO_MODE_OUTPUT);
	gpio_pin_mode(1,GPIO_MODE_OUTPUT);

	while(1)
	{
		gpio_pin_set(1);
		gpio_pin_set(0);
		sleep(1);
		gpio_pin_reset(1);
		gpio_pin_reset(0);
		sleep(1);


	}
  return 0;
}


```