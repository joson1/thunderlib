#include <kernel/thread.h>
#include <kernel/klist.h>


ALIGN(4)
/* 定义线程栈 */
static uint8_t idle_thread_stack[512];

static thread_t thread_idle;

extern k_list_t thread_priority_table[THREAD_PRIORITY_MAX];


unsigned long  idletask_ctr = 0;

void thread_idle_entry(void *parameter)
{
    parameter = parameter;
    while (1)
    {
        idletask_ctr ++;
    }
}

void thread_idle_init(void)
{
	/* 初始化线程 */
	thread_init( &thread_idle,                 /* 线程控制块 */
					&thread_priority_table[0],
	                thread_idle_entry,               /* 线程入口地址 */
	                NULL,                          /* 线程形参 */
	                &idle_thread_stack[0],        /* 线程栈起始地址 */
	                sizeof(idle_thread_stack) );  /* 线程栈大小，单位为字节 */

	printf("thread_idle_init init\r\n");
	

}

