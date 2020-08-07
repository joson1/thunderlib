/*
 * @Author: your name
 * @Date: 2020-08-06 23:02:11
 * @LastEditTime: 2020-08-06 23:20:08
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\arch\arm\st\stm32f429\common\adc.c
 */
#include "stm32f429/adc.h"

void ADC_Init(ADC_InitDef *ADCn)
{

    RCC->APB2ENR |= 1 <<((((vu32)(ADCn->ADCx) - (vu32)ADC1) >> 8) + 8);
    // RCC->APB2RSTR |= 1 << 8;
    // RCC->APB2RSTR &= ~(1 << 8);
    ADC->CCR = (ADCn->ADC_Prescaler) << 16;
    ADCn->ADCx->CR1 = 0;
    ADCn->ADCx->CR2 = 0;
    ADCn->ADCx->CR1 |= 0 << 24;
    ADCn->ADCx->CR1 |= 0 << 8;
    ADCn->ADCx->CR2 &= ~(1 << 1);
    ADCn->ADCx->CR2 &= ~(1 << 11);
    ADCn->ADCx->CR2 |= 0 << 28;
    ADCn->ADCx->SMPR2 &= ~(7 << (3 * ADCn->Channel));
    ADCn->ADCx->SMPR2 |= (ADCn->Sample_Time) << (3 * ADCn->Channel);
    ADCn->ADCx->CR2 |= 1 << 0;

}

u16 ADC_Get_Raw(ADC_InitDef *ADCn)
{
    ADCn->ADCx->SQR3&=0XFFFFFFE0;//规则序列1 通道ch
    ADCn->ADCx->SQR3 |= (ADCn->Channel);

    ADCn->ADCx->CR2 |= 1<<30;

    while (!(ADCn->ADCx->SR&1<<1));

    return ADCn->ADCx->DR;
}

