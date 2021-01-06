/*
 * @Author: your name
 * @Date: 2020-08-25 10:20:30
 * @LastEditTime: 2020-08-30 12:54:13
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\include\thunder\i2c.h
 */
#include <stdint.h>
#include <stddef.h>

#define I2C_CLOCK_100K   100000
#define I2C_CLOCK_200K   200000
#define I2C_CLOCK_400K   400000

struct i2c_dev
{
	uint8_t id;

	void (*set_clock)(uint32_t);//
	int (*i2c_wirte)(uint32_t slave_addr,uint8_t* buf,uint32_t length);//
	int (*i2c_read)(uint32_t slave_addr,uint8_t* buf,uint32_t length);//
	void* dev_init_conf ; 
	struct i2c_dev* next;
};


struct i2c_dev* i2c_open(uint8_t id);
void i2c_write(struct i2c_dev* dev,uint8_t* buf,uint32_t length,uint8_t addr7);

int i2c_dev_attach(struct i2c_dev* dev);
int i2c_dev_register(uint8_t id,void* conf);