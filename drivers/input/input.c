#include<thunder/input.h>


input_dev_t* input_dev_open(uint8_t event_type)
{

	input_dev_t* pdev = dev_open(DEV_MAJOR_INPUT,event_type);
	return pdev;
}

input_handler_t* input_open(uint8_t event_type)
{

	input_dev_t* pdev = dev_open(DEV_MAJOR_INPUT,event_type);
	return pdev->input_handler;

}


void input_dev_attach(input_dev_t* pdev,uint8_t event_type)
{
	dev_register(pdev,DEV_MAJOR_INPUT,event_type);
	
}

