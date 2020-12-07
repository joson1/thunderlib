#pragma once

#include "kdefs.h"
#include "klist.h"


#define THREAD_PRIORITY_MAX 10

typedef struct 
{
    void*   sp;        /* 线程栈指针 */
    void*   entry;     /* 线程入口地址 */
    void*   parameter; /* 线程形参 */
    void*   stack_addr;/* 线程栈起始地址 */
    uint32_t stack_size;
    k_list_t tlist;     /**/
}thread_t;

k_err_t thread_init(thread_t *thread,
                        void (*entry)(void *parameter),
                        void             *parameter,
                        void             *stack_start,
                        uint32_t       stack_size);
												
k_err_t thread_resume(thread_t* thread);
												
k_err_t thread_startup(thread_t* thread);




void system_scheduler_init(void);
void schedule_insert_thread(thread_t *thread);
void system_scheduler_start(void);

void schedule(void);

uint8_t *cpu_hw_stack_init(void         *tentry,
                             void       *parameter,
                             uint8_t    *stack_addr);
														 


void cpu_hw_context_switch(uint32_t from, uint32_t to);
void cpu_hw_context_switch_to(uint32_t to);
void cpu_hw_context_switch_interrupt(uint32_t from, uint32_t to);
														 

