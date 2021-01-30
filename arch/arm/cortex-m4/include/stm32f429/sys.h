/*
 * @Author: your name
 * @Date: 2020-08-06 23:02:26
 * @LastEditTime: 2020-08-06 23:09:06
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\arch\arm\st\include\stm32f429\sys.h
 */
#ifndef __SYS_H
#define __SYS_H	 
#include "stm32f429xx.h" 
#include <stdint.h>


typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;
 
typedef volatile uint32_t  vu32;
typedef volatile uint16_t vu16;
typedef volatile uint8_t  vu8; 

typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;


////////////////////////////////////////////////////////////////////////////////// 
//Ex_NVIC_Config专用定义
#define NVIC_EX_GPIO_A 				0
#define NVIC_EX_GPIO_B 				1
#define NVIC_EX_GPIO_C				2
#define NVIC_EX_GPIO_D 				3
#define NVIC_EX_GPIO_E 				4
#define NVIC_EX_GPIO_F 				5
#define NVIC_EX_GPIO_G 				6 
#define NVIC_EX_GPIO_H 				7 
#define NVIC_EX_GPIO_I 				8 

#define PA(n)    (0X00+n)
#define PB(n)    (0X10+n)
#define PC(n)    (0X20+n)
#define PD(n)    (0X30+n)
#define PE(n)    (0X40+n)
#define PF(n)    (0X50+n)
#define PG(n)    (0X60+n)
#define PH(n)    (0X70+n)
#define PI(n)    (0X80+n) 


////////////////////////////////////////////////////////////////////////////////// 
u8 Sys_Clock_Set(u32 plln,u32 pllm,u32 pllp,u32 pllq);		//系统时钟设置
void Stm32_Clock_Init(u32 plln,u32 pllm,u32 pllp,u32 pllq); //时钟初始化  
void Sys_Soft_Reset(void);      							//系统软复位
void Sys_Standby(void);         							//待机模式 	
void MY_NVIC_SetVectorTable(u32 NVIC_VectTab, u32 Offset);	//设置偏移地址
void MY_NVIC_PriorityGroupConfig(u8 NVIC_Group);			//设置NVIC分组
void MY_NVIC_Init(u8 NVIC_PreemptionPriority,u8 NVIC_Channel);	 //设置中断
void Ex_NVIC_Config(GPIO_TypeDef* GPIOx,u16 GPIO_PIN,u8 NVIC_TRIM); 			//外部中断配置函数


#endif











