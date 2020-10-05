/*
 * @Author: your name
 * @Date: 2020-07-31 19:32:57
 * @LastEditTime: 2020-10-05 19:58:30
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\app\main.c
 */

#include <thunder/sleep.h>
#include <stdio.h>
#include <thunder/tty/tty.h>
#include <thunder/gpio.h>
#include <thunder/i2c.h>
#include "mtd/at24cxx.h"
#include <thunder/timer.h>


void timer0_handler()
{

	printf("OK\r\n");
}

int main()
{
	unsigned long a = 0;
	cmd_init();
	printf("Compile at %s,%s\r\n",__DATE__,__TIME__);
	// at24cxx_init();
	gpio_pin_mode(0,GPIO_MODE_OUTPUT);
	gpio_pin_mode(1,GPIO_MODE_OUTPUT);
	gpio_pin_mode(2,GPIO_MODE_OUTPUT);
	timer_setup(4,300,0,timer0_handler);
	while(1)
	{
		// at24cxx_write(1,0x98);
		gpio_pin_set(1);
		gpio_pin_set(0);
		gpio_pin_set(2);
		printf("on\r\n");
		usleep(300000);
		// a = at24cxx_read(1);
		gpio_pin_reset(1);
		gpio_pin_reset(0);
		gpio_pin_reset(2);
		printf("off:%lu\r\n",a);
		usleep(300000);


	}
  return 0;
}
