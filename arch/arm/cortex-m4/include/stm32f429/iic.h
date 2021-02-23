#ifndef __IIC_H__
#define __IIC_H__

#define IIC_SPEED_LOW 10
#define IIC_SPEED_MEDIUM 5
#define IIC_SPEED_HIGH 1

#include "stm32f429/sys.h"

typedef struct 
{
    GPIO_TypeDef* SDA_GPIOx;
    u16 SDA_PIN;
    GPIO_TypeDef* SCL_GPIOx; 
    u16 SCL_PIN;
    u8 Speed;
   
} IIC_TypeDef;
extern void IIC_Init(IIC_TypeDef *IIC);
extern void IIC_start(IIC_TypeDef *IIC);
extern void IIC_stop(IIC_TypeDef *IIC);
extern void IIC_write(IIC_TypeDef *IIC,uint8_t val);
extern uint8_t IIC_read(IIC_TypeDef *IIC,uint8_t ack);
extern uint8_t IIC_wait_ack(IIC_TypeDef *IIC);

extern void IIC_Ack(IIC_TypeDef *IIC);
extern void IIC_NAck(IIC_TypeDef *IIC);

#endif