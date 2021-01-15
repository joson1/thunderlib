#include <kernel/thread.h>
#include <kernel/klist.h>
#include "kops.h"
#include <stdio.h>
extern void cpu_interrupt_enable_f();


extern uint32_t cpu_interrupt_disable();
extern void cpu_interrupt_enable(uint32_t level);

extern void cpu_hw_context_switch_interrupt(uint32_t from, uint32_t to);
uint32_t interrupt_cnt = 0;
uint32_t NumOfOverflows = 0;
uint32_t NextThreadUnblockTime;
uint32_t CurrentNumberOfThread = 0;
thread_t* pCurrentThread;
extern thread_t* pCurrentThread;
uint32_t sys_tick_counter = 0;
/* 线程就绪优先级组 */
uint32_t ThreadReadyPriorityGroup=0;

/* 当前优先级 */
uint8_t CurrentTopReadyPriority = 0;

// k_list_t thread_priority_table[THREAD_PRIORITY_MAX];

xList_t ThreadReadyTable[THREAD_PRIORITY_MAX];
extern xList_t ThreadReadyTable[THREAD_PRIORITY_MAX];


xList_t DelayedThreadList1;
xList_t DelayedThreadList2;

static xList_t* volatile pDelayedThreadList;
static xList_t* volatile pOverflowDelayedThreadList;


/* 线程休眠列表 */
k_list_t thread_defunct;

ALIGN(8)
/* 定义线程栈 */
static uint8_t idle_thread_stack[512];

static thread_t thread_idle;



unsigned long  idletask_ctr = 0;

#define GET_HIGHEST_PRIORITY( uxTopPriority, uxReadyPriorities ) uxTopPriority = ( 31UL - ( uint32_t ) __highest_bit_find( ( uxReadyPriorities ) ) )

void ThreadLists_init()
{

	for (size_t i = 0; i < configMAX_PRIORITIES; i++)
	{
		xList_init( &(ThreadReadyTable[i]) );
	}
	xList_init(&DelayedThreadList1);
	xList_init(&DelayedThreadList2);
	pDelayedThreadList = &DelayedThreadList1;
	pOverflowDelayedThreadList = &DelayedThreadList2;

}
extern void AddNewThreadToReadyList(thread_t* pthread);
void AddNewThreadToReadyList(thread_t* pthread)
{

	register level = cpu_interrupt_disable();
	CurrentNumberOfThread++;
	if (pCurrentThread == NULL)
	{	
		pCurrentThread = pthread;
		if (CurrentNumberOfThread==1U)
		{
			ThreadLists_init();
		}
		
		
	}
	ThreadReadyPriorityGroup |= (1<<(pthread->priority));
	xListInsertEnd(&(ThreadReadyTable[pthread->priority]),&(pthread->tListItem));
	cpu_interrupt_enable(level);
}
#define GT_INTS *((unsigned int*)0xF8F0020C)
#define GT_CON_REG0 *((unsigned int *)(0xF8F00200))
#define GT_CON_REG1 *((unsigned int *)(0xf8f00204))

//////////////////////////////////////////////IDLE_THREAD////////////////////////////
void thread_idle_entry(void *parameter)
{
    parameter = parameter;
    while (1)
    {
        idletask_ctr ++;

		// printf("sys_tick_counter:%d,GT_INTS:%08x,GT_CON_REG0:%08x,GT_CON_REG1:%08x\r\n",sys_tick_counter,GT_INTS,GT_CON_REG0,GT_CON_REG1);
		// if (GT_INTS)
		// {
		// 	GT_INTS =0;
		// 	GT_CON_REG0 = 0;
		// 	GT_CON_REG1 = 0;

		// }
		
    }
}

void thread_idle_init(void)
{
	/* 初始化线程 */
	thread_init( 	&thread_idle,
					(char*)"IDLE",                 /* 线程控制块 */
	                thread_idle_entry,               /* 线程入口地址 */
	                NULL,                          /* 线程形参 */
	                &idle_thread_stack[0],        /* 线程栈起始地址 */
	                sizeof(idle_thread_stack),
					0);  /* 线程栈大小，单位为字节 */

	printf("thread_idle_init init\r\n");

}



/* 初始化系统调度器 */
void system_scheduler_init(void)
{	


}


extern void show_stack(void* sp);

/* 启动系统调度器 */
void system_scheduler_start(void)
{

	uint32_t highest_ready_priority;

	thread_idle_init();

	/* 寻找包含就绪任务的最高优先级的队列 */

	GET_HIGHEST_PRIORITY(CurrentTopReadyPriority,ThreadReadyPriorityGroup) ;
    NextThreadUnblockTime = portMAX_DELAY;
	sys_tick_counter = 0;

	xlistGET_OWNER_OF_NEXT_ENTRY(pCurrentThread,&(ThreadReadyTable[CurrentTopReadyPriority]));

	// show_stack(pCurrentThread->sp);
	cpu_hw_context_switch_to((uint32_t)&pCurrentThread->sp);
    /* 永远不会返回 */

}




/* 系统调度 */
inline void schedule(void)
{
	register thread_t *to_thread;
	register thread_t *from_thread;
	// register unsigned long highest_ready_priority;
	uint32_t level = cpu_interrupt_disable();	
    /* 获取就绪的最高优先级 */
	GET_HIGHEST_PRIORITY(CurrentTopReadyPriority,ThreadReadyPriorityGroup) ;
    
	/* 获取就绪的最高优先级对应的线程控制块 */
	xlistGET_OWNER_OF_NEXT_ENTRY(to_thread,&(ThreadReadyTable[CurrentTopReadyPriority]));
	// if (to_thread==0)
	// {
	// 	xlistGET_OWNER_OF_NEXT_ENTRY(to_thread,&(ThreadReadyTable[CurrentTopReadyPriority]));
	// }
	

    /* 如果目标线程不是当前线程，则要进行线程切换 */
	if(to_thread!=pCurrentThread)
	{
		from_thread = pCurrentThread;
		pCurrentThread = to_thread;
		if (interrupt_cnt==0)
		{
			cpu_hw_context_switch((uint32_t)&from_thread->sp,
									(uint32_t)&to_thread->sp);
			cpu_interrupt_enable(level);
		}else
		{
			cpu_hw_context_switch_interrupt((uint32_t)&from_thread->sp,
											 (uint32_t)&to_thread->sp);
		}
		
		
		// current_priority = (uint8_t)highest_ready_priority;
	}
	cpu_interrupt_enable(level);
	
}


static void prvResetNextTaskUnblockTime( void )
{
    thread_t *pxTCB;

	if( xlistLIST_IS_EMPTY( pDelayedThreadList ) != 0 )
	{
		/* The new current delayed list is empty.  Set xNextTaskUnblockTime to
		the maximum possible value so it is	extremely unlikely that the
		if( xTickCount >= xNextTaskUnblockTime ) test will pass until
		there is an item in the delayed list. */
		NextThreadUnblockTime = portMAX_DELAY;
	}
	else
	{
		/* The new current delayed list is not empty, get the value of
		the item at the head of the delayed list.  This is the time at
		which the task at the head of the delayed list should be removed
		from the Blocked state. */
		( pxTCB ) = ( thread_t * ) xlistGET_OWNER_OF_HEAD_ENTRY( pDelayedThreadList );
		NextThreadUnblockTime = xlistGET_LIST_ITEM_VALUE( &( ( pxTCB )->tListItem ) );
	}
}

/* 
 * 当系统时基计数器溢出的时候，延时列表pxDelayedTaskList 和
 * pxOverflowDelayedTaskList要互相切换
 */
#define taskSWITCH_DELAYED_LISTS()\
{\
	xList_t *pxTemp;\
	pxTemp = pDelayedThreadList;\
	pDelayedThreadList = pOverflowDelayedThreadList;\
	pOverflowDelayedThreadList = pxTemp;\
	NumOfOverflows++;\
	prvResetNextTaskUnblockTime();\
}



static inline void _tick_increase(void)
{
    uint32_t i;
	register thread_t *pThread;
	uint32_t ItemValue;
    sys_tick_counter++ ;
	if (sys_tick_counter == 0)
	{
		taskSWITCH_DELAYED_LISTS();
	}
	/* 最近的延时任务延时到期 */
	if ( sys_tick_counter >= NextThreadUnblockTime )
	{
			for (  ;   ; )
			{
				 if ( xlistLIST_IS_EMPTY(pDelayedThreadList) != 0 )
				 {
					 NextThreadUnblockTime = portMAX_DELAY;
					 break;
				 }else
				 {
					pThread = (thread_t*)xlistGET_OWNER_OF_HEAD_ENTRY( pDelayedThreadList );
					// pThread = (thread_t*)(&(pDelayedThreadList->xListEnd)->pxNext->Owner)
					ItemValue = xlistGET_LIST_ITEM_VALUE(&( pThread->tListItem ));
					if (sys_tick_counter<ItemValue)
					{
						NextThreadUnblockTime = ItemValue;
						break;
					}
					pThread->status = THREAD_STATUS_RUNNING;
					xListRemove( &(pThread->tListItem) );
					AddNewThreadToReadyList(pThread);



				 }
				 
			}
			
	}
	

    /* 系统调度 */
	schedule();
}



void sys_tick_handler()
{

	_tick_increase();
}
extern void sys_tick_handler();


void sys_delay(uint32_t TicksToWait)
{
	register tmp = cpu_interrupt_disable();
	uint32_t delay;
	uint32_t TimeToWake;
	const uint32_t ConstTickCount = sys_tick_counter;

    /* 将任务从就绪列表中移除 */
	xListRemove(&(pCurrentThread->tListItem));
	/* 将任务在优先级位图中对应的位清除 */
	if (xlistCURRENT_LIST_LENGTH(&(ThreadReadyTable[pCurrentThread->priority]))==0)
	{
		
		ThreadReadyPriorityGroup &= ~(1<<pCurrentThread->priority);
	}
	

	TimeToWake = ConstTickCount+TicksToWait;

	xlistSET_LIST_ITEM_VALUE( &(pCurrentThread->tListItem),TimeToWake );
	if (TimeToWake<ConstTickCount)
	{
		xListInsert(pOverflowDelayedThreadList,&(pCurrentThread->tListItem));
	}else
	{
		xListInsert(pDelayedThreadList,&(pCurrentThread->tListItem));
		if (TimeToWake<NextThreadUnblockTime)
		{
			NextThreadUnblockTime = TimeToWake;
		}
		
	}
	pCurrentThread->status = THREAD_STATUS_SUSPEND;
	cpu_interrupt_enable(tmp);
	
	// schedule();
	while (pCurrentThread->status == THREAD_STATUS_SUSPEND)
	{
		delay++;
	}
	




}


extern void interrupt_enter();

void interrupt_enter()
{
	// uint32_t level = cpu_interrupt_disable();
	interrupt_cnt++;
	// cpu_interrupt_enable(level);
}

extern void interrupt_exit();
void interrupt_exit()
{
	// uint32_t level = cpu_interrupt_disable();
	interrupt_cnt--;
	// cpu_interrupt_enable(level);

}
