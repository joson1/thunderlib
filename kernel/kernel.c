#include <kernel/kernel.h>
#include <malloc.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
thread_t* thread_create(
                    const char* name,
                    void    (*entry)(void* par),
                    void    *par,
                    void    (*exit)(void),
                    uint32_t stack_size,
                    uint32_t priority,
                    uint32_t cpuid
                    )
{

    uint8_t* pstack;
    thread_t* pthread;

    pthread = (thread_t*)malloc(sizeof(*pthread));
    if(!pthread) return 0;
    memset(pthread,0,sizeof(*pthread));
    pthread->entry = entry;
    pthread->parameter = par;
    pthread->exit = exit;
    pthread->priority = priority;
    pstack = (uint8_t*)malloc(stack_size);
    if(!pstack) return 0;
    memset(pstack,0,stack_size);
    pthread->stack_addr = pstack;
    pthread->stack_size =stack_size;
    printf("pthread:0x%08x\tpstack:0x%08x\r\n",pthread,pstack);
    pthread->cpuid = cpuid;

    
     thread_init(pthread,
						name,
                        pthread->entry,
                        pthread->parameter,
                        pthread->exit,
                        pthread->stack_addr,
                        pthread->stack_size,
                        pthread->priority,
                        cpuid
                    );

    return pthread;
}

k_err_t thread_destroy(thread_t* pthread)
{
    free(pthread->stack_addr);
    free(pthread);
    return 0;
}
