#include <thunder/i2c.h>
#include <thunder/sleep.h>
#include <thunder/device.h>
#include <thunder/gpio.h>
#include <config.h>

#define I2C_SPEED_LOW 10
#define I2C_SPEED_MEDIUM 5
#define I2C_SPEED_HIGH 1

struct i2c_soft
{
    uint32_t pin_scl;
    uint32_t pin_sda;
    uint32_t speed;
    struct prv
    {
        uint32_t delay;
    };
    
};



void si2c_setup(struct i2c_soft* pi2c)
{
    gpio_pin_mode(pi2c->pin_scl,GPIO_MODE_OUTPUT);
    gpio_pin_mode(pi2c->pin_sda,GPIO_MODE_OUTPUT);
}


void static inline si2c_start(struct i2c_soft* pi2c)
{

    gpio_pin_set(pi2c->pin_scl);
    gpio_pin_set(pi2c->pin_sda);
    gpio_pin_mode(pi2c->pin_sda,GPIO_MODE_OUTPUT);

    usleep(pi2c->speed+2);
    gpio_pin_write(pi2c->pin_sda,0);
    usleep(pi2c->speed+2);
    gpio_pin_write(pi2c->pin_scl,0);

}


void static inline si2c_stop(struct i2c_soft* pi2c)
{
    gpio_pin_mode(pi2c->pin_sda,GPIO_MODE_OUTPUT);
    gpio_pin_write(pi2c->pin_scl,0);
    gpio_pin_write(pi2c->pin_sda,0);
    usleep(pi2c->speed+2);
    gpio_pin_write(pi2c->pin_scl,1);
    gpio_pin_write(pi2c->pin_sda,1);

}

void static inline si2c_ack(struct i2c_soft* pi2c)
{
    gpio_pin_write(pi2c->pin_scl,0);
    gpio_pin_mode(pi2c->pin_sda,GPIO_MODE_OUTPUT);
    gpio_pin_write(pi2c->pin_sda,0);
    usleep(pi2c->speed);
    gpio_pin_write(pi2c->pin_scl,1);
    usleep(pi2c->speed);
    gpio_pin_write(pi2c->pin_scl,0);

}

void static inline si2c_nack(struct i2c_soft* pi2c)
{
    gpio_pin_write(pi2c->pin_scl,0);
    gpio_pin_mode(pi2c->pin_sda,GPIO_MODE_OUTPUT);
    gpio_pin_write(pi2c->pin_sda,1);
    usleep(pi2c->speed);
    gpio_pin_write(pi2c->pin_scl,1);
    usleep(pi2c->speed);
    gpio_pin_write(pi2c->pin_scl,0);

}

void si2c_write(struct i2c_soft* pi2c , uint8_t txd)
{
    uint8_t t;
    gpio_pin_write(pi2c->pin_scl,0);
    gpio_pin_mode(pi2c->pin_sda,GPIO_MODE_OUTPUT);
    usleep(pi2c->speed);
    for(t=0;t<8;t++)
    {       
		// SDA_set(IIC, (txd&0x80)>>7);  
        gpio_pin_write(pi2c->pin_sda,(txd&0x80)>>7);

		// delay_us(IIC->Speed);   
        usleep(pi2c->speed);
		txd<<=1; 	
		// SCL_set(IIC, 1);
        gpio_pin_write(pi2c->pin_scl,1);

		// delay_us(IIC->Speed);
        usleep(pi2c->speed);
        gpio_pin_write(pi2c->pin_scl,0);
		
        // SCL_set(IIC, 0);
    }	 
    usleep(1);


}

uint8_t si2c_read(struct i2c_soft* pi2c , uint8_t ack)
{
	unsigned char i,receive=0;
	usleep(30);

	// SDA_IN(IIC);
    gpio_pin_mode(pi2c->pin_sda,GPIO_MODE_INPUT);

    for(i=0;i<8;i++ )
	{
        // SCL_set(IIC, 0);
        gpio_pin_write(pi2c->pin_scl,0);

        // delay_us(IIC->Speed);
        usleep(pi2c->speed);
	
    	// SCL_set(IIC, 1);
        gpio_pin_write(pi2c->pin_scl,1);
    
        receive<<=1;
        // if(SDA_read(IIC))receive++;   
        if(gpio_pin_read(pi2c->pin_sda))receive++;   
		// delay_us(IIC->Speed);
        usleep(pi2c->speed);
        
    }					 
    if (!ack)
        // IIC_NAck(IIC);//??nACK
        si2c_nack(pi2c);
    else
        // IIC_Ack(IIC); //??ACK  
        si2c_ack(pi2c);

    return receive;
}

uint8_t si2c_wait_ack(struct i2c_soft* pi2c )
{
	uint8_t time = 0;

	// SDA_IN(IIC);

	// SDA_set(IIC, 1); delay_us(IIC->Speed+2);
    gpio_pin_mode(pi2c->pin_sda,GPIO_MODE_OUTPUT);
    gpio_pin_write(pi2c->pin_sda,1);  usleep(pi2c->speed+2);

    gpio_pin_mode(pi2c->pin_sda,GPIO_MODE_INPUT);
	// SCL_set(IIC, 1); delay_us(IIC->Speed+2);
    gpio_pin_write(pi2c->pin_scl,1);  usleep(pi2c->speed+2);
	
    
	while (gpio_pin_read(pi2c->pin_sda))
	{
		time++;
		if (time > 0xfd)
		{
			//while(1);
			// IIC_stop(IIC);
            si2c_stop(pi2c);
			return 1;
		}
	}
	// SCL_set(IIC, 0);
    gpio_pin_write(pi2c->pin_scl,0);

	return 0;
}



void dev_si2c_setup(i2c_dev_t* pdev)
{
    si2c_setup((struct i2c_soft*)(pdev->prv_data));
}




int dev_si2c_write(i2c_dev_t* pdev, uint32_t slave_addr,uint8_t* buf,uint32_t length)
{

	u8 i; 
    // IIC_start((IIC_TypeDef*)(i2c0.i2c_init_info)); 
    si2c_start((struct i2c_soft*)(pdev->prv_data));
	// IIC_write((IIC_TypeDef*)(i2c0.i2c_init_info),(slave_addr<<1)|0);//发送器件地址+写命令
    si2c_write((struct i2c_soft*)(pdev->prv_data),(slave_addr<<1)|0);

	// if(IIC_wait_ack((IIC_TypeDef*)(i2c0.i2c_init_info)))	//等待应答
    if(si2c_wait_ack((struct i2c_soft*)(pdev->prv_data)))
	{
		// IIC_stop((IIC_TypeDef*)(i2c0.i2c_init_info));	
        si2c_stop((struct i2c_soft*)(pdev->prv_data));	 
		return -1;		
	}
    // IIC_write((IIC_TypeDef*)(i2c0.i2c_init_info),reg);	//写寄存器地址
    // IIC_wait_ack((IIC_TypeDef*)(i2c0.i2c_init_info));		//等待应答
	for(i=0;i<length;i++)
	{
		// IIC_write((IIC_TypeDef*)(i2c0.i2c_init_info),buf[i]);	//发送数据
        si2c_write((struct i2c_soft*)(pdev->prv_data),buf[i]);

		// if(IIC_wait_ack((IIC_TypeDef*)(i2c0.i2c_init_info)))		//等待ACK
        if(si2c_wait_ack((struct i2c_soft*)(pdev->prv_data)))
		{
			// IIC_stop((IIC_TypeDef*)(i2c0.i2c_init_info));	 
            si2c_stop((struct i2c_soft*)(pdev->prv_data));
			return -1;		 
		}	
		

	}    
    // IIC_stop((IIC_TypeDef*)(i2c0.i2c_init_info));	 
    si2c_stop((struct i2c_soft*)(pdev->prv_data));

	return 0;	

}


int dev_si2c_read(i2c_dev_t* pdev, uint32_t slave_addr,uint8_t* buf,uint32_t length)
{

	char* p= (char*)buf;
    // IIC_start((IIC_TypeDef*)(i2c0.i2c_init_info));
    si2c_start((struct i2c_soft*)(pdev->prv_data));

	// IIC_write((IIC_TypeDef*)(i2c0.i2c_init_info),(slave_addr<<1)|1);//发送器件地址+读命令	
    si2c_write((struct i2c_soft*)(pdev->prv_data),(slave_addr<<1)|1);

    // IIC_wait_ack((IIC_TypeDef*)(i2c0.i2c_init_info));		//等待应答 
	si2c_wait_ack((struct i2c_soft*)(pdev->prv_data));
    // usleep(20);
	while(length)
	{
		if(length==1)
		{
			// *p=IIC_read((IIC_TypeDef*)(i2c0.i2c_init_info),0);//读数据,发送nACK 
            *p = si2c_read((struct i2c_soft*)(pdev->prv_data),0);
		}else
		{
			// *p=IIC_read((IIC_TypeDef*)(i2c0.i2c_init_info),1);		//读数据,发送ACK
            *p = si2c_read((struct i2c_soft*)(pdev->prv_data),1);  
		} 
		length--;
		p++; 
	}    
    // IIC_stop((IIC_TypeDef*)(i2c0.i2c_init_info));	//产生一个停止条件 
    si2c_stop((struct i2c_soft*)(pdev->prv_data));
    return 0;
}



#if CONFIG_SOFT_I2C0_EN

struct i2c_soft si2c0_con = {
    .pin_scl = CONFIG_SOFT_I2C0_SCL,
    .pin_sda = CONFIG_SOFT_I2C0_SDA,
    .speed = I2C_SPEED_MEDIUM,
};



i2c_dev_t si2c0 = {
    .id = CONFIG_SOFT_I2C0_ID,
    .prv_data = &si2c0_con,
    .setup = dev_si2c_setup,
    .i2c_wirte = dev_si2c_write,
    .i2c_read = dev_si2c_read

};

#endif

void soft_i2c_init()
{
#if CONFIG_SOFT_I2C0_EN
    i2c_dev_attach(&si2c0);
#endif

}

DEV_INIT(soft_i2c_init);

