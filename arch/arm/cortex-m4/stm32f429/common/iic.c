#include "stm32f429/iic.h"
#include "stm32f429/gpio.h"
#include "stm32f429/delay.h" 

static __INLINE void SDA_IN(IIC_TypeDef *IIC)
{
	u8 pinpos;
	for (pinpos = 0; pinpos < 15; pinpos++)
	{
		if((IIC->SDA_PIN>>pinpos)&0x01) break;
	}
	
	IIC->SDA_GPIOx->MODER &= ~(3 << (pinpos * 2));			// ??
	// GPIOx->MODER |= GPIO_MODE_IN << (pinpos * 2);	
	// GPIO_Init(IIC->SDA_GPIOx, IIC->SDA_PIN, GPIO_MODE_IN, GPIO_OTYPE_OD, GPIO_SPEED_100M, GPIO_PUPD_PU);
}

static __INLINE void SDA_OUT(IIC_TypeDef *IIC)
{
	u8 pinpos;
	for (pinpos = 0; pinpos < 15; pinpos++)
	{
		if((IIC->SDA_PIN>>pinpos)&0x01) break;
	}
	
	// GPIOx->MODER &= ~(3 << (pinpos * 2));			// 
	IIC->SDA_GPIOx->MODER |= GPIO_MODE_OUT << (pinpos * 2);		//??
	//GPIO_Init(IIC->SDA_GPIOx, IIC->SDA_PIN, GPIO_MODE_OUT, GPIO_OTYPE_PP, GPIO_SPEED_100M, GPIO_PUPD_PU);
}

static __INLINE void SDA_set(IIC_TypeDef *IIC, u8 state)
{
	if (state)
	{
		IIC->SDA_GPIOx->ODR |= IIC->SDA_PIN;
	}
	else
	{
		IIC->SDA_GPIOx->ODR &= ~(IIC->SDA_PIN);
	}
}

static __INLINE void SCL_set(IIC_TypeDef *IIC, u8 state)
{
	if (state)
	{
		IIC->SCL_GPIOx->ODR |= IIC->SCL_PIN;
	}
	else
	{
		IIC->SCL_GPIOx->ODR &= ~(IIC->SCL_PIN);
	}
}

static __INLINE u8 SDA_read(IIC_TypeDef *IIC)
{

	if (IIC->SDA_GPIOx->IDR & IIC->SDA_PIN)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


void IIC_Init(IIC_TypeDef *IIC)
{
	
	GPIO_Init(IIC->SCL_GPIOx,IIC->SCL_PIN,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);
	GPIO_Init(IIC->SDA_GPIOx,IIC->SDA_PIN,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);
}


void __INLINE IIC_start(IIC_TypeDef *IIC)
{
	
	SCL_set(IIC, 1);
	SDA_set(IIC, 1);
	SDA_OUT(IIC);
	
	delay_us(IIC->Speed+2);
	SDA_set(IIC, 0);
	delay_us(IIC->Speed+2);
	SCL_set(IIC, 0);
}

void __INLINE IIC_stop(IIC_TypeDef *IIC)
{
	SDA_OUT(IIC);
	SCL_set(IIC, 0);
	SDA_set(IIC, 0);
	delay_us(IIC->Speed+2);
	SCL_set(IIC, 1);
	SDA_set(IIC, 1);
}

void __INLINE IIC_Ack(IIC_TypeDef *IIC)
{
	SCL_set(IIC, 0);

	SDA_OUT(IIC);
	SDA_set(IIC, 0);
	delay_us(IIC->Speed);
	SCL_set(IIC, 1);
	delay_us(IIC->Speed);
	SCL_set(IIC, 0);
}

void __INLINE IIC_NAck(IIC_TypeDef *IIC)
{
	
	SCL_set(IIC, 0);
	SDA_OUT(IIC);
	SDA_set(IIC, 1);
	delay_us(IIC->Speed+2);
	SCL_set(IIC, 1);
	delay_us(IIC->Speed+2);
	SCL_set(IIC, 0);
}

void IIC_write(IIC_TypeDef *IIC, uint8_t txd)
{
    u8 t;   
    SCL_set(IIC, 0);
	SDA_OUT(IIC);   
	delay_us(IIC->Speed);
    for(t=0;t<8;t++)
    {       
		SDA_set(IIC, (txd&0x80)>>7);    
		delay_us(IIC->Speed);   
		txd<<=1; 	
		SCL_set(IIC, 1);
		delay_us(IIC->Speed);
		SCL_set(IIC, 0);
		
		
    }	 
	delay_us(1);
}

uint8_t IIC_read(IIC_TypeDef *IIC, uint8_t ack)
{
	unsigned char i,receive=0;
	delay_us(30);

	SDA_IN(IIC);
    for(i=0;i<8;i++ )
	{
        SCL_set(IIC, 0);
        delay_us(IIC->Speed);
		SCL_set(IIC, 1);
        receive<<=1;
        if(SDA_read(IIC))receive++;   
		delay_us(IIC->Speed);
    }					 
    if (!ack)
        IIC_NAck(IIC);//??nACK
    else
        IIC_Ack(IIC); //??ACK   
    return receive;

}

uint8_t IIC_wait_ack(IIC_TypeDef *IIC)
{
	uint8_t time = 0;

	SDA_IN(IIC);
	SDA_set(IIC, 1); delay_us(IIC->Speed+2);
	SCL_set(IIC, 1); delay_us(IIC->Speed+2);
	
    
	while (SDA_read(IIC))
	{
		time++;
		if (time > 0xfd)
		{
			//while(1);
			IIC_stop(IIC);
			return 1;
		}
	}
	SCL_set(IIC, 0);
	return 0;
}
