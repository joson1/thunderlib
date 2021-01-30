/*
 * @Author: your name
 * @Date: 2020-08-20 19:42:16
 * @LastEditTime: 2020-08-24 12:54:09
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\drivers\interrupt\interrupt.c
 */

#include <thunder/irq.h>


InterruptTableEntry IRQ_vector_table[MAX_IRQn] = {0};



// int __attribute__((weak)) irq_register(uint32_t Irq_id,InterruptHandler handler,uint32_t Trigger_edge)
// {
//     IRQ_vector_table[Irq_id].Handler = handler;
    
// }
