/*
 * @Author: your name
 * @Date: 2020-10-09 09:23:55
 * @LastEditTime: 2020-10-09 11:15:16
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\drivers\sensors\ads1292\ads1292.c
 */

#include "sensors/ads1292.h"
#include <thunder/spi.h>
#include <stdint.h>

struct spi_dev* ads12;

void ads1292_init()
{
    ads12=spi_open(0);
    ads12->init(SPI_MODE_0);
    ads12->setClkDiv(SPI_CLOCK_DIV32);
    
}


int ads1292_write_read(uint8_t reg,uint8_t data)
{
    return ads12->transfer(data);
}
