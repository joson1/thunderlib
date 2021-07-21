#pragma once


#include "stm32f429xx.h"
#include "stm32f429/usart.h"
#include "stm32f429/timer.h"
#include <thunder/serial.h>

#include <thunder/i2c.h>
#include "stm32f429/iic.h"
#include <thunder/spi.h>
#include "stm32f429/spi.h"



IIC_TypeDef i2c0_conf = 
{
    .SDA_GPIOx = GPIOI,
    .SDA_PIN = GPIO_PIN_3,
    .SCL_GPIOx = GPIOH, 
    .SCL_PIN = GPIO_PIN_6,
    .Speed = IIC_SPEED_HIGH,
};


// extern stm32f429_i2c_init();

SPI_InitDef spi0_conf = 
{   
    .AFn   = 5,
    .mosi = __STM32PIN(A,7),
    .miso = __STM32PIN(A,6),
    .sck  = __STM32PIN(A,6),
};

SPI_InitDef spi1_conf = 
{
    .AFn   = 5,
    .mosi = __STM32PIN(B,15),
    .miso = __STM32PIN(B,14),
    .sck  = __STM32PIN(B,13),
};



