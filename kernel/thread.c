/*
 * @Author: your name
 * @Date: 1970-01-01 08:00:00
 * @LastEditTime: 2021-01-13 19:44:16
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /ThunderLib/kernel/thread.c
 */
#include <kernel/thread.h>


extern uint32_t cpu_interrupt_disable();
extern void cpu_interrupt_enable(uint32_t level);
extern void cpu_interrupt_enable_f();
extern void  AddNewThreadToReadyList(thread_t* pthread,uint32_t cpuid);


k_err_t thread_init(thread_t *thread,
						const char* name,
                        void (*entry)(void *parameter),
                        void             *parameter,
                        void (*exit)(void),
                        void*			stack_start,
                        uint32_t       stack_size,
						uint32_t 		priority,
						uint32_t		cpuid
						)
{

    thread->entry = (void*)entry;
	thread->parameter = parameter;
	thread->exit = exit;
	thread->stack_addr = stack_start;
	thread->stack_size = stack_size;
	thread->cpuid = cpuid;
	/* 初始化线程栈，并返回线程栈指针 */
	thread->sp = (void *)cpu_hw_stack_init( thread->entry, 
		                                   thread->parameter,
										   thread->exit = exit,
							               (uint8_t *)((char *)thread->stack_addr + thread->stack_size - 4) );
	thread->ticks_to_delay = 0;
	thread->number_mask = 0;

	
	/* 将任务的名字存储在TCB中 */
	for( uint32_t x = ( uint32_t ) 0; x < ( uint32_t ) configMAX_TASK_NAME_LEN; x++ )
	{
		// pxNewTCB->pcTaskName[ x ] = pcName[ x ];
		thread->name[x] = name[x];

		if( name[ x ] == 0x00 )
		{
			break;
		}
	}
	/* 任务名字的长度不能超过configMAX_TASK_NAME_LEN */
	// pxNewTCB->pcTaskName[ configMAX_TASK_NAME_LEN - 1 ] = '\0';
	thread->name[configMAX_TASK_NAME_LEN - 1] = '\0';
	xListItem_init(&(thread->tListItem));
    xlistSET_LIST_ITEM_OWNER(&(thread->tListItem),thread);

    /* 初始化优先级 */
	if( priority >= ( uint32_t ) configMAX_PRIORITIES )
	{
		priority = ( uint32_t ) configMAX_PRIORITIES - ( uint32_t ) 1U;
	}
	// pxNewTCB->uxPriority = uxPriority;
	thread->priority = priority;
    
	/* 将任务添加到就绪列表 */
	AddNewThreadToReadyList(thread,cpuid);
	return KERNEL_EOK;
}

