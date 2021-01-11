/*
 * @Author: your name
 * @Date: 2020-07-31 19:32:57
 * @LastEditTime: 2021-01-11 18:50:37
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\app\main.c
 */

#include <thunder/sleep.h>
#include <stdio.h>
#include <thunder/tty/tty.h>
#include <thunder/gpio.h>
#include "zynq/zynq.h"
#include <kernel/thread.h>
#include <kernel/klist.h>
#include "zynq/xtime_l.h"


/*
*************************************************************************
*                              全局变量
*************************************************************************
*/
uint8_t flag1;
uint8_t flag2;

uint8_t isReady = 0;
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
extern uint32_t cpu_interrupt_disable();
extern void cpu_interrupt_enable(uint32_t level);


ALIGN(4)
/* 定义线程栈 */
uint8_t flag1_thread_stack[512];
uint8_t flag2_thread_stack[512];
uint8_t flag3_thread_stack[512];

/* 线程声明 */
void flag1_thread_entry(void *p_arg);
void flag2_thread_entry(void *p_arg);
void flag3_thread_entry(void *p_arg);

#define GT_CON 	*((unsigned int*)0xF8F00208)
#define GT_CMPL 	*((unsigned int*)0xF8F00210)
#define GT_CMPH 	*((unsigned int*)0xf8f00214)

#define GT_INTS *((unsigned int*)0xF8F0020C)
#define OS_TIMER_SLICE_MS 1

#define COUNTS_PER_USECOND  (XPAR_CPU_CORTEXA9_CORE_CLOCK_FREQ_HZ / (2U*1000000U))
#define GT_CON_REG0 *((unsigned int *)(0xF8F00200))
#define GT_CON_REG1 *((unsigned int *)(0xf8f00204))

extern void sys_tick_handler();
void gtimer()
{

//   XTime tEnd, tCur;

//   XTime_GetTime(&tCur);
// 	tEnd = tCur + (((XTime) OS_TIMER_SLICE_MS*1000) * COUNTS_PER_USECOND);
	// if(isReady)
	// {
	// 	sys_tick_handler();
	// 	printf(".");
	// }else{
	// 	printf("gtime\r\n");

	// }

	sys_tick_handler();
		// printf("gtime\r\n");

	GT_CON_REG0 = 0;
	GT_CON_REG1 = 0;
	GT_INTS = 1;	


}

int main()
{
	int a = 0;
	uint32_t level = cpu_interrupt_disable();
	cmd_init();
	printf("Compile at %s,%s\r\n",__DATE__,__TIME__);
	gpio_pin_mode(0,GPIO_MODE_OUTPUT);
	gpio_pin_mode(1,GPIO_MODE_OUTPUT);
	gpio_pin_mode(2,GPIO_MODE_OUTPUT);
	// timer_setup(1,300,0,timer0_handler);

    ICDICFR[0] &= ~(TRIGGER_EDGE_RISING<<(0*2));
    ICDICFR[0] |=  (TRIGGER_EDGE_RISING<<(0*2));

    ICDISER[0] |= (1<<0);

	
	// GT_CMPL=166666667;
	GT_CON_REG0 = 0;
	GT_CON_REG1 = 0;
	GT_CON = 0;
	uint64_t tmp = (((uint64_t) OS_TIMER_SLICE_MS*1000) * COUNTS_PER_USECOND);
	uint32_t tmpl = tmp;
	GT_CMPL = tmpl;
	GT_CMPH = tmp>>32;

	GT_CON |= ((1<<2)|(1<<1));

	GT_CON |=1;

	printf("swi inittmpl:%u\r\n",*(uint32_t*)(&tmp));

	printf("swi initL:%u\r\n",GT_CMPL);
	printf("swi initH:%u\r\n",GT_CMPH);


    irq_register(27,gtimer,TRIGGER_EDGE_RISING,0,0);
	// while (1)
	// {
	// 	/* code */
	// }
	
	// usleep();


	// system_scheduler_init();
	// printf("system_scheduler_init init\r\n");
	// thread_idle_init();
	/* 初始化线程 */

	thread_init(&flag1_thread,
				"[1]flag1_thread",
				flag1_thread_entry,
				NULL,
				flag1_thread_stack,
				sizeof(flag1_thread_stack),
				1);
	// thread_startup(&flag1_thread);
	
	printf("thread1_init init\r\n");
	
	/* 初始化线程 */
	// thread_init( &flag2_thread,                 /* 线程控制块 */
	// 				&(thread_priority_table[1]),
	//                 flag2_thread_entry,               /* 线程入口地址 */
	//                 NULL,                          /* 线程形参 */
	//                 &flag2_thread_stack[0],        /* 线程栈起始地址 */
	//                 sizeof(flag2_thread_stack) );  /* 线程栈大小，单位为字节 */
	thread_init(&flag2_thread,
				"[2]flag2_thread",
				flag2_thread_entry,
				NULL,flag2_thread_stack,
				sizeof(flag2_thread_stack),
				2);
	// thread_startup(&flag2_thread);
	printf("thread2_init init\r\n");


	/* 启动系统调度器 */
	printf("system_scheduler_start\r\n");

	system_scheduler_start(); 

}

void delay (uint32_t count)
{
	for(; count!=0; count--);
}

/* 线程1 */
void flag1_thread_entry( void *p_arg )
{
	static int aa = 0;
	for( ;; )
	{
		printf("thread1\r\n");
		// aa++;
		sys_delay(20);

		/* 线程切换，这里是手动切换 */		
		// schedule();
	}
}

/* 线程2 */
void flag2_thread_entry( void *p_arg )
{
	static int bb = 0;
	for( ;; )
	{
		
		
		printf("thread2\r\n");
		// bb++;
		
		// sys_delay(20);



		/* 线程切换，这里是手动切换 */
		// schedule();
	}
}

void flag2_1_thread_entry( void *p_arg )
{
	for( ;; )
	{
		// sys_delay(200);


	}
  return 0;
}

