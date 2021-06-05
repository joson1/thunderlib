#include <thunder/pinmux.h>
#include <thunder/gpio.h>
#include "stm32f429/gpio.h"
#include <thunder/device.h>

// #include "mux-stm32f429.h"

const uint32_t nBrOfPar = 6;

#define PAR_ID          0
#define PAR_MODE        1
#define PAR_AF          2
#define PAR_OTYPE       3
#define PAR_SPEED       4
#define PAR_PUPD        5

// uint32_t pinmux_table[] = MUX_STM32F429;

int pin_mux_set(uint32_t pin_id,uint32_t* par)
{
    struct pinDesc* pPin=&pin_map[pin_id];
    GPIO_Init(pPin->bank,pPin->pin,par[PAR_MODE],par[PAR_OTYPE],par[PAR_SPEED],par[PAR_PUPD]);
    if(par[PAR_MODE]==GPIO_MODE_AF)
        GPIO_AF_Set(pPin->bank,pPin->pin,par[PAR_AF]);

}

