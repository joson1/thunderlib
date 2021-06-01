/*
 * @Author: your name
 * @Date: 2020-08-20 19:42:16
 * @LastEditTime: 2020-08-24 12:54:09
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\drivers\interrupt\interrupt.c
 */

#include <thunder/irq.h>
#include <xlist.h>

InterruptTableEntry IRQ_vector_table[MAX_IRQn] = {0};




// int __attribute__((weak)) irq_register(uint32_t Irq_id,InterruptHandler handler,uint32_t Trigger_edge)
// {
//     IRQ_vector_table[Irq_id].Handler = handler;
    
// }

void __attribute__((weak))  __irq_enable(int irq_id)//implemented in devices
{
    return;
}

int irq_register(uint32_t Irq_id,InterruptHandler handler,void* Message,void (*CallBack))
{

    if (handler){
        IRQ_vector_table[Irq_id].Handler = handler;
        IRQ_vector_table[Irq_id].data	 = Message;
        IRQ_vector_table[Irq_id].CallBack= CallBack;
    }
    


    __irq_enable(Irq_id);

    return Irq_id;
}

int irq_enable(uint32_t Irq_id)
{
    __irq_enable(Irq_id);

    return Irq_id;
}


int irq_dev_reg(xList_t* pList, ListItem_t* pItem)
{

    if(pList->xListEnd.pxNext==0){
        xList_init(pList);
    }

    xListInsert(pList,pItem);

    return 0;
}



