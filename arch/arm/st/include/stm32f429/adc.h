#ifndef __ADC_H__
#define __ADC_H__
#include "stm32f429/sys.h"

#define ADC_CHANNEL_0 0
#define ADC_CHANNEL_1 1
#define ADC_CHANNEL_2 2
#define ADC_CHANNEL_3 3
#define ADC_CHANNEL_4 4
#define ADC_CHANNEL_5 5
#define ADC_CHANNEL_6 6
#define ADC_CHANNEL_7 7
#define ADC_CHANNEL_8 8
#define ADC_CHANNEL_9 9
#define ADC_CHANNEL_10 10
#define ADC_CHANNEL_11 11
#define ADC_CHANNEL_12 12
#define ADC_CHANNEL_13 13
#define ADC_CHANNEL_14 14
#define ADC_CHANNEL_15 15
#define ADC_CHANNEL_16 16
#define ADC_CHANNEL_17 17
#define ADC_CHANNEL_18 18

#define ADC_Prescaler_2 0
#define ADC_Prescaler_4 1
#define ADC_Prescaler_6 2
#define ADC_Prescaler_8 3

#define ADC_SAMPLE_TIME_3 0
#define ADC_SAMPLE_TIME_15 1
#define ADC_SAMPLE_TIME_28 2
#define ADC_SAMPLE_TIME_84 3
#define ADC_SAMPLE_TIME_112 4
#define ADC_SAMPLE_TIME_144 5
#define ADC_SAMPLE_TIME_480 6

typedef struct 
{
    ADC_TypeDef* ADCx;
    u8 ADC_Prescaler;
    u32 Channel;
    u8 Sample_Time;

} ADC_InitDef;

extern void ADC_Init(ADC_InitDef *ADCn);
extern u16 ADC_Get_Raw(ADC_InitDef *ADCn);
#endif

