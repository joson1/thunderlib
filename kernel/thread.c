#include <kernel/thread.h>





k_err_t thread_init(thread_t *thread,
                        void (*entry)(void *parameter),
                        void             *parameter,
                        void             *stack_start,
                        uint32_t       stack_size)
{

    k_list_init(&(thread->tlist));
    thread->entry = (void*)entry;
	thread->parameter = parameter;

	thread->stack_addr = stack_start;
	thread->stack_size = stack_size;
	/* 初始化线程栈，并返回线程栈指针 */
	thread->sp = (void *)cpu_hw_stack_init( thread->entry, 
		                                   thread->parameter,
							               (void *)((char *)thread->stack_addr + thread->stack_size - 4) );
	    
}
                        
k_err_t rt_thread_resume(thread_t* thread);
												
k_err_t rt_thread_startup(thread_t* thread);
