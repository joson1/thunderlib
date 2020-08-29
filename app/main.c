/*
 * @Author: your name
 * @Date: 2020-07-31 19:32:57
 * @LastEditTime: 2020-08-29 22:08:04
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\app\main.c
 */

#include <thunder/sleep.h>
#include <stdio.h>
#include <thunder/tty/tty.h>
#include <thunder/gpio.h>
#include <zynq/zynq.h>
#include <thunder/i2c.h>
#include "mtd/at24cxx.h"


int main()
{
	unsigned long a = 0;
	cmd_init();
	printf("Compile at %s,%s\r\n",__DATE__,__TIME__);
	at24cxx_init();
	gpio_pin_mode(0,GPIO_MODE_OUTPUT);
	gpio_pin_mode(1,GPIO_MODE_OUTPUT);
	
	while(1)
	{
		at24cxx_write(1,0x62);
		gpio_pin_set(1);
		gpio_pin_set(0);
		printf("on\r\n");
		usleep(300000);
		a = at24cxx_read(1);
		gpio_pin_reset(1);
		gpio_pin_reset(0);
		printf("off:%lu\r\n",a);
		usleep(300000);


	}
  return 0;
}
