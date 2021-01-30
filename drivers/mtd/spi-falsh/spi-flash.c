/*
 * @Author: your name
 * @Date: 2020-10-08 18:45:15
 * @LastEditTime: 2020-10-08 21:44:42
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\drivers\mtd\spi-falsh\spi-flash.c
 */
#include "mtd/spi-flash.h"
#include <thunder/spi.h>
#include <thunder/gpio.h>
#include <stdio.h>

#define W25Q256 0XEF18
spi_dev_t* spi_flash;
int W25QXX_CS = 3;
uint16_t W25QXX_TYPE=W25Q256;	//默认是W25Q256

//0XEF14,表示芯片型号为W25Q16    





uint16_t W25QXX_ReadID(void)
{
	uint16_t Temp = 0;	  
	// W25QXX_CS=0;		
    gpio_pin_reset(W25QXX_CS);

	// SPI_Write_Read(SPI5,0x90);//发送读取ID命令	   
    spi_transfer(spi_flash,0x90); 
	// SPI_Write_Read(SPI5,0x00); 	
    spi_transfer(spi_flash,0x00); 

	// SPI_Write_Read(SPI5,0x00); 	  
    spi_transfer(spi_flash,0x00); 
    spi_transfer(spi_flash,0x00); 

	Temp|=spi_transfer(spi_flash,0xFF)<<8;  
	Temp|=spi_transfer(spi_flash,0xFF);	 
	// W25QXX_CS=1;
    gpio_pin_set(W25QXX_CS);				    
	return Temp;
}

void W25QXX_Init(void)
{
    uint8_t temp;


	W25QXX_TYPE=W25QXX_ReadID();	//读取FLASH ID.
    printf("spi:%d\r\n",W25QXX_TYPE);
}

void spi_flah_test()
{
    //open
    spi_flash=spi_open(0);
    spi_flash->init(SPI_MODE_3);

    gpio_pin_mode(W25QXX_CS,GPIO_MODE_OUTPUT);
    gpio_pin_set(W25QXX_CS);
    W25QXX_Init();
}

