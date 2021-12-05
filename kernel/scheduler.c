#include <kernel/thread.h>
#include <kernel/klist.h>
#include "kops.h"
#include <stdio.h>

extern void cpu_interrupt_enable_f();
extern int cpu_get_smp_id();

extern uint32_t cpu_interrupt_disable();
extern void cpu_interrupt_enable(uint32_t level);

extern void cpu_hw_context_switch_interrupt(uint32_t from, uint32_t to);
uint32_t interrupt_cnt[nBrOfCPUs] = { [0 ... nBrOfCPUs-1]=0,   };
uint32_t NumOfOverflows[nBrOfCPUs] = { [0 ... nBrOfCPUs-1]=0,   };
uint32_t NextThreadUnblockTime[nBrOfCPUs]={ [0 ... nBrOfCPUs-1]=0,   };
uint32_t CurrentNumberOfThread[nBrOfCPUs] = { [0 ... nBrOfCPUs-1]=0,   };
thread_t* pCurrentThread[nBrOfCPUs]={ [0 ... nBrOfCPUs-1]=0,   };
extern thread_t* pCurrentThread[nBrOfCPUs];
uint32_t sys_tick_counter[nBrOfCPUs] = { [0 ... nBrOfCPUs-1]=0,   };
/* 线程就绪优先级组 */
uint32_t ThreadReadyPriorityGroup[nBrOfCPUs]={ [0 ... nBrOfCPUs-1]=0,   };

/* 当前优先级 */
uint8_t CurrentTopReadyPriority[nBrOfCPUs] = {0};

// k_list_t thread_priority_table[THREAD_PRIORITY_MAX];

xList_t ThreadReadyTable[nBrOfCPUs][THREAD_PRIORITY_MAX];
extern xList_t ThreadReadyTable[nBrOfCPUs][THREAD_PRIORITY_MAX];


xList_t DelayedThreadList1[nBrOfCPUs];
xList_t DelayedThreadList2[nBrOfCPUs];

static xList_t* volatile pDelayedThreadList[nBrOfCPUs];
static xList_t* volatile pOverflowDelayedThreadList[nBrOfCPUs];


/* 线程休眠列表 */
k_list_t thread_defunct;

ALIGN(8)
/* 定义线程栈 */

extern unsigned long  idletask_ctr[nBrOfCPUs];
unsigned long  idletask_ctr[nBrOfCPUs] = {0};

#define GET_HIGHEST_PRIORITY( uxTopPriority, uxReadyPriorities ) uxTopPriority = ( 31UL - ( uint32_t ) __highest_bit_find( ( uxReadyPriorities ) ) )

void ThreadLists_init(uint32_t cpuid)
{

	// uint32_t cpuid = cpu_get_smp_id();
	for (size_t i = 0; i < configMAX_PRIORITIES; i++)
	{
		xList_init( &(ThreadReadyTable[cpuid][i]) );
	}
	xList_init(&DelayedThreadList1[cpuid]);
	xList_init(&DelayedThreadList2[cpuid]);
	pDelayedThreadList[cpuid] = &DelayedThreadList1[cpuid];
	pOverflowDelayedThreadList[cpuid] = &DelayedThreadList2[cpuid];

}
extern void  AddNewThreadToReadyList(thread_t* pthread,uint32_t cpuid);
void AddNewThreadToReadyList(thread_t* pthread,uint32_t cpuid)
{

	register level = cpu_interrupt_disable();
	CurrentNumberOfThread[cpuid]++;
	if (pCurrentThread[cpuid] == NULL)
	{	
		pCurrentThread[cpuid] = pthread;
		if (CurrentNumberOfThread[cpuid]==1U)
		{
			ThreadLists_init(cpuid);
		}
		
		
	}
	ThreadReadyPriorityGroup[cpuid] |= (1<<(pthread->priority));
	xListInsertEnd(&(ThreadReadyTable[cpuid][pthread->priority]),&(pthread->tListItem));
	cpu_interrupt_enable(level);
}
#define GT_INTS *((unsigned int*)0xF8F0020C)
#define GT_CON_REG0 *((unsigned int *)(0xF8F00200))
#define GT_CON_REG1 *((unsigned int *)(0xf8f00204))



/* 初始化系统调度器 */
void system_scheduler_init(void)
{	


}


extern void show_stack(void* sp);

/* 启动系统调度器 */
void system_scheduler_start(void)
{

	uint32_t highest_ready_priority;

	uint32_t cpuid = cpu_get_smp_id();
	// thread_idle_init();
	// if (cpuid)
	// {
	// 	thread_idle2_init();
	// }
	

	/* 寻找包含就绪任务的最高优先级的队列 */

	GET_HIGHEST_PRIORITY(CurrentTopReadyPriority[cpuid],ThreadReadyPriorityGroup[cpuid]) ;
    NextThreadUnblockTime[cpuid] = portMAX_DELAY;
	sys_tick_counter[cpuid] = 0;

	xlistGET_OWNER_OF_NEXT_ENTRY(pCurrentThread[cpuid],&(ThreadReadyTable[cpuid][CurrentTopReadyPriority[cpuid]]));

	// show_stack(pCurrentThread->sp);
	cpu_hw_context_switch_to((uint32_t)&(pCurrentThread[cpuid])->sp);
    /* 永远不会返回 */

}




/* 系统调度 */
inline void schedule(void)
{
	register thread_t *to_thread;
	register thread_t *from_thread;
	uint32_t cpuid = cpu_get_smp_id();
	// register unsigned long highest_ready_priority;
	// uint32_t level = cpu_interrupt_disable();	
    /* 获取就绪的最高优先级 */
	GET_HIGHEST_PRIORITY(CurrentTopReadyPriority[cpuid],ThreadReadyPriorityGroup[cpuid]) ;
    
	/* 获取就绪的最高优先级对应的线程控制块 */
	xlistGET_OWNER_OF_NEXT_ENTRY(to_thread,&(ThreadReadyTable[cpuid][CurrentTopReadyPriority[cpuid]]));
	// if (to_thread==0)
	// {
	// 	xlistGET_OWNER_OF_NEXT_ENTRY(to_thread,&(ThreadReadyTable[CurrentTopReadyPriority]));
	// }
	

    /* 如果目标线程不是当前线程，则要进行线程切换 */
	if(to_thread!=pCurrentThread[cpuid])
	{
		from_thread = pCurrentThread[cpuid];
		pCurrentThread[cpuid]= to_thread;
		if (interrupt_cnt[cpuid]==0)
		{
			cpu_hw_context_switch((uint32_t)&from_thread->sp,
									(uint32_t)&to_thread->sp);
			// cpu_interrupt_enable(level);
		}else
		{
			cpu_hw_context_switch_interrupt((uint32_t)&from_thread->sp,
											 (uint32_t)&to_thread->sp);
		}
		
		
		// current_priority = (uint8_t)highest_ready_priority;
	}
	// cpu_interrupt_enable(level);
	
}


static void prvResetNextTaskUnblockTime( void )
{
    thread_t *pxTCB;
	uint32_t cpuid = cpu_get_smp_id();

	if( xlistLIST_IS_EMPTY( pDelayedThreadList[cpuid] ) != 0 )
	{
		/* The new current delayed list is empty.  Set xNextTaskUnblockTime to
		the maximum possible value so it is	extremely unlikely that the
		if( xTickCount >= xNextTaskUnblockTime ) test will pass until
		there is an item in the delayed list. */
		NextThreadUnblockTime[cpuid] = portMAX_DELAY;
	}
	else
	{
		/* The new current delayed list is not empty, get the value of
		the item at the head of the delayed list.  This is the time at
		which the task at the head of the delayed list should be removed
		from the Blocked state. */
		( pxTCB ) = ( thread_t * ) xlistGET_OWNER_OF_HEAD_ENTRY( pDelayedThreadList[cpuid] );
		NextThreadUnblockTime[cpuid] = xlistGET_LIST_ITEM_VALUE( &( ( pxTCB )->tListItem ) );
	}
}

/* 
 * 当系统时基计数器溢出的时候，延时列表pxDelayedTaskList 和
 * pxOverflowDelayedTaskList要互相切换
 */
#define taskSWITCH_DELAYED_LISTS()\
{\
	uint32_t cpuid = cpu_get_smp_id();\
	xList_t *pxTemp;\
	pxTemp = pDelayedThreadList[cpuid];\
	pDelayedThreadList[cpuid] = pOverflowDelayedThreadList[cpuid];\
	pOverflowDelayedThreadList[cpuid] = pxTemp;\
	NumOfOverflows[cpuid]++;\
	prvResetNextTaskUnblockTime();\
}



static inline void _tick_increase(void)
{
    uint32_t i;
	register thread_t *pThread;
	uint32_t ItemValue;
	uint32_t cpuid = cpu_get_smp_id();
    sys_tick_counter[cpuid]++ ;
	if (sys_tick_counter[cpuid] == 0)
	{
		taskSWITCH_DELAYED_LISTS();
	}
	/* 最近的延时任务延时到期 */
	if ( sys_tick_counter[cpuid] >= NextThreadUnblockTime[cpuid] )
	{
			for (  ;   ; )
			{
				if ( xlistLIST_IS_EMPTY(pDelayedThreadList[cpuid]) != 0 )
				{
					NextThreadUnblockTime[cpuid] = portMAX_DELAY;
					break;
				}else
				{
				pThread = (thread_t*)xlistGET_OWNER_OF_HEAD_ENTRY( pDelayedThreadList[cpuid] );
				// pThread = (thread_t*)(&(pDelayedThreadList->xListEnd)->pxNext->Owner)
				ItemValue = xlistGET_LIST_ITEM_VALUE(&( pThread->tListItem ));
				if (sys_tick_counter[cpuid]<ItemValue)
				{
					NextThreadUnblockTime[cpuid] = ItemValue;
					break;
				}
				pThread->status = THREAD_STATUS_RUNNING;
				xListRemove( &(pThread->tListItem) );
				AddNewThreadToReadyList(pThread,cpuid);

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
	uint32_t cpuid = cpu_get_smp_id();
	const uint32_t ConstTickCount = sys_tick_counter[cpuid];

    /* 将任务从就绪列表中移除 */
	xListRemove(&(pCurrentThread[cpuid]->tListItem));
	/* 将任务在优先级位图中对应的位清除 */
	if (xlistCURRENT_LIST_LENGTH(&(ThreadReadyTable[cpuid][pCurrentThread[cpuid]->priority]))==0)
	{
		
		ThreadReadyPriorityGroup[cpuid] &= ~(1<<pCurrentThread[cpuid]->priority);
	}
	

	TimeToWake = ConstTickCount+TicksToWait;

	xlistSET_LIST_ITEM_VALUE( &(pCurrentThread[cpuid]->tListItem),TimeToWake );
	if (TimeToWake<ConstTickCount)
	{
		xListInsert(pOverflowDelayedThreadList[cpuid],&(pCurrentThread[cpuid]->tListItem));
	}else
	{
		xListInsert(pDelayedThreadList[cpuid],&(pCurrentThread[cpuid]->tListItem));
		if (TimeToWake<NextThreadUnblockTime[cpuid])
		{
			NextThreadUnblockTime[cpuid] = TimeToWake;
		}
		
	}
	pCurrentThread[cpuid]->status = THREAD_STATUS_SUSPEND;
	cpu_interrupt_enable(tmp);
	
	// schedule();
	while (pCurrentThread[cpuid]->status == THREAD_STATUS_SUSPEND)
	{
		delay++;
	}
	




}


extern void interrupt_enter();

void interrupt_enter()
{
	uint32_t cpuid = cpu_get_smp_id();
	// uint32_t level = cpu_interrupt_disable();
	interrupt_cnt[cpuid]++;
	// cpu_interrupt_enable(level);
}

extern void interrupt_exit();
void interrupt_exit()
{
	uint32_t cpuid = cpu_get_smp_id();

	// uint32_t level = cpu_interrupt_disable();
	interrupt_cnt[cpuid]--;
	// cpu_interrupt_enable(level);

}


extern void task_ed();
void task_ed()
{
	register tmp = cpu_interrupt_disable();
	uint32_t cpuid = cpu_get_smp_id();
    /* 将任务从就绪列表中移除 */
	xListRemove(&(pCurrentThread[cpuid]->tListItem));
	/* 将任务在优先级位图中对应的位清除 */
	if (xlistCURRENT_LIST_LENGTH(&(ThreadReadyTable[cpuid][pCurrentThread[cpuid]->priority]))==0)
	{
		
		ThreadReadyPriorityGroup[cpuid] &= ~(1<<pCurrentThread[cpuid]->priority);
	}
	if(pCurrentThread[cpuid]->exit) 
	{
		pCurrentThread[cpuid]->exit((xlistGET_LIST_ITEM_OWNER(&(pCurrentThread[cpuid]->tListItem))));
	}
	printf("Thread:%s Exit\r\n",pCurrentThread[cpuid]->name);
	cpu_interrupt_enable(tmp);
	
	while(1);
	
}

