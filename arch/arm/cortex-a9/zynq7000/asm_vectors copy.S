/******************************************************************************
*
* Copyright (C) 2009 - 2018 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/
/*****************************************************************************/
/**
* @file asm_vectors.s
*
* This file contains the initial vector table for the Cortex A9 processor
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who     Date     Changes
* ----- ------- -------- ---------------------------------------------------
* 1.00a ecm/sdm 10/20/09 Initial version
* 3.05a sdm	02/02/12 Save lr when profiling is enabled
* 3.10a srt     04/18/13 Implemented ARM Erratas. Please refer to file
*			 'xil_errata.h' for errata description
* 4.00a pkp	22/01/14 Modified return addresses for interrupt
*			 handlers (DataAbortHandler and SVCHandler)
*			 to fix CR#767251
* 5.1	pkp	05/13/15 Saved the addresses of instruction causing data
*			 abort and prefetch abort into DataAbortAddr and
*			 PrefetchAbortAddr for further use to fix CR#854523
* 5.4	pkp	12/03/15 Added handler for undefined exception
* 6.8	mus	04/27/18 Removed __ARM_NEON__ flag definition. Now,
*			 saving/restoring of of HW floating point register
*			 would be done through newly introduced flag
*			 FPU_HARD_FLOAT_ABI_ENABLED. This new flag will be
*			 configured based on the -mfpu-abi option in extra
*			 compiler flags.
* </pre>
*
* @note
*
* None.
*
******************************************************************************/
#include "zynq7000/xil_errata.h"
#include "zynq7000/bspconfig.h"

.org 0
.text

.globl _vector_table
.global cpu_thread_switch_interrupt_flag
.global cpu_thread_switch_interrupt_flag1
.global cpu_interrupt_from_thread
.global cpu_interrupt_from_thread1
.global cpu_interrupt_to_thread
.global cpu_interrupt_to_thread1
    
.equ Mode_USR,        0x10
.equ Mode_FIQ,        0x11
.equ Mode_IRQ,        0x12
.equ Mode_SVC,        0x13
.equ Mode_ABT,        0x17
.equ Mode_UND,        0x1B
.equ Mode_SYS,        0x1F

.equ I_Bit,           0x80            @ when I bit is set, IRQ is disabled
.equ F_Bit,           0x40            @ when F bit is set, FIQ is disabled

.section .vectors
_vector_table:
	B	_boot
	B	Undefined
	B	SVCHandler
	B	PrefetchAbortHandler
	B	DataAbortHandler
	NOP	/* Placeholder for address exception vector*/
	B	IRQHandler
	B	FIQHandler


IRQHandler:					/* IRQ vector handler */
	sub		lr,	lr,#4
	stmdb	sp!,{r0-r12,lr}		/* state save from compiled code*/
#if defined (__VFP_FP__) && !defined(__SOFTFP__)
    vstmdb sp!, {d0-d15}     /* Store floating point registers */
    vmrs r1, FPSCR
    stmfd sp!,{r1}
    vmrs r1, FPEXC
    stmfd sp!,{r1}
#endif

@ #ifdef PROFILING
@ 	ldr	r2, =prof_pc
@ 	subs	r3, lr, #0
@ 	str	r3, [r2]
@ #endif

	bl	IRQInterrupt			/* IRQ vector */



    @ if cpu_thread_switch_interrupt_flag set, jump to
    @ hw_context_switch_interrupt_do and don't return
    mrc     p15, #0, r4, c0, c0, #5
    and     r4, r4,#15
	cmp		r4, #0
	beq     proc0
	b       proc1


proc0:
    ldr     r0, =cpu_thread_switch_interrupt_flag
    ldr     r1, [r0]
    cmp     r1, #1
    beq     hw_context_switch_interrupt_do
#if defined (__VFP_FP__) && !defined(__SOFTFP__)
    ldmfd sp!, {r1}         /* Restore floating point registers */
    vmsr FPEXC, r1
    ldmfd sp!, {r1}
    vmsr FPSCR, r1
    vldmia sp!, {d0-d15}
#endif

@ #endif
    ldmfd   sp!, {r0-r12,pc}^
    @ subs    pc,  lr, #4

proc1:
    ldr     r0, =cpu_thread_switch_interrupt_flag1
    ldr     r1, [r0]
    cmp     r1, #1
    beq     hw_context_switch_interrupt_do
#if defined (__VFP_FP__) && !defined(__SOFTFP__)
    ldmfd sp!, {r1}         /* Restore floating point registers */
    vmsr FPEXC, r1
    ldmfd sp!, {r1}
    vmsr FPSCR, r1
    vldmia sp!, {d0-d15}
#endif

@ #endif
    ldmfd   sp!, {r0-r12,pc}^
    @ subs    pc,  lr, #4



hw_context_switch_interrupt_do:
    mov     r1,  #0         @ clear flag
    str     r1,  [r0]

#if defined (__VFP_FP__) && !defined(__SOFTFP__)
    ldmfd sp!, {r1}         /* Restore floating point registers */
    vmsr FPEXC, r1
    ldmfd sp!, {r1}
    vmsr FPSCR, r1
    vldmia sp!, {d0-d15}
#endif

    mov     r1, sp          @ r1 point to {r0-r3} in stack
    add     sp, sp, #4*4
    ldmfd   sp!, {r4-r12,lr}@ reload saved registers
    mrs     r0,  spsr       @ get cpsr of interrupt thread
    sub     r2,  lr, #4     @ save old task's pc to r2

    @ Switch to SVC mode with no interrupt. If the usr mode guest is
    @ interrupted, this will just switch to the stack of kernel space.
    @ save the registers in kernel space won't trigger data abort.
    msr     cpsr_c, #I_Bit|F_Bit|Mode_SVC

    stmfd   sp!, {r2}       @ push old task's pc
    stmfd   sp!, {r4-r12,lr}@ push old task's lr,r12-r4
    ldmfd   r1,  {r1-r4}    @ restore r0-r3 of the interrupt thread
    stmfd   sp!, {r1-r4}    @ push old task's r0-r3
    stmfd   sp!, {r0}       @ push old task's cpsr

#if defined (__VFP_FP__) && !defined(__SOFTFP__)
    vstmdb sp!, {d0-d15}    /* Store floating point registers */
    vmrs r1, FPSCR
    stmfd sp!,{r1}
    vmrs r1, FPEXC
    stmfd sp!,{r1}
#endif
    mrc     p15, #0, r4, c0, c0, #5
    and     r4, r4,#15
	cmp		r4, #0
	beq     handl0
	b       handl1
handl0:
    ldr     r4,  =cpu_interrupt_from_thread
    ldr     r5,  [r4]
    str     sp,  [r5]       @ store sp in preempted tasks's TCB

    ldr     r6,  =cpu_interrupt_to_thread
    ldr     r7,  [r6]
    ldr     sp,  [r7]       @ get new task's stack pointer

#if defined (__VFP_FP__) && !defined(__SOFTFP__)
    ldmfd sp!, {r1}         /* Restore floating point registers */
    vmsr FPEXC, r1
    ldmfd sp!, {r1}
    vmsr FPSCR, r1
    vldmia sp!, {d0-d15}
#endif

    ldmfd   sp!, {r4}       @ pop new task's cpsr to spsr
    msr     spsr_cxsf, r4

    ldmfd   sp!, {r0-r12,lr,pc}^ @ pop new task's r0-r12,lr & pc, copy spsr to cpsr

handl1:
    ldr     r4,  =cpu_interrupt_from_thread1
    ldr     r5,  [r4]
    str     sp,  [r5]       @ store sp in preempted tasks's TCB

    ldr     r6,  =cpu_interrupt_to_thread1
    ldr     r7,  [r6]
    ldr     sp,  [r7]       @ get new task's stack pointer

#if defined (__VFP_FP__) && !defined(__SOFTFP__)
    ldmfd sp!, {r1}         /* Restore floating point registers */
    vmsr FPEXC, r1
    ldmfd sp!, {r1}
    vmsr FPSCR, r1
    vldmia sp!, {d0-d15}
#endif

    ldmfd   sp!, {r4}       @ pop new task's cpsr to spsr
    msr     spsr_cxsf, r4

    ldmfd   sp!, {r0-r12,lr,pc}^ @ pop new task's r0-r12,lr & pc, copy spsr to cpsr









#if FPU_HARD_FLOAT_ABI_ENABLED
	pop 	{r1}
	vmsr    FPEXC, r1
	pop 	{r1}
	vmsr    FPSCR, r1
	vpop    {d16-d31}
	vpop    {d0-d7}
#endif
	ldmia	sp!,{r0-r12,pc}^		/* state restore from compiled code */


	@ subs	pc, lr, #4			/* adjust return */


FIQHandler:					/* FIQ vector handler */
	sub		lr,lr,#4
	stmdb	sp!,{r0-r12,lr}		/* state save from compiled code */
#if FPU_HARD_FLOAT_ABI_ENABLED
	vpush {d0-d7}
	vpush {d16-d31}
	vmrs r1, FPSCR
	push {r1}
	vmrs r1, FPEXC
	push {r1}
#endif

FIQLoop:
	bl	FIQInterrupt			/* FIQ vector */

#if FPU_HARD_FLOAT_ABI_ENABLED
	pop 	{r1}
	vmsr    FPEXC, r1
	pop 	{r1}
	vmsr    FPSCR, r1
	vpop    {d16-d31}
	vpop    {d0-d7}
#endif
	ldmia	sp!,{r0-r12,pc}		/* state restore from compiled code */
	@ subs	pc, lr, #4			/* adjust return */


Undefined:					/* Undefined handler */
	stmdb	sp!,{r0-r12,lr}		/* state save from compiled code */
	ldr     r0, =UndefinedExceptionAddr
	sub     r1, lr, #4
	str     r1, [r0]            		/* Store address of instruction causing undefined exception */

	bl	UndefinedException		/* UndefinedException: call C function here */
	ldmia	sp!,{r0-r12,pc}		/* state restore from compiled code */
	@ movs	pc, lr


SVCHandler:					/* SWI handler */

	mov		lr,r0
	bx lr
 	@ stmdb	sp!,{lr}
 	stmdb	sp!,{r0-r12,lr}
	ldmfd	sp!,{r0-r12,pc}
	@ msr cpsr_c,0x13|0x80
	@ msr cpsr_c,0x10
    @ mrs r0, cpsr
    @ and r1,r0,#0x3f
    @ msr cpsr_c, r1
    //获取中断标志位，看看是否为0
    LDR     r0, =cpu_thread_switch_interrupt_flag     //加载cpu_thread_switch_interrupt_flag的地址到r0
    LDR     r1, [r0]                                 //加载cpu_thread_switch_interrupt_flag的值到r1
	CMP 	r1,#0
    beq     SVC_exit                          //判断r1是否为0，为0则跳转到pendsv_exit

    //r1不为0则清0
    MOV     r1, #0x00
    STR     r1, [r0]                                 //将r1的值存储到cpu_thread_switch_interrupt_flag，即清0

    //判断cpu_interrupt_from_thread的值是否为0
    LDR     r0, =cpu_interrupt_from_thread            //加载cpu_interrupt_from_thread的地址到r0
    LDR     r1, [r0]                                 //加载cpu_interrupt_from_thread的值到r1
	cmp 	r1,#0
    beq     switch_to_thread                     //判断r1是否为0，为0则跳转到switch_to_thread
                                                     //第一次线程切换时cpu_interrupt_from_thread肯定为0，则跳转到switch_to_thread

@ //========================== 上文保存 ==============================
@     //当进入PendSVC Handler时，上一个线程运行的环境即：
@  	//xPSR，PC（线程入口地址），R14，R12，R3，R2，R1，R0（线程的形参）
@  	//这些CPU寄存器的值会自动保存到线程的栈中，剩下的r4~r11需要手动保存
    MOV     r1, sp                                  //获取线程栈指针到r1
	mrs		r4,spsr
    STMFD   r1!, {r4}                          //将CPU寄存器r4~r11的值存储到r1指向的地址(每操作一次地址将递减一次)
	
    LDR     r0, [r0]                                 //加载r0指向值到r0，即r0=cpu_interrupt_from_thread
    STR     r1, [r0]                                 //将r1的值存储到r0，即更新线程栈sp
	

	@ stmdb	sp!,{r0-r3,r12,lr}		/* state save from compiled code */

	@ tst	r0, #0x20			/* check the T bit */
	@ ldrneh	r0, [lr,#-2]			/* Thumb mode */
	@ bicne	r0, r0, #0xff00			/* Thumb mode */
	@ ldreq	r0, [lr,#-4]			/* ARM mode */
	@ biceq	r0, r0, #0xff000000		/* ARM mode */

switch_to_thread:
	LDR     r1, =cpu_interrupt_to_thread        @//获取线程栈指针到r1
	@//cpu_interrupt_to_thread是一个全局变量，里面存的是线程栈指针SP的指针
	LDR     r1, [r1]         @//加载cpu_interrupt_to_thread的值到r1，即sp指针的指针
	LDR     r1, [r1]          @加载cpu_interrupt_to_thread的值到r1，即sp
	@ LDMFD   r1!, {r4 - r11}   @将线程栈指针r1(操作之前先递减)指向的内容加载到CPU寄存器r4~r11
	ldmia   r1!, {r4}   @将线程栈指针r1(操作之前先递减)指向的内容加载到CPU寄存器r4~r11
	msr		spsr,r4
	movs     sp, r1       				@ //将线程栈指针更新到PSP
	@ ldmfd sp!, {r0-r12, lr, pc}^ 

SVC_exit:
	mrs r0, spsr
    and r1,r0,#0x3f
    msr spsr_c, r1
	ldmia	sp!,{r0-r12,lr,pc}^
	@ ldmia	sp!,{r4}  @pc
	@ ldmia	sp!,{r4}  @psr
	@ subs	pc, lr,#4
    @ ORR     lr, lr, #0x04                             //确保异常返回使用的堆栈指针是PSP，即LR寄存器的位2要为1
    @ BX      lr                                        //异常返回，这个时候任务堆栈中的剩下内容将会自动加载到xPSR，PC（任务入口地址），R14，R12，R3，R2，R1，R0（任务的形参）
	@ movs	pc, lr

	@ ldmia	sp!,{r0-r3,r12,lr}		/* state restore from compiled code */

	@ movs	pc, lr		/*return to the next instruction after the SWI instruction */


DataAbortHandler:				/* Data Abort handler */
#ifdef CONFIG_ARM_ERRATA_775420
	dsb
#endif
	stmdb	sp!,{r0-r3,r12,lr}		/* state save from compiled code */
	ldr     r0, =DataAbortAddr
	sub     r1, lr, #8
	str     r1, [r0]            		/* Stores instruction causing data abort */

	bl	DataAbortInterrupt		/*DataAbortInterrupt :call C function here */

	ldmia	sp!,{r0-r3,r12,lr}		/* state restore from compiled code */

	subs	pc, lr, #8			/* points to the instruction that caused the Data Abort exception */

PrefetchAbortHandler:				/* Prefetch Abort handler */
#ifdef CONFIG_ARM_ERRATA_775420
	dsb
#endif
	stmdb	sp!,{r0-r3,r12,lr}		/* state save from compiled code */
	ldr     r0, =PrefetchAbortAddr
	sub     r1, lr, #4
	str     r1, [r0]            		/* Stores instruction causing prefetch abort */

	bl	PrefetchAbortInterrupt		/* PrefetchAbortInterrupt: call C function here */

	ldmia	sp!,{r0-r3,r12,lr}		/* state restore from compiled code */

	subs	pc, lr, #4			/* points to the instruction that caused the Prefetch Abort exception */

.end
