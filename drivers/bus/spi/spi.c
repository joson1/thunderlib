/*
 * @Author: your name
 * @Date: 2020-08-25 10:04:14
 * @LastEditTime: 2020-10-08 19:41:26
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\drivers\bus\spi\spi.c
 */
#include <thunder/spi.h>


static struct spi_dev* spi_dev_dev_table = NULL;



int spi_dev_attach(struct spi_dev* dev)
{
	struct spi_dev* p;
	if (spi_dev_dev_table==NULL)
	{
		spi_dev_dev_table = dev;
		return 0;
	}else
	{
		p = spi_dev_dev_table;
		while (p->next!=NULL)
		{
			p = p->next;
		}
		p->next = dev;
		
	}
	return 0;
}


struct spi_dev* spi_open(uint8_t id)
{
	struct spi_dev* p = spi_dev_dev_table ;
	if (p==NULL)
	{
        
		//no spi devices;
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

int spi_transfer(struct spi_dev* dev,int data)
{
	return dev->transfer(data);
}
