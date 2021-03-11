#pragma once 
#include <thunder/device.h>


enum INPUT_EVTx{
    INPUT_EVT_BTN = 0,
	INPUT_EVT_MOUSE,
	INPUT_EVT_TOUCHSCREEN,
	INPUT_NbrOfEVT,
};

typedef struct __input_event
{
	
}input_event_t;

typedef struct __input_handler
{
	int (*read)(char* buf);
}input_handler_t;



typedef struct __input_drv
{
	ListItem_t devItem;
	xList_t inputDevList[INPUT_NbrOfEVT]; //list heads

}input_drv_t;

extern input_drv_t input_drv;

typedef struct input_dev
{
	uint8_t id;
	uint8_t event_type;
	input_handler_t* input_handler;
	ListItem_t devItem;

} input_dev_t;

int input_dev_register(input_dev_t* dev);
input_dev_t* input_dev_open(uint8_t event_type);
input_handler_t* input_open(uint8_t event_type);
void input_drv_attach();





