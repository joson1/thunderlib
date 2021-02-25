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

#define NVIC_FTIR   				1  		//�½��ش���
#define NVIC_RTIR   				2  		//�����ش���
#define NVIC_ALL                    3       //������봥��



typedef struct __ExtiInitDef
{
    GPIO_TypeDef*  GPIOx;
    u32            GPIO_PIN;
    u8             GPIO_PUPD;     //����GPIO������������
    u8             NVIC_TRIM;     //NVIC_TRIM:����ģʽ,1,������;2,�½���;3�������ƽ����
    u8              Priority;     //���ȼ� ��Χ 0~15
    void*           event_handler;  //����������Ļص�����

    
} ExtiInitDef;

extern void Exti_Init(ExtiInitDef* pStr);
extern void EXTI_set_handler(uint32_t GPIO_PIN,void* event_handler);