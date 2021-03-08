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

int main()
{
	cmd_init();
	printf("Compile at %s,%s\r\n",__DATE__,__TIME__);
	
	struct fb_info* fb = fb_open(0);
	struct fb_fillrect rect = {
		.dx = 10,	/* screen-relative */
		.dy = 0,
		.width = 100,
		.height =50 ,
		.color = 0xBB,
	};

	fb->fbops->fb_fillrect(fb,&rect);
	// printf("LCD:%d\r\n",*BUF);
	while (1)
	{
		/* code */
	}
	
}
