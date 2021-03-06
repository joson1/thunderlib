#pragma once

#include "stm32f429/gpio.h"
// typedef struct __stm32pin_mux
// {
//     uint32_t STM32AF;
//     uint32_t GPIO_OTYPE;
//     uint32_t GPIO_SPEED;
//     uint32_t GPIO_PUPD;
// 
// }stm32pin_mux_t;



#define THB_MUX_STM32F429  { \
                        __STM32MUX(120,GPIO_MODE_AF,7,0,GPIO_SPEED_100M,GPIO_PUPD_PU),  \
                        __STM32MUX(121,GPIO_MODE_AF,7,0,GPIO_SPEED_100M,GPIO_PUPD_PU),  \
                    }


