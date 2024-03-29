/*
 * @Author: your name
 * @Date: 2020-08-03 22:11:32
 * @LastEditTime: 2020-08-10 16:32:04
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\arch\arm\st\stm32f429\boards\thunderboards32.c
 */
#include "thunderboards32.h"
#include <config.h>
#include <thunder/tty/tty.h>
#include <thunder/pinmux.h>
#include "mux-stm32f429.h"
#include "stm32f429/sdram.h"
extern void stm32f429_serial_init();
extern void stm32f429_timer_init();



extern void stm32f429_spi_init();

extern int fb_stm32ltdc_init();
extern void input_drv_attach();



 

#define Bank5_SDRAM_ADDR    ((0XC0000000)) 			//
//

void sram_init()
{
    SDRAM_Init();
}
extern void sram_init();

void board_init()
{

//     // SDRAM_Init();
// #if(CONFIG_SERIAL_EN)
    pinmux_table_set(sizeof(THB_MUX_STM32F429),THB_MUX_STM32F429);
    // serial_info_register(0,&uart1_conf);
    // serial_info_register(1,&uart2_conf);
// #endif
    cmd_init(0,1);
//     // fb_stm32ltdc_init();

// #if(CONFIG_I2C_EN)
//     stm32f429_i2c_init();
//     i2c_info_register(0,&i2c0_conf);
// #endif


// #if(CONFIG_SPI_EN)
//     stm32f429_spi_init();
//     spi_info_register(0,&spi0_conf);
//     spi_info_register(1,&spi1_conf);

// #endif
//     // input_drv_attach();
// #if(CONFIG_TIMER_EN)
//     stm32f429_timer_init();
// #endif

}










