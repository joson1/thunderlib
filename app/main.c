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
#include <thunder/i2c.h>
#include "mtd/at24cxx.h"
#include <thunder/timer.h>
#include <thunder/spi.h>
#include "mtd/spi-flash.h"

int b = 0;

void timer0_handler()
{
	b = !b;
	if(b)
	{
		gpio_pin_set(0);
		
	}else
	{
		gpio_pin_reset(0);

	}
	
	printf("OK\r\n");
}

int main()
{
	int a = 0;
	cmd_init();
	printf("Compile at %s,%s\r\n",__DATE__,__TIME__);
	// at24cxx_init();
	scanf("%d",&a);
	printf("res:%d\r\n",a);
	gpio_pin_mode(0,GPIO_MODE_OUTPUT);
	gpio_pin_mode(1,GPIO_MODE_OUTPUT);
	gpio_pin_mode(2,GPIO_MODE_OUTPUT);
	timer_setup(1,300,0,timer0_handler);
	// spi_flah_test();
	while(1)
	{
		// at24cxx_write(1,0x98);

		// printf("on\r\n");
		usleep(300000);
		// a = at24cxx_read(1);
		// printf("off:%lu\r\n",a);
		usleep(300000);


	}
  return 0;
}
