#include <kernel/thread.h>

/*
*************************************************************************
*                                 数据类型
*************************************************************************
*/
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
};

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

    struct exception_stack_frame exception_stack_frame;
};
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


/*
*************************************************************************
*                                 函数实现
*************************************************************************
*/
/* 线程栈初始化 */
uint8_t *cpu_hw_stack_init(  void       *tentry,
                             void       *parameter,
                             uint8_t *stack_addr)
{
	
	
	struct stack_frame *stack_frame;
	uint8_t         *stk;
	unsigned long       i;
	
	
	/* 获取栈顶指针
	 rt_hw_stack_init 在调用的时候，传给stack_addr的是(栈顶指针)*/
	stk  = stack_addr + sizeof(uint32_t);
	
	/* 让stk指针向下8字节对齐 */
	stk  = (uint8_t *)ALIGN_DOWN((uint32_t)stk, 8);
	
	/* stk指针继续向下移动sizeof(struct stack_frame)个偏移 */
	stk -= sizeof(struct stack_frame);
	
	/* 将stk指针强制转化为stack_frame类型后存到stack_frame */
	stack_frame = (struct stack_frame *)stk;
	
	/* 以stack_frame为起始地址，将栈空间里面的sizeof(struct stack_frame)
	个内存初始化为0xdeadbeef */
	for (i = 0; i < sizeof(struct stack_frame) / sizeof(uint32_t); i ++)
	{
			((uint32_t *)stack_frame)[i] = 0xdeadbeef;
	}
	
	/* 初始化异常发生时自动保存的寄存器 */
	stack_frame->exception_stack_frame.r0  = (unsigned long)parameter; /* r0 : argument */
	stack_frame->exception_stack_frame.r1  = 0;                        /* r1 */
	stack_frame->exception_stack_frame.r2  = 0;                        /* r2 */
	stack_frame->exception_stack_frame.r3  = 0;                        /* r3 */
	stack_frame->exception_stack_frame.r12 = 0;                        /* r12 */
	stack_frame->exception_stack_frame.lr  = 0;                        /* lr */
	stack_frame->exception_stack_frame.pc  = (unsigned long)tentry;    /* entry point, pc */
	stack_frame->exception_stack_frame.psr = 0x01000000L;              /* PSR */
	
	/* 返回线程栈指针 */
	return stk;
}

