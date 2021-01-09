

@*************************************************************************
@                                 全局变量
@*************************************************************************
.global cpu_thread_switch_interrupt_flag
.global cpu_interrupt_from_thread
.global cpu_interrupt_to_thread
#define NOINT           0xc0 


@*************************************************************************
@                                 常量
@*************************************************************************
@-------------------------------------------------------------------------
.equ DISABLE_IRQ, 0x80
.equ DISABLE_FIQ, 0x40

.equ SYS_MOD, 0x1f
.equ IRQ_MOD, 0x12
.equ FIQ_MOD, 0x11
.equ SVC_MOD, 0x13
.equ ABT_MOD, 0x17
.equ UND_MOD, 0x1b

.global cpu_hw_context_switch_to
cpu_hw_context_switch_to:
    
	@ 导出cpu_hw_context_switch，让其具有全局属性，可以在C文件调用

    @ 设置cpu_interrupt_to_thread的值
    LDR     r1, =cpu_interrupt_to_thread             @将cpu_interrupt_to_thread的地址加载到r1
    STR     r0, [r1]                                @将r0的值存储到cpu_interrupt_to_thread

    @ 设置cpu_interrupt_from_thread的值为0，表示启动第一次线程切换
    LDR     r1, =cpu_interrupt_from_thread           @将cpu_interrupt_from_thread的地址加载到r1
    MOV     r0, #0x0                                @配置r0等于0
    STR     r0, [r1]                                @将r0的值存储到cpu_interrupt_from_thread

    @ 设置中断标志位cpu_thread_switch_interrupt_flag的值为1
    LDR     r1, =cpu_thread_switch_interrupt_flag    @将cpu_thread_switch_interrupt_flag的地址加载到r1
    MOV     r0, #1                                  @配置r0等于1
    STR     r0, [r1]                                @将r0的值存储到cpu_thread_switch_interrupt_flag


    @ 触发 SWI 异常 (产生上下文切换)
    SWI    0

    @ 保证中断开启

    @ 永远不会到达这里


;/*
; *-----------------------------------------------------------------------
; * void rt_hw_context_switch(rt_uint32 from, rt_uint32 to);
; * r0 --> from
; * r1 --> to
; *-----------------------------------------------------------------------
; */
.global cpu_hw_context_switch

cpu_hw_context_switch:

    @ 设置中断标志位cpu_thread_switch_interrupt_flag为1     
    LDR     r2, =cpu_thread_switch_interrupt_flag          @ 加载cpu_thread_switch_interrupt_flag的地址到r2
    LDR     r3, [r2]                                      @ 加载cpu_thread_switch_interrupt_flag的值到r3
    CMP     r3, #1                                        @ r3与1比较，相等则执行BEQ指令，否则不执行
    BEQ     _reswitch
    MOV     r3, #1                                        @ 设置r3的值为1
    STR     r3, [r2]                                      @ 将r3的值存储到cpu_thread_switch_interrupt_flag，即置1
    
	@ 设置cpu_interrupt_from_thread的值
    LDR     r2, =cpu_interrupt_from_thread                 @ 加载cpu_interrupt_from_thread的地址到r2
    STR     r0, [r2]                                      @ 存储r0的值到cpu_interrupt_from_thread，即上一个线程栈指针sp的指针

_reswitch:
    @ 设置cpu_interrupt_to_thread的值
	LDR     r2, =cpu_interrupt_to_thread                   @ 加载cpu_interrupt_from_thread的地址到r2
    STR     r1, [r2]                                      @ 存储r1的值到cpu_interrupt_from_thread，即下一个线程栈指针sp的指针

    @ @ 触发SWI异常，实现上下文切换

	SWI     0
    @ 子程序返回
	BX      LR
	
	@ 子程序结束



/*
 * extern uint32_t cpu_hw_interrupt_disable();
 */
.globl cpu_hw_interrupt_disable
cpu_hw_interrupt_disable:
    mrs r0, cpsr
    orr r1, r0, #NOINT
    msr cpsr_c, r1
    bx  lr
/*
 * extern void cpu_hw_interrupt_enable(uint32_t level);
 */
.globl cpu_hw_interrupt_enable
cpu_hw_interrupt_enable:
    msr cpsr, r0
    bx  lr
