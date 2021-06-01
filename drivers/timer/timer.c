/*
 * @Author: Alanwake@ThunderIndustry
 * @Date: 2020-08-03 19:50:11
 * @LastEditTime: 2020-08-07 22:52:03
 * @LastEditors: Please set LastEditors
 * @Description:  
 * @FilePath: \ThunderLib\drivers\timer\timer.c
 */
#include <thunder/timer.h>
#include <stddef.h>
#include <thunder/device.h>
#include <thunder/irq.h>


extern void (*_timer_setup)(uint32_t ,uint32_t ,uint32_t ,void (*)());
void (*_timer_setup)(uint32_t ,uint32_t ,uint32_t ,void (*)())=NULL;


xList_t tmr_irq_list;

static void tmr_irq_handler(timer_dev_t* dev)
{
    if (dev->irq.is_shared)
    {
        //do lowlevel 
    }else{
        dev->handler(dev); 
        dev->irq.clear_irq(dev);
    }

}


int timer_dev_attach(timer_dev_t* dev)
{
    dev_register(dev,DEV_MAJOR_TMR,dev->id);

    return 0;
}


timer_dev_t* timer_open(uint8_t id)
{
    return (timer_dev_t*)dev_open(DEV_MAJOR_TMR,id);
}


int timer_irq_request(timer_dev_t* tmr,void* handler)
{
    IRQ_vector_table[tmr->irq.IRQn].Handler = tmr_irq_handler;
    IRQ_vector_table[tmr->irq.IRQn].data    =tmr;
    xlistSET_LIST_ITEM_OWNER(&(tmr->irq.devItem),tmr); 
    irq_dev_reg(&tmr_irq_list,&(tmr->irq.devItem));
    tmr->handler = handler;
    // __tmr_irq_lowlevel_enable(tmr); 
    return tmr->irq.IRQn;
}


int timer_set_period(timer_dev_t* tmr,int ms)
{
    if ((tmr->ops.set_period))
    {
        tmr->ops.set_period(tmr,ms);
    }else
    {
        return -1;
    }
    return 0;
}

int timer_start(timer_dev_t* tmr)
{
    if ((tmr->ops.start))
    {
        tmr->ops.start(tmr);
    }else
    {
        return -1;
    }
    return 0;
}

int timer_stop(timer_dev_t* tmr)
{
    if ((tmr->ops.stop))
    {
        tmr->ops.stop(tmr);
    }else
    {
        return -1;
    }
    return 0;
}


void timer_setup(uint32_t id,uint32_t ms,
                    uint32_t Priority,void (*event_handler)())
{
    if(_timer_setup)
    {
        _timer_setup(id,ms,Priority,event_handler);
    }
}


