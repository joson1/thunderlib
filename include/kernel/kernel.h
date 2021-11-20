/*
 * @Author: your name
 * @Date: 1970-01-01 08:00:00
 * @LastEditTime: 2021-01-11 19:47:48
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: /ThunderLib/include/kernel/kernel.h
 */
#include "kdefs.h"
#include <kernel/thread.h>
#include <thunder/init.h>


#define KERNEL_INIT(fn)		__define_initcall("1", fn, 0)

thread_t* thread_create(
                    const char* name,
                    void    (*entry)(void* par),
                    void    *par,
                    void    (*exit)(void),
                    uint32_t stack_size,
                    uint32_t priority,
                    uint32_t cpuid
                    );

