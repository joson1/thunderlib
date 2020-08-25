/*
 * @Author: your name
 * @Date: 2020-08-20 21:46:25
 * @LastEditTime: 2020-08-24 13:34:33
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\drivers\interrupt\devices\interrupt-zynq.c
 */
#include <thunder/interrput.h>
#include "zynq/zynq.h"
#include <stdio.h>




int irq_register(uint32_t Irq_id,InterruptHandler handler,uint32_t Trigger_edge)
{
    uint32_t n,m;
    n = Irq_id/16;
    m = (Irq_id%16);
    IRQ_vector_table[Irq_id].Handler = handler;
    ICDICFR[n] &= ~(Trigger_edge<<(m*2));
    ICDICFR[n] |=  (Trigger_edge<<(m*2));


}



