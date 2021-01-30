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

typedef struct __spi_dev
{
	uint8_t id;

	void (*init)(uint32_t);//
	void (*setMode)(uint32_t);//
	void (*setBitOrder)(char);//
	void (*setClkDiv)(uint8_t);//
	int (*transfer)(int);//
	void* spi_init_info ; 
	ListItem_t devItem;
}spi_dev_t;

spi_dev_t* spi_open(uint8_t id);
int spi_transfer(spi_dev_t* dev,int data);

int spi_dev_attach(spi_dev_t* dev,void* pInfo);
// int spi_dev_register(uint8_t id,void* conf);
