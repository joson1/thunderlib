/*
 * @Author: your name
 * @Date: 2020-08-06 23:02:11
 * @LastEditTime: 2020-08-07 00:09:00
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\arch\arm\st\include\stm32f429\timer.h
 */
#ifndef __TIMER_H__
#define __TIMER_H__
#include "stm32f429/sys.h"

typedef struct 
{
    TIM_TypeDef* TIMx;
    u16 ms;       //you can specify ms to set a timer,the psc and arr will be set automatically
    u32 psc;      //you can also set psc and arr value manually to set a timer,BUT leave ms to 0
    u32 arr;        
    u8 Priority; 

    void (*event_handler)();
} Timer_InitDef;

extern void timerInit(Timer_InitDef *Timer);

#endif