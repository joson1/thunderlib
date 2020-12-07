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
#include <thunder/interrput.h>
#include "zynq/zynq.h"
#include <kernel/thread.h>
#include <kernel/klist.h>

/*
*************************************************************************
*                              全局变量
*************************************************************************
*/
uint8_t flag1;
uint8_t flag2;

extern k_list_t thread_priority_table[THREAD_PRIORITY_MAX];

/*
*************************************************************************
*                      线程控制块 & STACK & 线程声明
*************************************************************************
*/


/* 定义线程控制块 */
thread_t flag1_thread;
thread_t flag2_thread;
thread_t flag3_thread;



ALIGN(4)
/* 定义线程栈 */
uint8_t flag1_thread_stack[512];
uint8_t flag2_thread_stack[512];
uint8_t flag3_thread_stack[512];

/* 线程声明 */
void flag1_thread_entry(void *p_arg);
void flag2_thread_entry(void *p_arg);
void flag3_thread_entry(void *p_arg);



int main()
{
	int a = 0;
	cmd_init();
	printf("Compile at %s,%s\r\n",__DATE__,__TIME__);
	// at24cxx_init();
	// scanf("%d",&a);
	gpio_pin_mode(0,GPIO_MODE_OUTPUT);
	gpio_pin_mode(1,GPIO_MODE_OUTPUT);
	gpio_pin_mode(2,GPIO_MODE_OUTPUT);
	// timer_setup(1,300,0,timer0_handler);

    ICDICFR[0] &= ~(TRIGGER_EDGE_RISING<<(0*2));
    ICDICFR[0] |=  (TRIGGER_EDGE_RISING<<(0*2));

    ICDISER[0] |= (1<<0);
	printf("swi init\r\n");

	system_scheduler_init();
	printf("system_scheduler_init init\r\n");
	
	/* 初始化线程 */
	thread_init( &flag1_thread,                 /* 线程控制块 */
	                flag1_thread_entry,               /* 线程入口地址 */
	                NULL,                          /* 线程形参 */
	                &flag1_thread_stack[0],        /* 线程栈起始地址 */
	                sizeof(flag1_thread_stack) );  /* 线程栈大小，单位为字节 */
	/* 将线程插入到就绪列表 */
	k_list_insert_before( &(thread_priority_table[0]),&(flag1_thread.tlist) );
	printf("thread_init init\r\n");
	
	/* 初始化线程 */
	thread_init( &flag2_thread,                 /* 线程控制块 */
	                flag2_thread_entry,               /* 线程入口地址 */
	                NULL,                          /* 线程形参 */
	                &flag2_thread_stack[0],        /* 线程栈起始地址 */
	                sizeof(flag2_thread_stack) );  /* 线程栈大小，单位为字节 */
	/* 将线程插入到就绪列表 */
	k_list_insert_before( &(thread_priority_table[1]),&(flag2_thread.tlist) );
	printf("thread_init init\r\n");


	/* 初始化线程 */
	thread_init( &flag3_thread,                 /* 线程控制块 */
	                flag3_thread_entry,               /* 线程入口地址 */
	                NULL,                          /* 线程形参 */
	                &flag3_thread_stack[0],        /* 线程栈起始地址 */
	                sizeof(flag3_thread_stack) );  /* 线程栈大小，单位为字节 */
	/* 将线程插入到就绪列表 */
	k_list_insert_before( &(thread_priority_table[2]),&(flag3_thread.tlist) );
	printf("thread_init init\r\n");
	
	/* 启动系统调度器 */
	printf("system_scheduler_start\r\n");

	system_scheduler_start(); 

	// irq_register(0,sft_interrput,TRIGGER_EDGE_RISING,NULL,NULL);
	// spi_flah_test();
// 	while(1)
// 	{
// 		// at24cxx_write(1,0x98);

// 		// printf("on\r\n");
// 		usleep(300000);
// 		// a = at24cxx_read(1);
// 		// printf("off:%lu\r\n",a);
// 		usleep(300000);


// 	}
//   return 0;
}

void delay (uint32_t count)
{
	for(; count!=0; count--);
}

/* 线程1 */
void flag1_thread_entry( void *p_arg )
{
	for( ;; )
	{
		delay(200);

		printf("thread1\r\n");
		/* 线程切换，这里是手动切换 */		
		schedule();
	}
}

/* 线程2 */
void flag2_thread_entry( void *p_arg )
{
	for( ;; )
	{
		delay(200);

		printf("thread2\r\n");

		/* 线程切换，这里是手动切换 */
		schedule();
	}
}

void flag3_thread_entry( void *p_arg )
{
	for( ;; )
	{
		delay(200);

		printf("thread3\r\n");

		/* 线程切换，这里是手动切换 */
		schedule();
	}
}


