#include <kernel/thread.h>
#include <kernel/klist.h>


thread_t* current_thread;


k_list_t thread_priority_table[THREAD_PRIORITY_MAX];

/* 线程休眠列表 */
k_list_t thread_defunct;



/* 初始化系统调度器 */
void system_scheduler_init(void)
{	
	register uint32_t offset;	

	
	/* 线程就绪列表初始化 */
	for (offset = 0; offset < THREAD_PRIORITY_MAX; offset ++)
	{
        
			k_list_init(&thread_priority_table[offset]);
	}
	
	/* 初始化当前线程控制块指针 */
	current_thread = NULL;
	
	/* 初始化线程休眠列表，当线程创建好没有启动之前会被放入到这个列表 */
	k_list_init(&thread_defunct);
}


/* 启动系统调度器 */
void system_scheduler_start(void)
{
	register thread_t *to_thread;
	

	/* 手动指定第一个运行的线程 */
	to_thread = k_list_entry(thread_priority_table[0].next,
							  thread_t,
							  tlist);
	current_thread = to_thread;
														
	/* 切换到第一个线程，该函数在context_rvds.S中实现，
       用于实现第一次任务切换。当一个汇编函数在C文件中调用的时候，
       如果有形参，则执行的时候会将形参传人到CPU寄存器r0。*/
	cpu_hw_context_switch_to((uint32_t)&(current_thread->sp));
}


/* 系统调度 */
void schedule(void)
{
	 thread_t *to_thread;
	 thread_t *from_thread;
	
	
	
	/* 两个线程轮流切换 */
	if( current_thread == k_list_entry( thread_priority_table[0].next,
                                                                thread_t,
                                                                tlist) )
	{
		from_thread = current_thread;
		to_thread = k_list_entry( thread_priority_table[1].next,
													               thread_t,
													               tlist);
	  current_thread = to_thread;
	}
	else
	{
		from_thread = current_thread;
		to_thread = k_list_entry( thread_priority_table[0].next,
																		 thread_t,
																		 tlist);
	  current_thread = to_thread;																		 
	}
	
	/* 产生上下文切换 */
	cpu_hw_context_switch((uint32_t)&from_thread->sp,(uint32_t)&to_thread->sp);	
	
}
