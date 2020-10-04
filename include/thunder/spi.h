/*
 * @Author: Alanwake
 * @Date: 2020-08-25 10:05:07
 * @LastEditTime: 2020-08-31 19:30:24
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\include\thunder\spi.h
 */
#include <stdint.h>

struct spi_dev
{
	uint8_t id;

	void (*setMode)(uint32_t);//
	void (*setBitOrder)(char);//
	int (*transfer)(int);//
	void* dev_init_conf ; 
	struct spi_dev* next;
};

struct spi_dev* spi_open(uint8_t id);
void i2c_write(struct i2c_dev* dev,uint8_t* buf,uint32_t length,uint8_t addr7);

int i2c_dev_attach(struct i2c_dev* dev);
int i2c_dev_register(uint8_t id,void* conf);
