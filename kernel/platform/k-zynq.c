#include <thunder/sleep.h>
#include <stdio.h>
#include <thunder/tty/tty.h>
#include <thunder/gpio.h>
#include "zynq7000/zynq.h"
#include <kernel/thread.h>
#include <kernel/klist.h>
#include "zynq7000/xtime_l.h"
#include <thunder/irq.h>
#include <kernel/kernel.h>








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

void k_handler()
{


    interrupt_enter();

	sys_tick_handler();
		// printf("ptimer\r\n"); 
    PRIVATE_TIMER->ISR = PRIVATE_TIMER_ISR_EVENT_FLAG_MASK;

	interrupt_exit();

	
}


extern kernel_zynq_init();
int kernel_zynq_init()
{
	int a = 0;
	__swi();
	cmd_init();
	uint32_t level = cpu_interrupt_disable();

    ICDICFR[0] &= ~(TRIGGER_EDGE_RISING<<(0*2));
    ICDICFR[0] |=  (TRIGGER_EDGE_RISING<<(0*2));

    ICDISER[0] |= (1<<0);

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
    irq_register(IRQ_Zynq7000_PTIMER ,k_handler,TRIGGER_EDGE_RISING,0,0);

    /* The processor timer is always clocked at 1/2 CPU frequency(CPU_3x2x). */
    PRIVATE_TIMER->COUNTER = APU_FREQ/2/TICK_PER_SECOND;
    /* Set reload value. */
    PRIVATE_TIMER->LOAD = APU_FREQ/2/TICK_PER_SECOND;
    PRIVATE_TIMER->CONTROL |= PRIVATE_TIMER_CONTROL_AUTO_RELOAD_MASK;

	// cpu_interrupt_enable_f();
    PRIVATE_TIMER->CONTROL |= PRIVATE_TIMER_CONTROL_ENABLE_MASK;

	system_scheduler_start(); 

}

