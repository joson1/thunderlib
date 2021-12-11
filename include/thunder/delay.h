#pragma once

#include <stdint.h>

void delay_ms(uint32_t ms);
void delay_us(uint32_t us);



extern void __attribute__((weak)) _delay_ms(uint32_t ms);
extern void __attribute__((weak)) _delay_us(uint32_t us);


