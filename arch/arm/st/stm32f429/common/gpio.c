#include "stm32f429/gpio.h"


void GPIO_AF_Set(GPIO_TypeDef* GPIOx,u32 GPIO_PIN,u8 GPIO_AF)
{ 
	u8 i = 0;
	for ( i = 0; i < 16; i++)
	{
		if((GPIO_PIN>>i)&0x01)
		{
			GPIOx->AFR[i>>3]&=~(0X0F<<((i&0X07)*4));
			GPIOx->AFR[i>>3]|=(u32)GPIO_AF<<((i&0X07)*4);
		}
	}
}   

void GPIO_Init(GPIO_TypeDef* GPIOx,u32 GPIO_PIN,u32 GPIO_MODE,u32 GPIO_OTYPE,u32 GPIO_SPEED,u32 GPIO_PUPD)
{  

	u32 pinpos=0,pos=0,curpin=0;
	RCC->AHB1ENR |= 1<<(((uint32_t)GPIOx-(uint32_t)GPIOA)/1024);//使能GPIOx的时钟
	
	for(pinpos=0;pinpos<16;pinpos++)
	{
		pos=1<<pinpos;	//一个个位检查 
		curpin=GPIO_PIN&pos;//检查引脚是否要设置
		if(curpin==pos)	//需要设置
		{
			GPIOx->MODER&=~(3<<(pinpos*2));	//先清除原来的设置
			GPIOx->MODER|=GPIO_MODE<<(pinpos*2);	//设置新的模式 
			if((GPIO_MODE==0X01)||(GPIO_MODE==0X02))	//如果是输出模式/复用功能模式
			{  
				GPIOx->OSPEEDR&=~(3<<(pinpos*2));	//清除原来的设置
				GPIOx->OSPEEDR|=(GPIO_SPEED<<(pinpos*2));//设置新的速度值  
				GPIOx->OTYPER&=~(1<<pinpos) ;		//清除原来的设置
				GPIOx->OTYPER|=GPIO_OTYPE<<pinpos;		//设置新的输出模式
			}  
			GPIOx->PUPDR&=~(3<<(pinpos*2));	//先清除原来的设置
			GPIOx->PUPDR|=GPIO_PUPD<<(pinpos*2);	//设置新的上下拉
		}
	}
} 


//#define PA(n)    (0X00+n)
void GPIO_PIN_Init(u8 PIN,u32 GPIO_MODE,u32 GPIO_OTYPE,u32 GPIO_SPEED,u32 GPIO_PUPD)
{
	//PA(0)  -->  0x00
	u8 GPIO_X   = PIN>>4;   //0 ~ 8   -->   A ~ I
	u8 GPIO_PIN = PIN&0x0f; //0 ~ 15

	GPIO_TypeDef* GPIOx = (GPIO_TypeDef*)(0x40020000+GPIO_X*1024);
	
	RCC->AHB1ENR |= 1<<GPIO_X;		//使能GPIOx的时钟

	GPIOx->MODER&=~(3<<(GPIO_PIN*2));	//先清除原来的设置
	GPIOx->MODER|=GPIO_MODE<<(GPIO_PIN*2);	//设置新的模式 
	if((GPIO_MODE==0X01)||(GPIO_MODE==0X02))	//如果是输出模式/复用功能模式
	{  
		GPIOx->OSPEEDR&=~(3<<(GPIO_PIN*2));	//清除原来的设置
		GPIOx->OSPEEDR|=(GPIO_SPEED<<(GPIO_PIN*2));//设置新的速度值  
		GPIOx->OTYPER&=~(1<<GPIO_PIN) ;		//清除原来的设置
		GPIOx->OTYPER|=GPIO_OTYPE<<GPIO_PIN;		//设置新的输出模式
	}  
	GPIOx->PUPDR&=~(3<<(GPIO_PIN*2));	//先清除原来的设置
	GPIOx->PUPDR|=GPIO_PUPD<<(GPIO_PIN*2);	//设置新的上下拉
}

void GPIO_PIN_AF_Set(u8 PIN, u8 GPIO_AF)
{
	u8 GPIO_X   = PIN>>4;   //0 ~ 8   -->   A ~ I
	u8 GPIO_PIN = PIN&0x0f; //0 ~ 15

	GPIO_TypeDef* GPIOx = (GPIO_TypeDef*)(0x40020000+GPIO_X*1024);

	GPIOx->AFR[GPIO_PIN>>3]&=~(0X0F<<((GPIO_PIN&0X07)*4));
	GPIOx->AFR[GPIO_PIN>>3]|=(u32)GPIO_AF<<((GPIO_PIN&0X07)*4);		
}

void GPIO_Set(GPIO_TypeDef *GPIOx, u16 GPIO_PIN)
{
	GPIOx->ODR |= GPIO_PIN;
}

void GPIO_Rset(GPIO_TypeDef *GPIOx, u16 GPIO_PIN)
{
	GPIOx->ODR &= ~GPIO_PIN;
}
