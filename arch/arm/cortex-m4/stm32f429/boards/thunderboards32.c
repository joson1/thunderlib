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
#include "stm32f429/sdram.h"
#include <thunder/tty/tty.h>
#include <thunder/pinmux.h>
#include "mux-stm32f429.h"

extern void stm32f429_serial_init();
extern void stm32f429_timer_init();



extern void stm32f429_spi_init();

extern int fb_stm32ltdc_init();
extern void input_drv_attach();


uint32_t pin_mux_table[] = THB_MUX_STM32F429;

void board_init()
{

//     // SDRAM_Init();
// #if(CONFIG_SERIAL_EN)
    pinmux_table_set(sizeof(pin_mux_table),pin_mux_table);
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










