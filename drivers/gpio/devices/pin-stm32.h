#pragma once

#define __STM32_PIN_DESC(id,GPIOx,PINx) {.pin_id=id,.bank=GPIO##GPIOx,.pin=GPIO_PIN_##PINx}

#define PINS_STM32F429 \
{                               \
    __STM32_PIN_DESC(0,A,0),    \
    __STM32_PIN_DESC(1,A,1),    \
    __STM32_PIN_DESC(1,A,1),    \
                                \
}



