# PWM

`c
#include <stdio.h>
#include <thunder/pwm.h>
#include <thunder/sleep.h>
#include <thunder/tty/tty.h>


int main()
{
	int a = 0;
	cmd_init();
	printf("Compile at %s,%s\r\n",__DATE__,__TIME__);

	struct pwm_dev* pwm0 = pwm_open(0);
	pwm_setup(pwm0,50,10000);


	while(1)
	{


		pwm_set_duty(pwm0,90);

		usleep(300000);
		gpio_pin_reset(1);
		pwm_set_duty(pwm0,10);

		usleep(300000);


	}
  return 0;
}


```