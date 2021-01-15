/*
 * @Author: your name
 * @Date: 1970-01-01 08:00:00
 * @LastEditTime: 2021-01-13 11:23:09
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /ThunderLib/arch/arm/xilinx/zynq/trap.c
 */
#include <kernel/kernel.h>
#include <stdio.h>

extern thread_t* pCurrentThread;

extern void show_register(struct stack_frame *regs);

void show_register(struct stack_frame *regs)
{
    printf("Execption:\r\n");
    printf("r00:0x%08x r01:0x%08x r02:0x%08x r03:0x%08x\r\n",regs->exception_stack_frame.r0,regs->exception_stack_frame.r1,regs->exception_stack_frame.r2,regs->exception_stack_frame.r3);
    printf("r04:0x%08x r05:0x%08x r06:0x%08x r07:0x%08x\r\n",regs->r4,regs->r5,regs->r6,regs->r7);
    printf("r08:0x%08x r09:0x%08x r10:0x%08x\r\n",regs->r8,regs->r9,regs->r10);
    printf("fp :0x%08x ip :0x%08x\r\n",regs->r11,regs->exception_stack_frame.r12);
    printf("sp :0x%08x lr :0x%08x pc :0x%08x\r\n",(pCurrentThread->sp),regs->exception_stack_frame.lr,regs->exception_stack_frame.pc);
    // printf("cpsr:0x%08x\n");
}

extern void show_stack(void* sp);

void show_stack(void* sp)
{
    uint32_t* pp = (uint32_t*)sp;
    size_t i;
    printf("Stack:\r\n");
    for (i = 0; i < 512;)
    {
        printf("%08X ",*pp);
        pp++;
         i++;
        if (i%8==0)
        {
            printf("\r\n");
        }
    }
    printf("\r\n End of Stack \r\n");
    
    
}
extern void trap_dabt();

void trap_dabt()
{
    printf("Current thread:%s\r\n",pCurrentThread->name);
  show_register((struct stack_frame *)(pCurrentThread->sp));
  show_stack(pCurrentThread->sp);
}


