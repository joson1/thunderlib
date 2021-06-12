#include <stdio.h>
#include <thunder/tty/tty.h>
#include <kernel/thread.h>
#include <kernel/klist.h>
#include <kernel/kernel.h>
#include "stm32f429/sys.h"

#define OS_TIMER_SLICE_MS 10

void systick_init()
{
    uint32_t temp;		   
	SysTick->LOAD=OS_TIMER_SLICE_MS*22500-1;			//
    
    MY_NVIC_Init(SysTick_IRQn,0);
	SysTick->VAL =0;           			//清空计数器
	SysTick->CTRL= (1<<2)|(1<<1)|0x01 ;          			//开始倒数  
    
}

void SysTick_Handler()
{

    interrupt_enter();

	sys_tick_handler();
		// printf("ptimer\r\n"); 
    // PRIVATE_TIMER->ISR = PRIVATE_TIMER_ISR_EVENT_FLAG_MASK;

	interrupt_exit();

}

void kernel_stm32f429_init()
{
	uint32_t level = cpu_interrupt_disable();

    systick_init();
    MY_NVIC_Init(PendSV_IRQn,1);
	system_scheduler_start(); 


    // while (1)
    // {
    //     /* code */
    // }
    
}
