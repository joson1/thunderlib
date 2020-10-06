/*
 * @Author: Alanwake
 * @Date: 2020-08-25 10:05:07
 * @LastEditTime: 2020-10-06 21:30:58
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\include\thunder\spi.h
 */
#include <stdint.h>
#include <asm/spi_defs.h>
#include <stddef.h>

struct spi_dev
{
	uint8_t id;

	void (*init)(uint32_t);//
	void (*setMode)(uint32_t);//
	void (*setBitOrder)(char);//
	int (*transfer)(int);//
	void* dev_init_conf ; 
	struct spi_dev* next;
};

struct spi_dev* spi_open(uint8_t id);
int spi_transfer(struct spi_dev* dev,int data);

int spi_dev_attach(struct spi_dev* dev);
int spi_dev_register(uint8_t id,void* conf);
