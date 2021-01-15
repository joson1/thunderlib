/*
 * @Author: your name
 * @Date: 2020-07-31 19:32:57
 * @LastEditTime: 2021-01-15 23:12:57
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
#include <thunder/interrput.h>

#define NONE                  "\e[0m"           //清除颜色，即之后的打印为正常输出，之前的不受影响
#define BLACK                 "\e[0;30m"         //深黑
#define L_BLACK             "\e[1;30m"            //亮黑，偏灰褐
#define RED                     "\e[0;31m"      //深红，暗红
#define L_RED                 "\e[1;31m"        //鲜红
#define GREEN                "\e[0;32m"         //深绿，暗绿
#define L_GREEN            "\e[1;32m"           //鲜绿
#define BROWN               "\e[0;33m"          //深黄，暗黄
#define YELLOW              "\e[1;33m"          //鲜黄
#define BLUE                    "\e[0;34m"      //深蓝，暗蓝
#define L_BLUE                "\e[1;34m"        //亮蓝，偏白灰
#define PURPLE               "\e[0;35m"         //深粉，暗粉，偏暗紫
#define L_PURPLE           "\e[1;35m"           //亮粉，偏白灰
#define CYAN                   "\e[0;36m"       //暗青色
#define L_CYAN               "\e[1;36m"         //鲜亮青色
#define GRAY                   "\e[0;37m"       //灰色
#define WHITE                  "\e[1;37m"       //白色，字体粗一点，比正常大，比bold小
#define BOLD                    "\e[1m"         //白色，粗体
#define UNDERLINE         "\e[4m"               //下划线，白色，正常大小
#define BLINK                   "\e[5m"         //闪烁，白色，正常大小
#define REVERSE            "\e[7m"              //反转，即字体背景为白色，字体为黑色
#define HIDE                     "\e[8m"        //隐藏
#define CLEAR                  "\e[2J"          //清除
#define CLRLINE               "\r\e[K"          //清除行

#define MOVETO(x,y) printf("\033[%d;%dH", (x), (y))
#define CLEAR() printf("\033[2J")

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
thread_t flag2_1_thread;
extern uint32_t cpu_interrupt_disable();
extern void cpu_interrupt_enable(uint32_t level);


ALIGN(8)
/* 定义线程栈 */
uint8_t flag1_thread_stack[10240];
uint8_t flag2_thread_stack[10240];
uint8_t flag2_1_thread_stack[10240];

/* 线程声明 */
void flag1_thread_entry(void *p_arg);
void flag2_thread_entry(void *p_arg);
void flag3_thread_entry(void *p_arg);
void flag2_1_thread_entry( void *p_arg );

#define GT_CON 	*((unsigned int*)0xF8F00208)
#define GT_CMPL 	*((unsigned int*)0xF8F00210)
#define GT_CMPH 	*((unsigned int*)0xf8f00214)

#define GT_INTS *((unsigned int*)0xF8F0020C)
#define OS_TIMER_SLICE_MS 10
#define TICK_PER_SECOND (1000/OS_TIMER_SLICE_MS)
#define COUNTS_PER_USECOND  (XPAR_CPU_CORTEXA9_CORE_CLOCK_FREQ_HZ / (2U*1000000U))
#define GT_CON_REG0 *((unsigned int *)(0xF8F00200))
#define GT_CON_REG1 *((unsigned int *)(0xf8f00204))

extern void sys_tick_handler();
extern void interrupt_exit();
extern void interrupt_enter();


/* Freq of all peripherals */
#define APU_FREQ     666666667
#define DDR_FREQ     533333313
#define DCI_FREQ     10159000
#define IRQ_Zynq7000_PTIMER      29

void __swi()
{
	asm("mov r0,lr");
	asm("swi 0");
}

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
    interrupt_enter();
	// GT_CON_REG0 = 0;
	// GT_CON_REG1 = 0;
	// GT_INTS = 1;	
	sys_tick_handler();
		// printf("ptimer\r\n"); 
    PRIVATE_TIMER->ISR = PRIVATE_TIMER_ISR_EVENT_FLAG_MASK;

	interrupt_exit();

}

int main()
{
	int a = 0;
	__swi();
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
	// GT_CON_REG0 = 0;
	// GT_CON_REG1 = 0;
	// GT_CON = 0;
	// uint64_t tmp = (((uint64_t) OS_TIMER_SLICE_MS*1000) * COUNTS_PER_USECOND);
	// uint32_t tmpl = tmp;
	// GT_CMPL = tmpl;
	// GT_CMPH = tmp>>32;

	// GT_CON |= ((1<<2)|(1<<1));
	// GT_CON |=1;


	// printf("swi inittmpl:%u\r\n",*(uint32_t*)(&tmp));

	// printf("swi initL:%u\r\n",GT_CMPL);
	// printf("swi initH:%u\r\n",GT_CMPH);

    PRIVATE_TIMER->CONTROL &= ~PRIVATE_TIMER_CONTROL_ENABLE_MASK;
    {
        /* Clear the prescaler. */
        uint32_t ctrl = PRIVATE_TIMER->CONTROL;
        ctrl &= ~PRIVATE_TIMER_CONTROL_PRESCALER_MASK;
        PRIVATE_TIMER->CONTROL = ctrl;
    }

    /* The processor timer is always clocked at 1/2 CPU frequency(CPU_3x2x). */
    PRIVATE_TIMER->COUNTER = APU_FREQ/2/TICK_PER_SECOND;
    /* Set reload value. */
    PRIVATE_TIMER->LOAD = APU_FREQ/2/TICK_PER_SECOND;
    PRIVATE_TIMER->CONTROL |= PRIVATE_TIMER_CONTROL_AUTO_RELOAD_MASK;

    PRIVATE_TIMER->CONTROL |= PRIVATE_TIMER_CONTROL_IRQ_ENABLE_MASK;
    PRIVATE_TIMER->ISR = PRIVATE_TIMER_ISR_EVENT_FLAG_MASK;


	// InterruptMaptoCpu(0,27);
    irq_register(IRQ_Zynq7000_PTIMER ,gtimer,TRIGGER_EDGE_RISING,0,0);


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
	

	thread_init(&flag2_thread,
				"[2]flag2_thread",
				flag2_thread_entry,
				NULL,flag2_thread_stack,
				sizeof(flag2_thread_stack),
				2);
	// thread_startup(&flag2_thread);
	printf("thread2_init init\r\n");

	thread_init(&flag2_1_thread,
				"[2]flag2_1_thread",
				flag2_1_thread_entry,
				NULL,flag2_1_thread_stack,
				sizeof(flag2_1_thread_stack),
				2);

	printf("flag2_1_thread init\r\n");

	/* 启动系统调度器 */
	printf("system_scheduler_start\r\n");
	// GT_CON_REG0=0;
	// GT_CON_REG1=0;
	CLEAR();

	// cpu_interrupt_enable_f();
    PRIVATE_TIMER->CONTROL |= PRIVATE_TIMER_CONTROL_ENABLE_MASK;

	system_scheduler_start(); 

}

void delay (uint32_t count)
{
	for(; count!=0; count--);
}

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
