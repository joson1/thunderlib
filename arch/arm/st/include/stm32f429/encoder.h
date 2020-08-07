#pragma once
#include "stm32f429/sys.h"
//only Time2 ~ Time5,Time1 & Time8 for STM32F103xxx
//only Time2 ~ Time5,Time1 & Time8 for STM32F4xxx
/*
正交编码器驱动库：
Orth_Encoder_Init(TIM_TypeDef *TIMx)			//初始化编码器模式TIMx
												//编码器的A,B 相应该接在TIMx的CH1和CH2
												//需要用户自行初始化TIMx的CH1和CH2 IO口

Orth_Get_EnCount(TIM_TypeDef *TIMx)    			//获取编码器的计数值
Orth_Set_EnCount(TIM_TypeDef *TIMx,u16 count) 	//设置编码器的计数值
说明：
	计数器是一个u16的寄存器，计数范围为0 ~ 65535，
	初始化之后，计数值默认为30000，
	当正交编码器接入TIMx的CH1和CH2之后并初始化定时器，编码器正转产生的脉冲会使得计数器以30000为初值(也可自定义初值)向上计数，一直计到65535之后会溢出.
	反转则会使计数方向相反.
eg:
500线欧姆龙编码器，每转一圈输出500个脉冲
计数器计数2000次，正转为增，反转为减（相对
初始化gpio:
	GPIO_Init(GPIOH,GPIO_PIN_10|GPIO_PIN_11,GPIO_MODE_AF,0,GPIO_SPEED_100M,GPIO_PUPD_PU);
	GPIO_AF_Set(GPIOH,GPIO_PIN_10|GPIO_PIN_11,2);							//TIM5-CH1   -> PH10   TIM5-CH2   -> PH11	
初始化编码器：													
	Orth_Encoder_Init(TIM5);
	Orth_Set_EnCount(TIM5,10000);   //设置计数初值10000
调用：
	Orth_Get_EnCount(TIM5);
便可获得当前计数值（当前位置）

定时1ms调用：
	En_counter = Orth_Get_EnCount(TIM5);
	En_Speed = 30000 - En_counter;
	Orth_Set_EnCount(TIM5,30000);
便可获得转速 En_Speed

*/

#define Encoder_Double_freq      0   //两倍频计数
#define Encoder_Quadruple_freq   1   //四倍频计数

void quad_encoder_init(TIM_TypeDef *TIMx, u8 x_freq);
u16 quad_encoder_GetCount(TIM_TypeDef *TIMx);
void quad_encoder_SetCount(TIM_TypeDef *TIMx,u16 count);

