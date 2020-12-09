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


int main()
{
	int a = 0;
	cmd_init();
	printf("Compile at %s,%s\r\n",__DATE__,__TIME__);
	gpio_pin_mode(0,GPIO_MODE_OUTPUT);
	gpio_pin_mode(1,GPIO_MODE_OUTPUT);

	while(1)
	{
		// at24cxx_write(1,0x98);
		gpio_pin_set(1);
		gpio_pin_set(0);
		// printf("on\r\n");
		usleep(300000);
		gpio_pin_reset(1);
		gpio_pin_reset(0);
		// a = at24cxx_read(1);
		// printf("off:%lu\r\n",a);
		usleep(300000);


	}
  return 0;
}

