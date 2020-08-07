#pragma once
#include "stm32f429/sys.h"
//only Time2 ~ Time5,Time1 & Time8 for STM32F103xxx
//only Time2 ~ Time5,Time1 & Time8 for STM32F4xxx
/*
���������������⣺
Orth_Encoder_Init(TIM_TypeDef *TIMx)			//��ʼ��������ģʽTIMx
												//��������A,B ��Ӧ�ý���TIMx��CH1��CH2
												//��Ҫ�û����г�ʼ��TIMx��CH1��CH2 IO��

Orth_Get_EnCount(TIM_TypeDef *TIMx)    			//��ȡ�������ļ���ֵ
Orth_Set_EnCount(TIM_TypeDef *TIMx,u16 count) 	//���ñ������ļ���ֵ
˵����
	��������һ��u16�ļĴ�����������ΧΪ0 ~ 65535��
	��ʼ��֮�󣬼���ֵĬ��Ϊ30000��
	����������������TIMx��CH1��CH2֮�󲢳�ʼ����ʱ������������ת�����������ʹ�ü�������30000Ϊ��ֵ(Ҳ���Զ����ֵ)���ϼ�����һֱ�Ƶ�65535֮������.
	��ת���ʹ���������෴.
eg:
500��ŷķ����������ÿתһȦ���500������
����������2000�Σ���תΪ������תΪ�������
��ʼ��gpio:
	GPIO_Init(GPIOH,GPIO_PIN_10|GPIO_PIN_11,GPIO_MODE_AF,0,GPIO_SPEED_100M,GPIO_PUPD_PU);
	GPIO_AF_Set(GPIOH,GPIO_PIN_10|GPIO_PIN_11,2);							//TIM5-CH1   -> PH10   TIM5-CH2   -> PH11	
��ʼ����������													
	Orth_Encoder_Init(TIM5);
	Orth_Set_EnCount(TIM5,10000);   //���ü�����ֵ10000
���ã�
	Orth_Get_EnCount(TIM5);
��ɻ�õ�ǰ����ֵ����ǰλ�ã�

��ʱ1ms���ã�
	En_counter = Orth_Get_EnCount(TIM5);
	En_Speed = 30000 - En_counter;
	Orth_Set_EnCount(TIM5,30000);
��ɻ��ת�� En_Speed

*/

#define Encoder_Double_freq      0   //����Ƶ����
#define Encoder_Quadruple_freq   1   //�ı�Ƶ����

void quad_encoder_init(TIM_TypeDef *TIMx, u8 x_freq);
u16 quad_encoder_GetCount(TIM_TypeDef *TIMx);
void quad_encoder_SetCount(TIM_TypeDef *TIMx,u16 count);

