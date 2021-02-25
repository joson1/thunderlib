/*
 * @Author: your name
 * @Date: 2020-08-06 23:02:11
 * @LastEditTime: 2020-08-06 23:46:29
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\arch\arm\st\include\stm32f429\exti.h
 */
#pragma once
#include "stm32f429/sys.h"

#define NVIC_FTIR   				1  		//下降沿触发
#define NVIC_RTIR   				2  		//上升沿触发
#define NVIC_ALL                    3       //任意编译触发



typedef struct __ExtiInitDef
{
    GPIO_TypeDef*  GPIOx;
    u32            GPIO_PIN;
    u8             GPIO_PUPD;     //配置GPIO的上下拉电阻
    u8             NVIC_TRIM;     //NVIC_TRIM:触发模式,1,上升沿;2,下降沿;3，任意电平触发
    u8              Priority;     //优先级 范围 0~15
    void*           event_handler;  //按键触发后的回调函数

    
} ExtiInitDef;

extern void Exti_Init(ExtiInitDef* pStr);
extern void EXTI_set_handler(uint32_t GPIO_PIN,void* event_handler);