/*
 * @Author: your name
 * @Date: 2020-08-25 10:04:14
 * @LastEditTime: 2020-10-08 19:41:26
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\drivers\bus\spi\spi.c
 */
#include <thunder/spi.h>


// static struct spi_dev* spi_dev_dev_table = NULL;


int spi_dev_attach(spi_dev_t* dev)
{
	
	dev_register(dev,DEV_MAJOR_SPI,dev->id);
	return 0;
}

// int spi_info_register(uint8_t id,void* par)
// {
// 	spi_dev_t*dev=dev_open(DEV_MAJOR_SPI,id);
// 	dev->prv_data = par;
// 	return 0;

// }

spi_dev_t* spi_open(uint8_t id)
{
	return dev_open(DEV_MAJOR_SPI,id);	
}

int spi_transfer(spi_dev_t* dev,int data)
{
	return dev->transfer(dev,data);
}
