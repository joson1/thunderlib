/*
 * @Author: your name
 * @Date: 2020-08-06 23:02:11
 * @LastEditTime: 2020-08-06 23:46:48
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\arch\arm\st\include\stm32f429\spi.h
 */
#ifndef __SPI_H__
#define __SPI_H__
#include "stm32f429/sys.h"
#include "stm32f429/gpio.h"
// #define SPI_FRAME_MSB 0
// #define SPI_FRAME_LSB 1

// #define SPI_MODE_1 0X02			//时钟空闲状态为高，下降沿采样
// #define SPI_MODE_2 0X03			//时钟空闲状态为高，上升沿采样
// #define SPI_MODE_3 0X01			//时钟空闲状态为低，下降沿采样
// #define SPI_MODE_4 0X00			//时钟空闲状态为低，上升沿采样

#define SPI_8Bits_Mode  8
#define SPI_16Bits_Mode 16



typedef struct _SPI_InitDef 
{
    uint32_t    AFn;
    stm32pin_t mosi;
    stm32pin_t miso;
    stm32pin_t sck;

}SPI_InitDef ;


void SPI_init(SPI_TypeDef *SPIx, u8 SPI_MODE, u8 width, u8 SPI_Speed_Grade);
u8 SPI_Write_Read(SPI_TypeDef *SPIx, u8 data);


//extern void SPI_init(SPI_TypeDef *SPIx, u8 SPI_MODE, u8 SPI_DATA_WIDTH, u8 SPI_PCLK_DEV, u8 SPI_FRAME);
//extern void SPI_close(SPI_TypeDef *SPIx);


#endif


