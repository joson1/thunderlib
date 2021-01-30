#ifndef __PWM_H__
#define __PWM_H__
#include "stm32f429/sys.h"
#include "stm32f429/tim.h"

#define TIM_CCR(x,n) TIM##x->CCR##n      //TIMx->CCRn ,值越大占空比越大

typedef struct 
{
    TIM_TypeDef* TIMx;
    u8 channels;
    u16 frequency;    //50 ~ ++  HZ
    u32 psc;
    u32 arr;

} PWM_InitTypeDef;

extern void PWM_init(PWM_InitTypeDef *PWM);
extern u32 PWM_Get_Param_ARR(PWM_InitTypeDef *PWM);
#endif
