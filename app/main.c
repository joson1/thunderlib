/*
 * @Author: your name
 * @Date: 2020-07-31 19:32:57
 * @LastEditTime: 2020-08-24 14:07:19
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\app\main.c
 */

#include "zynq/sleep.h"
#include <stdio.h>
#include <thunder/tty/tty.h>
#include <thunder/gpio.h>
#include <zynq/zynq.h>

int main()
{
	int a = 0;
	cmd_init();
	printf("input:%d\r\n",a);
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
