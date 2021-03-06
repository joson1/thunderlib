/*
 * @Author: your name
 * @Date: 1970-01-01 08:00:00
 * @LastEditTime: 2021-01-15 22:29:23
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /ThunderLib/arch/arm/xilinx/zynq7000/platfromcpu.c
 */
#include <kernel/thread.h>
#define VFP_DATA_NR 32
/*
*************************************************************************
*                                 数据类型
*************************************************************************
*/

/*
*************************************************************************
*                                 全局变量
*************************************************************************
*/

/* 用于存储上一个线程的栈的sp的指针 */
uint32_t cpu_interrupt_from_thread = 0;

/* 用于存储下一个将要运行的线程的栈的sp的指针 */
uint32_t cpu_interrupt_to_thread = 0;

/* SWI中断服务函数执行标志 */
uint32_t cpu_thread_switch_interrupt_flag = 0;


extern void task_ed();

/*
*************************************************************************
*                                 函数实现
*************************************************************************
*/
/* 线程栈初始化 */
// uint8_t *cpu_hw_stack_init(  void       *tentry,
//                              void       *parameter,
//                              uint8_t *stack_addr)
// {
	
	
// 	struct stack_frame *stack_frame;
// 	uint8_t         *stk;
// 	unsigned long       i;
	
	
// 	/* 获取栈顶指针
// 	 rt_hw_stack_init 在调用的时候，传给stack_addr的是(栈顶指针)*/
// 	stk  = stack_addr + sizeof(uint32_t);
	
// 	/* 让stk指针向下8字节对齐 */
// 	stk  = (uint8_t *)ALIGN_DOWN((uint32_t)stk, 8);
	
// 	/* stk指针继续向下移动sizeof(struct stack_frame)个偏移 */
// 	stk -= sizeof(struct stack_frame);
	
// 	/* 将stk指针强制转化为stack_frame类型后存到stack_frame */
// 	stack_frame = (struct stack_frame *)stk;
	
// 	/* 以stack_frame为起始地址，将栈空间里面的sizeof(struct stack_frame)
// 	个内存初始化为0xdeadbeef */
// 	for (i = 0; i < sizeof(struct stack_frame) / sizeof(uint32_t); i ++)
// 	{
// 			((uint32_t *)stack_frame)[i] = 0xdeadbeef;
// 	}
	
// 	/* 初始化异常发生时自动保存的寄存器 */
// 	stack_frame->exception_stack_frame.r0  = (unsigned long)parameter; /* r0 : argument */
// 	stack_frame->exception_stack_frame.r1  = 0;                        /* r1 */
// 	stack_frame->exception_stack_frame.r2  = 0;                        /* r2 */
// 	stack_frame->exception_stack_frame.r3  = 0;                        /* r3 */
// 	stack_frame->r4  = 0x193;                        					/*r4*/
// 	stack_frame->exception_stack_frame.r12 = 0;                        /* r12 */
// 	stack_frame->exception_stack_frame.lr  = (uint32_t)task_ed;                        /* lr */
// 	stack_frame->exception_stack_frame.pc  = (unsigned long)tentry;    /* entry point, pc */
// 	stack_frame->exception_stack_frame.psr = 0x01000000L;              /* PSR */
	
// 	/* 返回线程栈指针 */
// 	return stk;
// }
// #define FPU_HARD_FLOAT_ABI_ENABLED 1

// uint8_t *cpu_hw_stack_init(  void       *tentry,
//                              void       *parameter,
//                              void       *exit,
//                              uint8_t *stack_addr)
// {
	
//     uint32_t *stk;

//     stack_addr += sizeof(uint32_t);
//     stack_addr  = (uint8_t *)ALIGN_DOWN((uint32_t)stack_addr, 8);
//     stk      = (uint32_t *)stack_addr;
//     *(--stk) = (uint32_t)tentry;         /* entry point */
//     *(--stk) = (uint32_t)task_ed;          /* lr */
//     *(--stk) = 0xdeadbeef;                  /* r12 */
//     *(--stk) = 0xdeadbeef;                  /* r11 */
//     *(--stk) = 0xdeadbeef;                  /* r10 */
//     *(--stk) = 0xdeadbeef;                  /* r9 */
//     *(--stk) = 0xdeadbeef;                  /* r8 */
//     *(--stk) = 0xdeadbeef;                  /* r7 */
//     *(--stk) = 0xdeadbeef;                  /* r6 */
//     *(--stk) = 0xdeadbeef;                  /* r5 */
//     *(--stk) = 0xdeadbeef;                  /* r4 */
//     *(--stk) = 0xdeadbeef;                  /* r3 */
//     *(--stk) = 0xdeadbeef;                  /* r2 */
//     *(--stk) = 0xdeadbeef;                  /* r1 */
//     *(--stk) = (uint32_t)parameter;      /* r0 : argument */

//     /* cpsr */

//     *(--stk) = SVCMODE;                 /* arm mode   */
// #if defined (__VFP_FP__) && !defined(__SOFTFP__)
//     {
//         int i;
//         for (i = 0; i < VFP_DATA_NR; i++)
//         {
//             *(--stk) = 0;
//         }
//         /* FPSCR TODO: do we need to set the values other than 0? */
//         *(--stk) = 0;
//         /* FPEXC. Enable the FVP if no lazy stacking. */
//         *(--stk) = 0x40000000;
//     }
// #endif
//     /* return task's current stack address */
//     return (uint8_t *)stk;
// }

extern void task_ed();

#define USE_FPU 1
struct exception_stack_frame
{
    uint32_t r0;
    uint32_t r1;
    uint32_t r2;
    uint32_t r3;
    uint32_t r12;
    uint32_t lr;
    uint32_t pc;
    uint32_t psr;
};

struct stack_frame
{
#if USE_FPU
    uint32_t flag;
#endif /* USE_FPU */

    /* r4 ~ r11 register */
    uint32_t r4;
    uint32_t r5;
    uint32_t r6;
    uint32_t r7;
    uint32_t r8;
    uint32_t r9;
    uint32_t r10;
    uint32_t r11;

    struct exception_stack_frame exception_stack_frame;
};

struct exception_stack_frame_fpu
{
    uint32_t r0;
    uint32_t r1;
    uint32_t r2;
    uint32_t r3;
    uint32_t r12;
    uint32_t lr;
    uint32_t pc;
    uint32_t psr;

#if USE_FPU
    /* FPU register */
    uint32_t S0;
    uint32_t S1;
    uint32_t S2;
    uint32_t S3;
    uint32_t S4;
    uint32_t S5;
    uint32_t S6;
    uint32_t S7;
    uint32_t S8;
    uint32_t S9;
    uint32_t S10;
    uint32_t S11;
    uint32_t S12;
    uint32_t S13;
    uint32_t S14;
    uint32_t S15;
    uint32_t FPSCR;
    uint32_t NO_NAME;
#endif
};

struct stack_frame_fpu
{
    uint32_t flag;

    /* r4 ~ r11 register */
    uint32_t r4;
    uint32_t r5;
    uint32_t r6;
    uint32_t r7;
    uint32_t r8;
    uint32_t r9;
    uint32_t r10;
    uint32_t r11;

#if USE_FPU
    /* FPU register s16 ~ s31 */
    uint32_t s16;
    uint32_t s17;
    uint32_t s18;
    uint32_t s19;
    uint32_t s20;
    uint32_t s21;
    uint32_t s22;
    uint32_t s23;
    uint32_t s24;
    uint32_t s25;
    uint32_t s26;
    uint32_t s27;
    uint32_t s28;
    uint32_t s29;
    uint32_t s30;
    uint32_t s31;
#endif

    struct exception_stack_frame_fpu exception_stack_frame;
};

// uint8_t *cpu_hw_stack_init(  void       *tentry,
//                              void       *parameter,
//                              void       *exit,
//                              uint8_t *stack_addr)
// {

uint8_t *cpu_hw_stack_init(void       *tentry,
                             void       *parameter,
                             void       *texit,
                             uint8_t *stack_addr)
{
    struct stack_frame *stack_frame;
    uint8_t         *stk;
    unsigned long       i;

    stk  = stack_addr + sizeof(uint32_t);
    stk  = (uint8_t *)ALIGN_DOWN((uint32_t)stk, 8);
    stk -= sizeof(struct stack_frame);

    stack_frame = (struct stack_frame *)stk;

    /* init all register */
    for (i = 0; i < sizeof(struct stack_frame) / sizeof(uint32_t); i ++)
    {
        ((uint32_t *)stack_frame)[i] = 0xdeadbeef;
    }

    stack_frame->exception_stack_frame.r0  = (unsigned long)parameter; /* r0 : argument */
    stack_frame->exception_stack_frame.r1  = 0;                        /* r1 */
    stack_frame->exception_stack_frame.r2  = 0;                        /* r2 */
    stack_frame->exception_stack_frame.r3  = 0;                        /* r3 */
    stack_frame->exception_stack_frame.r12 = 0;                        /* r12 */
    stack_frame->exception_stack_frame.lr  = (unsigned long)task_ed;     /* lr */
    stack_frame->exception_stack_frame.pc  = (unsigned long)tentry;    /* entry point, pc */
    stack_frame->exception_stack_frame.psr = 0x01000000L;              /* PSR */

#if USE_FPU
    stack_frame->flag = 0;
#endif /* USE_FPU */

    /* return task's current stack address */
    return stk;
}
