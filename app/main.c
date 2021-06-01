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
#include <kernel/kernel.h>
#include <thunder/timer.h>

#define KEY_PS1 (9)
#define KEY_PS2 (10)

void key1_handler()
{
	printf("KEY1\r\n");
}
void key2_handler()
{
	printf("KEY2\r\n");
}

void tmr_handler()
{
	printf(".\r\n");
}

timer_dev_t* tmrt;
int main()
{
	printf("Compile at %s,%s\r\n",__DATE__,__TIME__);

	// gpio_irq_request(KEY_PS,GPIO_IRQ_EDGE_RISING,key_handler);
	irq_enable(gpio_irq_request(KEY_PS1,GPIO_IRQ_EDGE_FALLING,key1_handler));	
	irq_enable(gpio_irq_request(KEY_PS2,GPIO_IRQ_EDGE_RISING,key2_handler));	


	// tmrt = timer_open(1);
	// timer_set_period(tmrt,500);
	// timer_start(tmrt);
	// irq_enable( timer_irq_request(tmrt,tmr_handler));
	// while (1)
	// {
	// 	/* code */
	// }
	
}
