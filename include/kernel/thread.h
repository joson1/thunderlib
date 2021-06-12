/*
 * @Author: your name
 * @Date: 2020-11-29 11:18:39
 * @LastEditTime: 2021-01-13 22:53:02
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\include\kernel\thread.h
 */
#pragma once

#include "kdefs.h"
#include <xlist.h>

#define THREAD_PRIORITY_MAX (10)
#define configMAX_TASK_NAME_LEN		            ( 16 )
#define configMAX_PRIORITIES                     THREAD_PRIORITY_MAX  


#define THREAD_STATUS_INIT                  0x00                /* 初始态 */
#define THREAD_STATUS_READY                 0x01                /* 就绪态 */
#define THREAD_STATUS_SUSPEND               0x02                /* 挂起态 */
#define THREAD_STATUS_RUNNING               0x03                /* 运行态 */
#define THREAD_STATUS_BLOCK                 THREAD_STATUS_SUSPEND   /* 阻塞态 */
#define THREAD_STATUS_CLOSE                 0x04                /* 关闭态 */
#define THREAD_STATUS_STAT_MASK             0x0f

// struct exception_stack_frame
// {
//     /* 异常发生时自动保存的寄存器 */
// 	uint32_t r0;
//     uint32_t r1;
//     uint32_t r2;
//     uint32_t r3;
//     uint32_t r12;
//     uint32_t lr;
//     uint32_t pc;
//     uint32_t psr;
// };

// struct stack_frame
// {
//     /* r4 ~ r11 register 
// 	  异常发生时需手动保存的寄存器 */
//     uint32_t r4;
//     uint32_t r5;
//     uint32_t r6;
//     uint32_t r7;
//     uint32_t r8;
//     uint32_t r9;
//     uint32_t r10;
//     uint32_t r11;

//     struct exception_stack_frame exception_stack_frame;
// };

typedef struct 
{
    void*   sp;        /* 线程栈指针 */
    void    (*entry)(void* parameter);     /* 线程入口地址 */
    void*   parameter; /* 线程形参 */
    void    (*exit)(void* pthread);     /* 线程出口地址 */
    void*   stack_addr;/* 线程栈起始地址 */
    char    name[configMAX_TASK_NAME_LEN];
    uint8_t status;
    uint32_t stack_size;
    uint32_t remaining_tick;

    uint8_t     current_priority;     /* 当前优先级 */
    uint8_t     priority;           /* 初始优先级 */
    uint8_t     number_mask;          /* 当前优先级掩码 */
    
    uint32_t    ticks_to_delay;         /* delay */

    ListItem_t tListItem;     /**/
}thread_t;

k_err_t thread_init(thread_t *thread,
						const char* name,
                        void (*entry)(void *parameter),
                        void             *parameter,
                        void (*exit)(void),
                        void             *stack_start,
                        uint32_t       stack_size,
						uint32_t 		priority);

k_err_t thread_resume(thread_t* thread);
												
k_err_t thread_startup(thread_t* thread);




void system_scheduler_init(void);
void schedule_insert_thread(thread_t *thread);
void system_scheduler_start(void);

void schedule(void);

uint8_t *cpu_hw_stack_init(  void       *tentry,
                             void       *parameter,
                             void       *exit,
                             uint8_t *stack_addr);				 


void cpu_hw_context_switch(uint32_t from, uint32_t to);
void cpu_hw_context_switch_to(uint32_t to);
void cpu_hw_context_switch_interrupt(uint32_t from, uint32_t to);
														 

void sys_delay(uint32_t ticks);

void thread_idle_init(void);
