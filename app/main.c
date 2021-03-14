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

#include "drivers/iio/ad9361/AD9361/ad9361.h"
#include "adconf.h"


#define BUF ((uint16_t*)0XC0000000)

struct ad9361_rf_phy *ad9361_phy;

 

/* 线程1 */
void flag1_thread_entry( void *p_arg )
{
	int aa = 1;
	float af = 1;
	uint32_t level;
	for( ;; )
	{
		MOVETO(1,0);

		printf(YELLOW"thread1:%d\taf:%.2f\r\n",aa,af);
		aa++;
		af+=0.1;

		sys_delay(10);

		/* 线程切换，这里是手动切换 */		
		// schedule();
	}
}

/* 线程2 */
void flag2_thread_entry( void *p_arg )
{
	int aa = 1;
	float af = 1;
	uint32_t level;
	for( ;; )
	{
		MOVETO(2,0);

		printf(BLUE"thread2:%d\taf:%.2f\r\n",aa,af);
		aa++;
		af+=0.01;

		sys_delay(20);

		/* 线程切换，这里是手动切换 */		
		// schedule();
	}
}

void flag2_1_thread_entry( void *p_arg )
{
	int cc =3;
	float af = 30.0;
	while(1){
		cc++;
		af+=0.05;
		MOVETO(3,0);
		printf(GREEN"thread3:%d\taf:%.2f\r\n",cc,af);
		delay(200);
		sys_delay(20);
	}
}


int main()
{
	printf("Compile at %s,%s\r\n",__DATE__,__TIME__);

	
	thread_t* pthread1 = thread_create(
		"thread1",
		flag1_thread_entry,
		NULL,
		NULL,
		10240,
		1
	);

	thread_t* pthread2 = thread_create(
		"thread2",
		flag2_thread_entry,
		NULL,
		NULL,
		10240,
		1
	);

	
}
