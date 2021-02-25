#pragma once
#include "zynq7000/gpio.h"

#define __ZYNQ_PIN_DESC(id,bankn,mion) {.pin_id=id,.bank=&GPIO_BANK##bankn,.pin=BANK##bankn##_MIO_##mion}

#define PINS_ZYNQ7020           \
{                               \
    __ZYNQ_PIN_DESC(0,0,0),     \
    __ZYNQ_PIN_DESC(1,0,1),     \
    __ZYNQ_PIN_DESC(1,0,2),     \
}                               \

