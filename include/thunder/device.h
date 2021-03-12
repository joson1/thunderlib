#pragma once
#ifndef __DEVICE_H__
#define __DEVICE_H__
#include <stdint.h>
#include <xlist.h>
#include <thunder/init.h>

#define DEV_INIT(fn)		__define_initcall("0", fn, 0)

enum DEV_MAJORx{
    DEV_MAJOR_SERIAL = 0,
	DEV_MAJOR_I2C,
	DEV_MAJOR_SPI,
	DEV_MAJOR_DMA,
	DEV_MAJOR_FB,
	DEV_MAJOR_INPUT,

	DEV_NbrOfMAJOR,
};


extern xList_t devList[DEV_NbrOfMAJOR];


#define dev_register(pdev,major,id)                  \
{                                                       \
                                                        \
                                                        \
	if (devList[major].xListEnd.pxNext ==0)             \
	{                                                   \
		xList_init(&devList[major]);                    \
                                                        \
    }                                                   \
	(pdev)->devItem.xItemValue = id;                      \
	xlistSET_LIST_ITEM_OWNER(&((pdev)->devItem),pdev);      \
	xListInsert(&devList[major],&((pdev)->devItem));        \
}


void* dev_open(uint32_t major,uint32_t id);

#endif
