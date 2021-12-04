

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
    ldr     sp, [r0]
#if defined (__VFP_FP__) && !defined(__SOFTFP__)
    ldmfd sp!, {r1}				/* Restore floating point registers */
    vmsr FPEXC, r1
    ldmfd sp!, {r1}
    vmsr FPSCR, r1
    vldmia sp!, {d0-d15}
#endif

    ldmfd   sp!,{r4}
    @ mov     r0, sp
    msr     spsr_cxsf, r4

    bic     r4,r4,#0x20
    msr     cpsr_cxsf, r4

    ldmfd   sp!,{r0-r12,lr,pc}
	
    /* 使能全局中断 */
    @ mrs r0, cpsr
    @ and r1,r0,#0x3f
    @ msr cpsr_c, r1
    @ bx  lr

    @ 触发 SWI 异常 (产生上下文切换)
    @ SWI    0
    @ NOP {0}
    @ 保证中断开启

    @ 永远不会到达这里


;/*
; *-----------------------------------------------------------------------
; * void cpu_hw_context_switch(uint32 from, uint32 to);
; * r0 --> from
; * r1 --> to
; *-----------------------------------------------------------------------
; */
.global cpu_hw_context_switch

cpu_hw_context_switch:
    stmfd   sp!,{lr}
    stmfd   sp!,{r0-r12,lr}

    mrs     r4,cpsr
    tst     lr,#0x01
    beq     _ARM_MODE
    orr     r4,r4,#0x20

_ARM_MODE:
    stmfd   sp!,{r4}
#if defined (__VFP_FP__) && !defined(__SOFTFP__)
    vstmdb sp!, {d0-d15}     /* Store floating point registers */
    vmrs r4, FPSCR
    stmfd sp!,{r4}
    vmrs r4, FPEXC
    stmfd sp!,{r4}
#endif
    str sp, [r0]            @ store sp in preempted tasks TCB
    ldr sp, [r1]            @ get new task stack pointer
#if defined (__VFP_FP__) && !defined(__SOFTFP__)
    ldmfd sp!, {r1}				/* Restore floating point registers */
    vmsr FPEXC, r1
    ldmfd sp!, {r1}
    vmsr FPSCR, r1
    vldmia sp!, {d0-d15}
#endif

    ldmfd sp!, {r4}         @ pop new task cpsr to spsr
    msr spsr_cxsf, r4

    ldmfd sp!, {r0-r12, lr, pc}^  @ pop new task r0-r12, lr & pc, copy spsr to cpsr

@ (r0:uint32_t from,r1:uint32_t to);
.globl cpu_hw_context_switch_interrupt
cpu_hw_context_switch_interrupt:

    mrc     p15, #0, r4, c0, c0, #5
    and     r4, r4,#15

    ldr r2, =cpu_thread_switch_interrupt_flag
    add r2, r2, r4,LSL #2 
    ldr r3, [r2]

    cmp r3, #1
    beq _reswitch
    mov r3, #1              @ set cpu_thread_switch_interrupt_flag to 1
    str r3, [r2]
    ldr r2, =cpu_interrupt_from_thread   @ set cpu_interrupt_from_thread
    str r0, [r2,r4,LSL #2]
_reswitch:
    ldr r2, =cpu_interrupt_to_thread     @ set cpu_interrupt_to_thread
    str r1, [r2,r4,LSL #2]
    bx  lr


/*
 * extern uin32_t cpu_interrupt_disable();
 */
.globl cpu_interrupt_disable
cpu_interrupt_disable:
    mrs r0, cpsr
    orr r1, r0, #NOINT
    msr cpsr_c, r1
    bx  lr
/*
 * extern void cpu_interrupt_enable(uint32_t level);
 */
.globl cpu_interrupt_enable
cpu_interrupt_enable:
    msr cpsr , r0
    @ mrs r0, cpsr
    @ and r1,r0,#0x3f
    @ msr cpsr_c, r1
    bx  lr

/*
 * extern void cpu_interrupt_enable_f();
 */
.globl cpu_interrupt_enable_f
cpu_interrupt_enable_f:
    mrs r0, cpsr
    and r1,r0,#0x3f
    msr cpsr_c, r1
    bx  lr
