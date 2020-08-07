/*
 * @Author: your name
 * @Date: 2020-08-06 23:02:10
 * @LastEditTime: 2020-08-06 23:20:50
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\arch\arm\st\stm32f429\common\encoder.c
 */
#include "stm32f429/encoder.h"

void quad_encoder_init(TIM_TypeDef *TIMx, u8 x_freq)
{
	RCC->APB1ENR |= 1 << (((u32)TIMx - (u32)TIM2) / 0X0400);    //TIMx时钟使能2 ~ 5
	
	TIMx->PSC   = 0;          
	TIMx->ARR   = 65535;		
	TIMx->CR1   &= 0XFF0F;      //TIMx向上计数 TIMx_ARR寄存器没有缓冲
	
	TIMx->CR1   &= 0XFCFF;		//TIMx时钟不分频
	
	//TIMx-CC1通道被配置为输入， IC1映射在TI1上；
	//TIMx-CC2通道被配置为输入， IC2映射在TI2上；
	//无预分频器，捕获输入口上检测到的每一个边沿都触发一次捕获；
	//无滤波器，以CK_INT采样
	TIMx->CCMR1 &= 0X0000;
	TIMx->CCMR1 |= 0X0101;	
	
	TIMx->CCER  |= 0X0011;   //使能TIMx-CC1&TIMx-CC2通道.  IC1&IC2不反相
	
	TIMx->SMCR  &= 0XFFF8;
	TIMx->SMCR  &= ~0x07;
	if(x_freq==Encoder_Quadruple_freq)
		TIMx->SMCR  |= 3;       //编码器模式 3––计数器在 TI1FP1 和 TI2FP2 的边沿计数，计数的方向取决于另外一个信号的电平。
	else if(x_freq==Encoder_Double_freq)
		TIMx->SMCR  |= 2;       //编码器模式 2––计数器根据 TI2FP2 电平在 TI1FP1 边沿递增/递减计数。
	
	TIMx->CNT = 30000;
	TIMx->CR1 |= 0X01;
}
u16 quad_encoder_GetCount(TIM_TypeDef *TIMx)
{
	return TIMx->CNT;
}
void quad_encoder_SetCount(TIM_TypeDef *TIMx,u16 count)
{
    TIMx->CNT = count;
}


