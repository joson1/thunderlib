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
	RCC->APB1ENR |= 1 << (((u32)TIMx - (u32)TIM2) / 0X0400);    //TIMxʱ��ʹ��2 ~ 5
	
	TIMx->PSC   = 0;          
	TIMx->ARR   = 65535;		
	TIMx->CR1   &= 0XFF0F;      //TIMx���ϼ��� TIMx_ARR�Ĵ���û�л���
	
	TIMx->CR1   &= 0XFCFF;		//TIMxʱ�Ӳ���Ƶ
	
	//TIMx-CC1ͨ��������Ϊ���룬 IC1ӳ����TI1�ϣ�
	//TIMx-CC2ͨ��������Ϊ���룬 IC2ӳ����TI2�ϣ�
	//��Ԥ��Ƶ��������������ϼ�⵽��ÿһ�����ض�����һ�β���
	//���˲�������CK_INT����
	TIMx->CCMR1 &= 0X0000;
	TIMx->CCMR1 |= 0X0101;	
	
	TIMx->CCER  |= 0X0011;   //ʹ��TIMx-CC1&TIMx-CC2ͨ��.  IC1&IC2������
	
	TIMx->SMCR  &= 0XFFF8;
	TIMx->SMCR  &= ~0x07;
	if(x_freq==Encoder_Quadruple_freq)
		TIMx->SMCR  |= 3;       //������ģʽ 3�C�C�������� TI1FP1 �� TI2FP2 �ı��ؼ����������ķ���ȡ��������һ���źŵĵ�ƽ��
	else if(x_freq==Encoder_Double_freq)
		TIMx->SMCR  |= 2;       //������ģʽ 2�C�C���������� TI2FP2 ��ƽ�� TI1FP1 ���ص���/�ݼ�������
	
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


