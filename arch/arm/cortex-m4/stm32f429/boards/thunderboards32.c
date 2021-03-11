/*
 * @Author: your name
 * @Date: 2020-08-03 22:11:32
 * @LastEditTime: 2020-08-10 16:32:04
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\arch\arm\st\stm32f429\boards\thunderboards32.c
 */
#include "stm32f429xx.h"
#include "stm32f429/usart.h"
#include "stm32f429/timer.h"
#include <thunder/serial.h>
#include <config.h>
#include <thunder/i2c.h>
#include "stm32f429/iic.h"
#include <thunder/spi.h>
#include "stm32f429/spi.h"
#include "stm32f429/sdram.h"

extern void stm32f429_serial_init();
extern void stm32f429_timer_init();


Uart_InitDef uart1_conf = 
{
    .GPIOx_RX  = GPIOA,
    .GPIOx_TX  = GPIOA,
    .PIN_RX    = GPIO_PIN_10,
    .PIN_TX    = GPIO_PIN_9,
    .GPIO_AF   = 7,
    .pclk2     = 90,
    .rx_int_en = 1,
    .Priority  = 3,
};
Uart_InitDef uart2_conf = 
{
    .GPIOx_RX  = GPIOA,
    .GPIOx_TX  = GPIOA,
    .PIN_RX    = GPIO_PIN_3,
    .PIN_TX    = GPIO_PIN_2,
    .GPIO_AF   = 7,
    .pclk2     = 45,
    .rx_int_en = 1,
    .Priority  = 12,

};

IIC_TypeDef i2c0_conf = 
{
    .SDA_GPIOx = GPIOI,
    .SDA_PIN = GPIO_PIN_3,
    .SCL_GPIOx = GPIOH, 
    .SCL_PIN = GPIO_PIN_6,
    .Speed = IIC_SPEED_HIGH,
};


extern stm32f429_i2c_init();

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


extern void stm32f429_spi_init();

extern int fb_stm32ltdc_init();
extern void input_drv_attach();

void board_init()
{

    SDRAM_Init();
#if(CONFIG_SERIAL_EN)
    stm32f429_serial_init();
    serial_info_register(0,&uart1_conf);
    serial_info_register(1,&uart2_conf);
#endif

    // fb_stm32ltdc_init();

#if(CONFIG_I2C_EN)
    stm32f429_i2c_init();
    i2c_info_register(0,&i2c0_conf);
#endif


#if(CONFIG_SPI_EN)
    stm32f429_spi_init();
    spi_info_register(0,&spi0_conf);
    spi_info_register(1,&spi1_conf);

#endif
    input_drv_attach();
#if(CONFIG_TIMER_EN)
    stm32f429_timer_init();
#endif

}










