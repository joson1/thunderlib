#include <thunder/i2c.h>
#include "stm32f429/iic.h"
#include <thunder/sleep.h>
#include <thunder/device.h>


/*
under development
*/

//i2c2 ph4 ph5
void I2C_init(I2C_TypeDef* pi2c,uint32_t speed)
{
	if(pi2c==I2C1)
		RCC->APB1ENR |= (1<<5);
	else if(pi2c==I2C2)
		RCC->APB1ENR |= (1<<6);
	else if(pi2c==I2C3)
		RCC->APB1ENR |= (1<<7);


	pi2c->CR1 |= (1<<3);
	pi2c->CR1 |= (1<<0);

}

// int i2c0_write(uint32_t slave_addr,uint8_t* buf,uint32_t length)
// {

// 	u8 i; 
//     IIC_start((IIC_TypeDef*)(i2c0.i2c_init_info)); 
// 	IIC_write((IIC_TypeDef*)(i2c0.i2c_init_info),(slave_addr<<1)|0);//发送器件地址+写命令	
// 	if(IIC_wait_ack((IIC_TypeDef*)(i2c0.i2c_init_info)))	//等待应答
// 	{
// 		IIC_stop((IIC_TypeDef*)(i2c0.i2c_init_info));		 
// 		return -1;		
// 	}
//     // IIC_write((IIC_TypeDef*)(i2c0.i2c_init_info),reg);	//写寄存器地址
//     // IIC_wait_ack((IIC_TypeDef*)(i2c0.i2c_init_info));		//等待应答
// 	for(i=0;i<length;i++)
// 	{
// 		IIC_write((IIC_TypeDef*)(i2c0.i2c_init_info),buf[i]);	//发送数据
// 		if(IIC_wait_ack((IIC_TypeDef*)(i2c0.i2c_init_info)))		//等待ACK
// 		{
// 			IIC_stop((IIC_TypeDef*)(i2c0.i2c_init_info));	 
// 			return -1;		 
// 		}	
		

// 	}    
//     IIC_stop((IIC_TypeDef*)(i2c0.i2c_init_info));	 
// 	return 0;	

// }


// int i2c0_read(uint32_t slave_addr,uint8_t* buf,uint32_t length)
// {
//  	// IIC_start((IIC_TypeDef*)(i2c0.i2c_init_info)); 
// 	// IIC_write((IIC_TypeDef*)(i2c0.i2c_init_info),(addr<<1)|0);//发送器件地址+写命令	
// 	// if(IIC_wait_ack((IIC_TypeDef*)(i2c0.i2c_init_info)))	//等待应答
// 	// {
// 	// 	IIC_stop((IIC_TypeDef*)(i2c0.i2c_init_info));		 
// 	// 	return 1;		
// 	// }
//     // IIC_write((IIC_TypeDef*)(i2c0.i2c_init_info),reg);	//写寄存器地址
//     // IIC_wait_ack((IIC_TypeDef*)(i2c0.i2c_init_info));		//等待应答
// 	char* p= (char*)buf;
//     IIC_start((IIC_TypeDef*)(i2c0.i2c_init_info));
// 	IIC_write((IIC_TypeDef*)(i2c0.i2c_init_info),(slave_addr<<1)|1);//发送器件地址+读命令	
//     IIC_wait_ack((IIC_TypeDef*)(i2c0.i2c_init_info));		//等待应答 
// 	// usleep(20);
// 	while(length)
// 	{
// 		if(length==1)
// 		{
// 			*p=IIC_read((IIC_TypeDef*)(i2c0.i2c_init_info),0);//读数据,发送nACK 
// 		}else
// 		{
// 			*p=IIC_read((IIC_TypeDef*)(i2c0.i2c_init_info),1);		//读数据,发送ACK  
// 		} 
// 		length--;
// 		p++; 
// 	}    
//     IIC_stop((IIC_TypeDef*)(i2c0.i2c_init_info));	//产生一个停止条件 
//     return 0;
// }

// void i2c0_open()
// {
// 	IIC_Init((IIC_TypeDef*)(i2c0.i2c_init_info));
// }


static int stm32f429_i2c_setup(i2c_dev_t* pdev)
{
	I2C_TypeDef* pdata = (I2C_TypeDef*)(pdev->prv_data);
	pdata->CR1
}


i2c_dev_t i2c0 = {
    .id = 0,
	.prv_data = I2C1,
	.setup = stm32f429_i2c_setup,
    .i2c_wirte = i2c0_write,
    .i2c_read  = i2c0_read,

};
// i2c_dev_t i2c1 = {
//     .id = 1,
//     .i2c_wirte = i2c1_write,
//     .i2c_read  = i2c1_read

// };


void stm32f429_i2c_init()
{

    i2c_dev_attach(&i2c0);
    // i2c_dev_attach(&i2c1);
}

DEV_INIT(stm32f429_i2c_init);
