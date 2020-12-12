/*
 * @Author: your name
 * @Date: 2020-07-31 19:32:57
 * @LastEditTime: 2020-10-14 15:03:42
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\app\main.c
 */

#include <thunder/sleep.h>
#include <stdio.h>
#include <thunder/tty/tty.h>
#include <thunder/gpio.h>
#include "zynq/zynq.h"
#include <thunder/timer.h>
#include <thunder/pwm.h>
#include "zynq/axi-timer.h"

void timer_handler()
{
		printf("timer int\r\n");

}

int main()
{
	int a = 0;
	cmd_init();
	printf("Compile at %s,%s\r\n",__DATE__,__TIME__);
	gpio_pin_mode(0,GPIO_MODE_OUTPUT);
	gpio_pin_mode(1,GPIO_MODE_OUTPUT);
	struct pwm_dev* pwm0 = pwm_open(0);
	pwm_setup(pwm0,50,10000);
	// pwm_setup(0,20,10000);//channel0 duty 20% freq 100Hz
	// timer_setup(0,300,0,timer_handler);


	while(1)
	{

		// at24cxx_write(1,0x98);
		gpio_pin_set(1);
		gpio_pin_set(0);
		pwm_set_duty(pwm0,90);

		// printf("match_0_counter:0x%08X\r\n",TTC0->match_0_counter[0]);
		// printf("interval_counter:0x%08X\r\n",TTC0->interval_counter[0]);

		// printf("counter_value:0x%08X\r\n",TTC0->counter_value[0]);

  

		usleep(300000);
		gpio_pin_reset(1);
		pwm_set_duty(pwm0,10);
		gpio_pin_reset(0);
		// a = at24cxx_read(1);
		// printf("off:%lu\r\n",a);
		usleep(300000);


	}
  return 0;
}

