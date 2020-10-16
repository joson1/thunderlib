/*
 * @Author: your name
 * @Date: 2020-08-10 16:28:42
 * @LastEditTime: 2020-08-10 16:31:22
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\drivers\timer\devices\timer-stm32f429.c
 */
/*-----------------------TIMER-------------------------*/

#include "stm32f429xx.h"
#include "stm32f429/timer.h"


extern void (*_timer_setup)(uint32_t ,uint32_t ,uint32_t ,void (*)());


void timer_init(uint32_t id,uint32_t ms,
                    uint32_t Priority,void (*event_handler)())
{

    Timer_InitDef timerx = {
        .event_handler = event_handler,
        .ms = ms,
        .Priority = Priority
    };


    switch (id)
    {
    case 1:
        timerx.TIMx = TIM1;
        break;
    case 2:
        timerx.TIMx = TIM2;
        break;
    
    case 3:
        timerx.TIMx = TIM3;
        break;
    case 4:
        timerx.TIMx = TIM4;
        break;
    
    case 5:
        timerx.TIMx = TIM5;
        break;
    
    case 6:
        timerx.TIMx = TIM6;
        break;

    case 7:
        timerx.TIMx = TIM7;
        break;
    case 8:
        timerx.TIMx = TIM8;
        break;
    case 9:
        timerx.TIMx = TIM9;
        break;
    case 10:
        timerx.TIMx = TIM10;
        break;
    case 11:
        timerx.TIMx = TIM11;
        break;
    default:
        break;
    }
    timerInit(&timerx);

}

extern void stm32f429_timer_init();
void stm32f429_timer_init()
{

	_timer_setup = &timer_init;
}