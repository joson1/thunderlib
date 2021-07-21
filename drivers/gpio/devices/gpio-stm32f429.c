/*
 * @Author: your name
 * @Date: 2020-08-16 11:37:49
 * @LastEditTime: 2020-08-16 19:38:24
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * 
 * @FilePath: \ThunderLib\drivers\gpio\devices\gpio-stm32f429.c
 */
#include <thunder/gpio.h>
#include "stm32f429/gpio.h"
#include "pin-stm32.h"
#include "stm32f429/exti.h"

void gpio_pin_mode (uint8_t pin_id, uint32_t mode)
{
    GPIO_TypeDef* pin =  (GPIO_TypeDef*)(pin_map[pin_id].bank);
    uint8_t pinpos;

	for (pinpos = 0; pinpos < 15; pinpos++)
	{
		if((pin_map[pin_id].pin>>pinpos)&0x01) break;
	}
	
    if (mode==GPIO_MODE_OUTPUT)
    {
        pin->MODER |= (1 << (pinpos * 2));	
        
    }else
    {
        pin->MODER &= ~(3 << (pinpos * 2));	

    }
    
    // GPIO_Init(
    //         (GPIO_TypeDef*)(pin_map[pin_id].bank),
    //         pin_map[pin_id].pin,
    //         (mode&0x000f),
    //         (mode&0x00f0)>>4,
    //         (mode&0x0f00)>>8,
    //         (mode&0xf000)>>12
    // );


}
void gpio_pin_dir (uint8_t pin_id, uint32_t mode)
{
	u32 pinpos=0,pos=0,curpin=0;
	for(pinpos=0;pinpos<16;pinpos++)
	{
		pos=1<<pinpos;	//一个个位检查 
		curpin=(pin_map[pin_id].pin)&pos;//检查引脚是否要设置
		if(curpin==pos)	//需要设置
		{
			((GPIO_TypeDef*)(pin_map[pin_id].bank))->MODER&=~(3<<(pinpos*2));	//先清除原来的设置
			((GPIO_TypeDef*)(pin_map[pin_id].bank))->MODER|=(mode&0x000f)<<(pinpos*2);	//设置新的模式 
			if(((mode&0x000f)==0X01)||((mode&0x000f)==0X02))	//如果是输出模式/复用功能模式
			{  
				((GPIO_TypeDef*)(pin_map[pin_id].bank))->OSPEEDR&=~(3<<(pinpos*2));	//清除原来的设置
				((GPIO_TypeDef*)(pin_map[pin_id].bank))->OSPEEDR|=(((mode&0x0f00)>>8)<<(pinpos*2));//设置新的速度值  
				((GPIO_TypeDef*)(pin_map[pin_id].bank))->OTYPER&=~(1<<pinpos) ;		//清除原来的设置
				((GPIO_TypeDef*)(pin_map[pin_id].bank))->OTYPER|=((mode&0x00f0)>>4)<<pinpos;		//设置新的输出模式
			}  

		}
	}
}
void gpio_pin_pull (uint8_t pin_id, uint32_t pull)
{
	u32 pinpos=0,pos=0,curpin=0;

	for(pinpos=0;pinpos<16;pinpos++)
	{
		pos=1<<pinpos;	//一个个位检查 
		curpin=(pin_map[pin_id].pin)&pos;//检查引脚是否要设置
		if(curpin==pos)	//需要设置
		{
			((GPIO_TypeDef*)(pin_map[pin_id].bank))->PUPDR&=~(3<<(pinpos*2));	//先清除原来的设置
			((GPIO_TypeDef*)(pin_map[pin_id].bank))->PUPDR|=pull<<(pinpos*2);	//设置新的上下拉
		}
	}

}

void gpio_pin_set  (uint8_t pin_id)
{
    GPIO_Set( (GPIO_TypeDef*)(pin_map[pin_id].bank),
              pin_map[pin_id].pin);
}

void gpio_pin_reset(uint8_t pin_id)
{
    GPIO_Rset( (GPIO_TypeDef*)(pin_map[pin_id].bank),
               pin_map[pin_id].pin);
}

struct pinDesc  pin_map[] = PINS_STM32F429;

void gpio_pin_write(uint8_t pin_id,uint8_t value)
{
    if (value)
    {
        gpio_pin_set(pin_id);
    }else
    {
        gpio_pin_reset(pin_id);
    }
    
}
uint8_t gpio_pin_read(uint8_t pin_id)
{
    return GPIO_read( (GPIO_TypeDef*)(pin_map[pin_id].bank),
              pin_map[pin_id].pin);
}


uint32_t gpio_interrupt_request(uint8_t pin_id, uint8_t edge)
{
	GPIO_TypeDef* GPIOx = ((GPIO_TypeDef*)(pin_map[pin_id].bank));
	uint32_t GPIO_PIN = ((GPIO_TypeDef*)(pin_map[pin_id].pin));
    GPIO_Init( GPIOx,GPIO_PIN,GPIO_MODE_IN,0,0,GPIO_PUPD_PU);
	uint32_t tmp;
    switch (GPIO_PIN)
    {
        case GPIO_PIN_0:
                tmp = EXTI0_IRQn;
                break;
            case GPIO_PIN_1:
                tmp = EXTI1_IRQn;
                break;
            case GPIO_PIN_2:
                tmp = EXTI2_IRQn;
            case GPIO_PIN_3:
                tmp = EXTI3_IRQn;
                break;
            case GPIO_PIN_4:
                tmp = EXTI4_IRQn;
                break;
            case GPIO_PIN_5:
                tmp = EXTI9_5_IRQn;
            case GPIO_PIN_6:
                tmp = EXTI9_5_IRQn;
                break;
            case GPIO_PIN_7:
                tmp = EXTI9_5_IRQn;
                break;
            case GPIO_PIN_8:
                tmp = EXTI9_5_IRQn;
                break;
            case GPIO_PIN_9:
                tmp = EXTI9_5_IRQn;
                break;
            case GPIO_PIN_10:
                tmp = EXTI15_10_IRQn;
                break;
            case GPIO_PIN_11:
                tmp = EXTI15_10_IRQn;
            case GPIO_PIN_12:
                tmp = EXTI15_10_IRQn;
                break;
            case GPIO_PIN_13:
                tmp = EXTI15_10_IRQn;
                break;
            case GPIO_PIN_14:
                tmp = EXTI15_10_IRQn;
                break;
            case GPIO_PIN_15:
                tmp = EXTI15_10_IRQn;
                break;
            default:
                break;

    }	
    Ex_NVIC_Config(GPIOx,GPIO_PIN,edge);

	return tmp;
}

void gpio_intr_setup(uint8_t pin_id, uint8_t Priority,uint32_t irqn,void* handler)
{

	uint32_t GPIO_PIN = ((GPIO_TypeDef*)(pin_map[pin_id].pin));
	EXTI_set_handler(GPIO_PIN,handler);
    MY_NVIC_Init(Priority,irqn);

}





