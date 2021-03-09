/*
 * @Author: your name
 * @Date: 2020-07-31 19:32:57
 * @LastEditTime: 2021-01-15 23:29:02
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\app\main.c
 */

#include <thunder/sleep.h>
#include <stdio.h>
#include <thunder/tty/tty.h>
#include <thunder/gpio.h>
#include <thunder/irq.h>
#include <thunder/dma.h>
#include <malloc.h>
#include <thunder/fb.h>

#define BUF ((uint16_t*)0XC0000000)


 
extern void lvgl_test();


int main()
{
	cmd_init();
	printf("Compile at %s,%s\r\n",__DATE__,__TIME__);
	
	lvgl_test();
	// printf("LCD:%d\r\n",*BUF);
	while (1)
	{
		/* code */
	}
	
}
