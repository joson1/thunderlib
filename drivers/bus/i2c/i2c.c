/*
 * @Author: your name
 * @Date: 2020-08-25 10:21:15
 * @LastEditTime: 2020-08-28 12:42:40
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\drivers\i2c\i2c.c
 */
#include <thunder/i2c.h>
#include <stdio.h>


// static struct i2c_dev* i2c_dev_dev_table = NULL;


int i2c_dev_attach(i2c_dev_t* dev)
{
	
	dev_register(dev,DEV_MAJOR_I2C,dev->id);
 
}

int i2c_info_register(uint8_t id,void* info)
{
	i2c_dev_t*dev=dev_open(DEV_MAJOR_I2C,id);
	dev->i2c_init_info = info;

}

int i2c_dev_remove(i2c_dev_t* dev)
{
	
	xListRemove(&(dev->devItem));
	return 0;
}


i2c_dev_t* i2c_open(uint8_t id)
{
	i2c_dev_t* pdev = dev_open(DEV_MAJOR_I2C,id);
	pdev->open();
	return pdev;
}


