#include "stm32f429/exti.h"
#include "stm32f429/gpio.h"
#include <stddef.h>


void (*My_EXTI0_Irq)()      = NULL;
void (*My_EXTI1_Irq)()      = NULL;
void (*My_EXTI2_Irq)()      = NULL;
void (*My_EXTI3_Irq)()      = NULL;
void (*My_EXTI4_Irq)()      = NULL;
void (*My_EXTI5_Irq)()      = NULL;
void (*My_EXTI6_Irq)()      = NULL;
void (*My_EXTI7_Irq)()      = NULL;
void (*My_EXTI8_Irq)()      = NULL;
void (*My_EXTI9_Irq)()      = NULL;
void (*My_EXTI10_Irq)()     = NULL;
void (*My_EXTI11_Irq)()     = NULL;
void (*My_EXTI12_Irq)()     = NULL;
void (*My_EXTI13_Irq)()     = NULL;
void (*My_EXTI14_Irq)()     = NULL;
void (*My_EXTI15_Irq)()     = NULL;



void Exti_Init(ExtiInitDef* pStr)
{
    u8 tmp = 0; 
    
    GPIO_Init( pStr->GPIOx,pStr->GPIO_PIN,GPIO_MODE_IN,0,0,pStr->GPIO_PUPD);
    Ex_NVIC_Config(pStr->GPIOx,pStr->GPIO_PIN,pStr->NVIC_TRIM);

    switch (pStr->GPIO_PIN)
    {
        case GPIO_PIN_0:
                My_EXTI0_Irq = pStr->event_handler;
                tmp = EXTI0_IRQn;
                break;
            case GPIO_PIN_1:
                My_EXTI1_Irq = pStr->event_handler;
                tmp = EXTI1_IRQn;
                break;
            case GPIO_PIN_2:
                My_EXTI2_Irq = pStr->event_handler;
                tmp = EXTI2_IRQn;
            case GPIO_PIN_3:
                My_EXTI3_Irq = pStr->event_handler;
                tmp = EXTI3_IRQn;
                break;
            case GPIO_PIN_4:
                My_EXTI4_Irq = pStr->event_handler;
                tmp = EXTI4_IRQn;
                break;
            case GPIO_PIN_5:
                My_EXTI5_Irq = pStr->event_handler;
                tmp = EXTI9_5_IRQn;
            case GPIO_PIN_6:
                My_EXTI6_Irq = pStr->event_handler;
                tmp = EXTI9_5_IRQn;
                break;
            case GPIO_PIN_7:
                My_EXTI7_Irq = pStr->event_handler;
                tmp = EXTI9_5_IRQn;
                break;
            case GPIO_PIN_8:
                My_EXTI8_Irq = pStr->event_handler;
                tmp = EXTI9_5_IRQn;
                break;
            case GPIO_PIN_9:
                My_EXTI9_Irq = pStr->event_handler;
                tmp = EXTI9_5_IRQn;
                break;
            case GPIO_PIN_10:
                My_EXTI10_Irq = pStr->event_handler;
                tmp = EXTI15_10_IRQn;
                break;
            case GPIO_PIN_11:
                My_EXTI11_Irq = pStr->event_handler;
                tmp = EXTI15_10_IRQn;
            case GPIO_PIN_12:
                My_EXTI12_Irq = pStr->event_handler;
                tmp = EXTI15_10_IRQn;
                break;
            case GPIO_PIN_13:
                My_EXTI13_Irq = pStr->event_handler;
                tmp = EXTI15_10_IRQn;
                break;
            case GPIO_PIN_14:
                My_EXTI14_Irq = pStr->event_handler;
                tmp = EXTI15_10_IRQn;
                break;
            case GPIO_PIN_15:
                My_EXTI15_Irq = pStr->event_handler;
                tmp = EXTI15_10_IRQn;
                break;
            default:
                break;

    }

    MY_NVIC_Init(pStr->Priority,tmp);


}


void EXTI_set_handler(uint32_t GPIO_PIN,void* event_handler)
{
    switch (GPIO_PIN)
    {
        case GPIO_PIN_0:
                My_EXTI0_Irq = event_handler;
                break;
            case GPIO_PIN_1:
                My_EXTI1_Irq = event_handler;
                break;
            case GPIO_PIN_2:
                My_EXTI2_Irq = event_handler;
            case GPIO_PIN_3:
                My_EXTI3_Irq = event_handler;
                break;
            case GPIO_PIN_4:
                My_EXTI4_Irq = event_handler;
                break;
            case GPIO_PIN_5:
                My_EXTI5_Irq = event_handler;
            case GPIO_PIN_6:
                My_EXTI6_Irq = event_handler;
                break;
            case GPIO_PIN_7:
                My_EXTI7_Irq = event_handler;
                break;
            case GPIO_PIN_8:
                My_EXTI8_Irq = event_handler;
                break;
            case GPIO_PIN_9:
                My_EXTI9_Irq = event_handler;
                break;
            case GPIO_PIN_10:
                My_EXTI10_Irq = event_handler;
                break;
            case GPIO_PIN_11:
                My_EXTI11_Irq = event_handler;
            case GPIO_PIN_12:
                My_EXTI12_Irq = event_handler;
                break;
            case GPIO_PIN_13:
                My_EXTI13_Irq = event_handler;
                break;
            case GPIO_PIN_14:
                My_EXTI14_Irq = event_handler;
                break;
            case GPIO_PIN_15:
                My_EXTI15_Irq = event_handler;
                break;
            default:
                break;

    }

}

void EXTI0_IRQHandler()
{
    if(EXTI->PR&(1<<0))
        My_EXTI0_Irq();
    EXTI->PR |= 1<<0;

}
void EXTI1_IRQHandler()
{
    if(EXTI->PR&(1<<1))
        My_EXTI1_Irq();
    EXTI->PR |= 1<<1;

}
void EXTI2_IRQHandler()
{
    if(EXTI->PR&(1<<2))
        My_EXTI2_Irq();
    EXTI->PR |= 1<<2;

}
void EXTI3_IRQHandler()
{
    if(EXTI->PR&(1<<3))
        My_EXTI3_Irq();
    EXTI->PR |= 1<<3;

}
void EXTI4_IRQHandler()
{
    if(EXTI->PR&(1<<4))
        My_EXTI4_Irq();
    EXTI->PR |= 1<<4;

}
void EXTI9_5_IRQHandler()
{
    if(EXTI->PR&(1<<5))
    {
        My_EXTI5_Irq();
        EXTI->PR |= 1<<5;
    }
    if(EXTI->PR&(1<<6))
    {
        My_EXTI6_Irq();
        EXTI->PR |= 1<<6;
    }
    if(EXTI->PR&(1<<7))
    {
        My_EXTI7_Irq();
        EXTI->PR |= 1<<7;
    }
    if(EXTI->PR&(1<<8))
    {
        My_EXTI8_Irq();
        EXTI->PR |= 1<<8;
    }
    if(EXTI->PR&(1<<9))
    {
        My_EXTI9_Irq();
        EXTI->PR |= 1<<9;
    }

}
void EXTI15_10_IRQHandler()
{
    if(EXTI->PR&(1<<10))
    {
        My_EXTI10_Irq();
        EXTI->PR |= 1<<10;
    }
    if(EXTI->PR&(1<<11))
    {
        My_EXTI11_Irq();
        EXTI->PR |= 1<<11;
    }
    if(EXTI->PR&(1<<12))
    {
        My_EXTI12_Irq();
        EXTI->PR |= 1<<12;
    }
    if(EXTI->PR&(1<<13))
    {
        My_EXTI13_Irq();
        EXTI->PR |= 1<<13;
    }
    if(EXTI->PR&(1<<14))
    {
        My_EXTI14_Irq();
        EXTI->PR |= 1<<14;
    }
    if(EXTI->PR&(1<<15))
    {
        My_EXTI15_Irq();
        EXTI->PR |= 1<<15;
    }

}


