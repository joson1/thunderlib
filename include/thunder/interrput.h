/*
 * @Author: your name
 * @Date: 2020-08-20 19:44:26
 * @LastEditTime: 2020-10-05 19:45:36
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\include\thunder\interrput.h
 */
#include <asm/interrupt_defs.h>
#include <stdint.h>

typedef void (*InterruptHandler)(void *data);
typedef struct
{
	InterruptHandler Handler;
	void (*CallBack)(void*);
	void* data;
} InterruptTableEntry;



extern InterruptTableEntry IRQ_vector_table[MAX_IRQn];

int irq_register(uint32_t Irq_id,InterruptHandler handler,uint32_t Trigger_edge,void* Message,void (*CallBack));
