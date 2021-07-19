#pragma once

#include <stdint.h>


extern const uint32_t nBrOfPar;
extern uint32_t pinmux_table[];

int pin_mux_set(uint32_t pin_id,uint32_t* par); //low level

int pinmux_table_set(uint32_t size,uint32_t* ptable);

