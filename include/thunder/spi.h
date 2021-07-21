/*
 * @Author: Alanwake
 * @Date: 2020-08-25 10:05:07
 * @LastEditTime: 2020-10-09 10:29:45
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\include\thunder\spi.h
 */
#include <stdint.h>
#include <asm/spi_defs.h>
#include <stddef.h>
#include <thunder/device.h>

typedef struct __spi_dev spi_dev_t;
struct __spi_dev
{
	uint8_t id;

	void* prv_data; 

	void (*setup)(spi_dev_t* pdev,uint32_t mode,uint32_t bitOrder);//
	// void (*setMode)(uint32_t mode);//
	// void (*setBitOrder)(char Order);//
	void (*setClk)(spi_dev_t* pdev,uint32_t freq);//
	int (*transfer)(spi_dev_t* pdev,int data);//
	int (*write)(spi_dev_t* pdev,int data);//
	int (*read)(spi_dev_t* pdev);//
	ListItem_t devItem;
};

spi_dev_t* spi_open(uint8_t id);
int spi_transfer(spi_dev_t* dev,int data);

int spi_dev_attach(spi_dev_t* dev);
int spi_info_register(uint8_t id,void* info);
