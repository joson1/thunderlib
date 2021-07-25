/*
 * @Author: your name
 * @Date: 1970-01-01 08:00:00
 * @LastEditTime: 2021-01-13 11:23:09
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /ThunderLib/arch/arm/xilinx/zynq7000/trap.c
 */
#include <kernel/kernel.h>
#include <stdio.h>

extern thread_t* pCurrentThread;
struct stack_frame
{
    /* r4 ~ r11 register 
	  异常发生时需手动保存的寄存器 */
    uint32_t r4;
    uint32_t r5;
    uint32_t r6;
    uint32_t r7;
    uint32_t r8;
    uint32_t r9;
    uint32_t r10;
    uint32_t r11;

    struct exception_stack_frame
    {
        /* 异常发生时自动保存的寄存器 */
        uint32_t r0;
        uint32_t r1;
        uint32_t r2;
        uint32_t r3;
        uint32_t r12;
        uint32_t lr;
        uint32_t pc;
        uint32_t psr;
    } exception_stack_frame;
};

extern void show_register(struct stack_frame *regs);

void show_register(struct stack_frame *regs)
{
    printf("Execption:\r\n"); 
    printf("r00:0x%08lx r01:0x%08lx r02:0x%08lx r03:0x%08lx\r\n",regs->exception_stack_frame.r0,regs->exception_stack_frame.r1,regs->exception_stack_frame.r2,regs->exception_stack_frame.r3);
    printf("r04:0x%08lx r05:0x%08lx r06:0x%08lx r07:0x%08lx\r\n",regs->r4,regs->r5,regs->r6,regs->r7);
    printf("r08:0x%08lx r09:0x%08lx r10:0x%08lx\r\n",regs->r8,regs->r9,regs->r10);
    printf("fp :0x%08lx ip :0x%08lx\r\n",regs->r11,regs->exception_stack_frame.r12);
    printf("sp :0x%08lx lr :0x%08lx pc :0x%08lx\r\n",(pCurrentThread->sp),regs->exception_stack_frame.lr,regs->exception_stack_frame.pc);
    // printf("cpsr:0x%08lx\n");
}

extern void show_stack(void* sp);

void show_stack(void* sp)
{
    uint32_t* pp = (uint32_t*)sp;
    size_t i;
    printf("Stack:\r\n");
    for (i = 0; i < 512;)
    {
        printf("%08lX ",*pp);
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


