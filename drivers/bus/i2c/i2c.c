/*
 * @Author: your name
 * @Date: 2020-08-25 10:21:15
 * @LastEditTime: 2020-08-28 12:42:40
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\drivers\i2c\i2c.c
 */
#include <thunder/i2c.h>



static struct i2c_dev* i2c_dev_dev_table = NULL;



int i2c_dev_attach(struct i2c_dev* dev)
{
	struct i2c_dev* p;
	if (i2c_dev_dev_table==NULL)
	{
		i2c_dev_dev_table = dev;
		return 0;
	}else
	{
		p = i2c_dev_dev_table;
		while (p->next!=NULL)
		{
			p = p->next;
		}
		p->next = dev;
		
	}
	return 0;
}


struct i2c_dev* i2c_open(uint8_t id)
{
	struct i2c_dev* p = i2c_dev_dev_table ;
	if (p==NULL)
	{
        
		//no i2c devices;
		return NULL;
	}
	
	while (p->id!=id)
	{
		p = p->next;
		if (p==NULL)
			return NULL;
	}

    return p;

}
