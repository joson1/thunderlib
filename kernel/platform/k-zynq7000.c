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
#define CPU1STARTADDR 0xFFFFFFF0
void __sev()
{
    asm("sev");
}

void __dmb()
{
    asm("dmb");
}

void __setsp()
{
    asm("mov sp, #0x104000");
}
// #d
// #define sev() __asm__("sev")

void __setvfp()
{


	/* enable vfp */
	asm(" fmrx	r1, FPEXC ");			/* read the exception register */
	asm(" orr	r1,r1, #0x40000000");			/* read the exception register */
	asm("fmxr	FPEXC, r1");			/* read the exception register */
				/* write back the exception register */


}
void k_handler()
{


    interrupt_enter();

	sys_tick_handler();
		// printf("ptimer\r\n"); 
    PRIVATE_TIMER->ISR = PRIVATE_TIMER_ISR_EVENT_FLAG_MASK;

	interrupt_exit();

	
}

//	MRC p15,0,<Rd>,c0,c0,5; read Multiprocessor ID register
#include "zynq7000/gic.h"
#define Zynq7000_GIC_CPU_BASE            0xF8F00100  /* Generic interrupt controller CPU interface */
#define Zynq7000_GIC_DIST_BASE           0xF8F01000  /* Generic interrupt controller */

extern kernel1_zynq_init();
int kernel1_zynq_init()
{
	int a = 0;
	// __swi();
	uint32_t level = cpu_interrupt_disable();
    // __setsp();
    // __setvfp();

    arm_gic_dist_init(0, Zynq7000_GIC_DIST_BASE, 0);
    arm_gic_cpu_init(0, Zynq7000_GIC_CPU_BASE);

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
    irq_register(IRQ_Zynq7000_PTIMER ,k_handler,0,0);
    arm_gic_set_cpu(0, IRQ_Zynq7000_PTIMER, 1 << 1);
    
    /* The processor timer is always clocked at 1/2 CPU frequency(CPU_3x2x). */
    PRIVATE_TIMER->COUNTER = APU_FREQ/2/TICK_PER_SECOND;
    /* Set reload value. */
    PRIVATE_TIMER->LOAD = APU_FREQ/2/TICK_PER_SECOND;
    PRIVATE_TIMER->CONTROL |= PRIVATE_TIMER_CONTROL_AUTO_RELOAD_MASK;

	// cpu_interrupt_enable_f();
    PRIVATE_TIMER->CONTROL |= PRIVATE_TIMER_CONTROL_ENABLE_MASK;

	system_scheduler_start(); 

}


extern kernel_zynq_init();
int kernel_zynq_init()
{
	int a = 0;
	// __swi();
	uint32_t level = cpu_interrupt_disable();
    // __setsp();
    // __setvfp();
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
    irq_register(IRQ_Zynq7000_PTIMER ,k_handler,0,0);

    /* The processor timer is always clocked at 1/2 CPU frequency(CPU_3x2x). */
    PRIVATE_TIMER->COUNTER = APU_FREQ/2/TICK_PER_SECOND;
    /* Set reload value. */
    PRIVATE_TIMER->LOAD = APU_FREQ/2/TICK_PER_SECOND;
    PRIVATE_TIMER->CONTROL |= PRIVATE_TIMER_CONTROL_AUTO_RELOAD_MASK;

	// cpu_interrupt_enable_f();
    PRIVATE_TIMER->CONTROL |= PRIVATE_TIMER_CONTROL_ENABLE_MASK;

	system_scheduler_start(); 

}
#include "zynq7000/xil_cache_l.h"
extern void weakup_cpu1();
void weakup_cpu1()
{
    // __swi();
    *((uint32_t*)CPU1STARTADDR) = 0x100000;
    __dmb();
    Xil_DCacheFlushLine(CPU1STARTADDR);
    __sev();
}




//////////////////////////////////////////////IDLE_THREAD////////////////////////////


static thread_t thread_idle[nBrOfCPUs];
ALIGN(4)
static uint8_t idle_thread_stack[nBrOfCPUs][512];
extern unsigned long  idletask_ctr[nBrOfCPUs];


void thread_idle0_entry(void *parameter)
{
	uint32_t id = 0;
    parameter = parameter;
    while (1)
    {
		// id = cpu_get_smp_id();
        idletask_ctr[0] ++;
		// printf("sys_tick_counter:%d,GT_INTS:%08x,GT_CON_REG0:%08x,GT_CON_REG1:%08x\r\n",sys_tick_counter,GT_INTS,GT_CON_REG0,GT_CON_REG1);
		// if (GT_INTS)
		// {
		// 	GT_INTS =0;
		// 	GT_CON_REG0 = 0;
		// 	GT_CON_REG1 = 0;

		// }
		
    }
}

void thread_idle0_init(void)
{
	// uint32_t cpuid = cpu_get_smp_id();
	/* 初始化线程 */
	thread_init( 	&(thread_idle[0]),
					(char*)"IDLE(0)",                 /* 线程控制块 */
	                thread_idle0_entry,               /* 线程入口地址 */
					NULL,
	                NULL,                          /* 线程形参 */
	                idle_thread_stack[0],        /* 线程栈起始地址 */
	                sizeof(idle_thread_stack)/2, /* 线程栈大小，单位为字节 */
					0,
					0);  

	// printf("thread_idle init on cpu:%d\t stack%08x\r\n",cpuid, &idle_thread_stack[cpuid][0]);
	

}


void thread_idle1_entry(void *parameter)
{
	uint32_t id = 0;
    parameter = parameter;
    while (1)
    {
		// id = cpu_get_smp_id();
        idletask_ctr[1] ++;
		// printf("sys_tick_counter:%d,GT_INTS:%08x,GT_CON_REG0:%08x,GT_CON_REG1:%08x\r\n",sys_tick_counter,GT_INTS,GT_CON_REG0,GT_CON_REG1);
		// if (GT_INTS)
		// {
		// 	GT_INTS =0;
		// 	GT_CON_REG0 = 0;
		// 	GT_CON_REG1 = 0;

		// }
		
    }
}

void thread_idle1_init(void)
{
	/* 初始化线程 */
	thread_init( 	&(thread_idle[1]),
					(char*)"IDLE(1)",                 /* 线程控制块 */
	                thread_idle1_entry,               /* 线程入口地址 */
					NULL,
	                NULL,                          /* 线程形参 */
	                idle_thread_stack[1],        /* 线程栈起始地址 */
	                sizeof(idle_thread_stack)/2,
					0,
					1);  /* 线程栈大小，单位为字节 */

	// printf("thread_idle init on cpu:%d\t stack%08x\r\n",cpuid, &idle_thread_stack[cpuid][0]);
	

}





void zynq7000_kernel_services_init()
{
    thread_idle0_init();
    thread_idle1_init();
}

KERNEL_SEV_INIT(zynq7000_kernel_services_init);
