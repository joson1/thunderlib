/*
 * @Author: your name
 * @Date: 2020-08-03 19:50:59
 * @LastEditTime: 2020-08-07 22:07:47
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\include\thunder\timer.h
 */
#pragma once

#include <stdint.h>
#include <xlist.h>

typedef struct __tmr_dev timer_dev_t;
struct __tmr_dev
{
    uint8_t id;
    uint32_t period_ms;
    void (*handler)(timer_dev_t* ptmr);
    void* prv_data;

    struct timer_ops{
        void (*set_period)(timer_dev_t* ptmr,uint32_t ms);
        void (*start)(timer_dev_t* ptmr);
        void (*stop)(timer_dev_t* ptmr);
    } ops;

    struct timer_irq{
        uint32_t IRQn;
        uint32_t is_shared;
        void (*clear_irq)(timer_dev_t* ptmr);
        ListItem_t devItem;
    } irq;

	ListItem_t devItem;

};




void timer_setup(uint32_t id,
                    uint32_t ms,uint32_t Priority,
                    void (*event_handler)());


int timer_dev_attach(timer_dev_t* dev);
timer_dev_t* timer_open(uint8_t id);
int timer_irq_request(timer_dev_t* tmr,void* handler);

int timer_set_period(timer_dev_t* tmr,int ms);
int timer_start(timer_dev_t* tmr);
int timer_stop(timer_dev_t* tmr);