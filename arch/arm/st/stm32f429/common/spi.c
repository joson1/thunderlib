//SpeedSet:0~7   对SPI2 和SPI3(APB1)
//SPI速度=fAPB1/2^(SpeedSet+1)     
//fAPB1时钟一般为45Mhz


//SpeedSet:0~7   对SPI1,4,5,6(APB2)
//SPI 速度=fAPB2/2^(SpeedSet+1)
//fAPB2 时钟一般为 90Mhz

/*
SPI时钟源说明：
	SPI2&SPI3:       PCLK1 = 45M
	SPI1,4,5,6:      PCLK2 = 90M
	
	分频后波特率(速度等级:1~8):
	SPI2_CLK    	= 45M/(2^速度等级)
	SPI3_CLK    	= 45M/(2^速度等级)
	其它SPI_CLK 	=  90M/(2^速度等级)

SPI_init(SPI_TypeDef *SPIx, u8 SPI_MODE, u8 width, u8 SPI_Speed_Grade)函数说明：
默认配置:
	主从模式：    主机
	通信模式：	  双线双向全双工
	硬件CRC校验： 不启用
	DMA：         不启用
	软件从设备管理： 启用（SPI NSS线不用，使用软件片选）
	帧格式：       先发送MSB
参数说明：
	SPIx：SPI1/SPI2/SPI3/SPI4/SPI5/SPI6
	SPI_MODE:
		SPI_MODE_1		时钟空闲状态为高，下降沿采样
		SPI_MODE_2		时钟空闲状态为高，上升沿采样
		SPI_MODE_3		时钟空闲状态为低，下降沿采样
		SPI_MODE_4		时钟空闲状态为低，上升沿采样
	width: 数据传输宽度8 or 16
		SPI_8Bits_Mode
		SPI_16Bits_Mode
	SPI_Speed_Grade: 设置spi速度等级（共1~8八个等级）
		可选参数为数字1 ~ 8
		设置为1时最快，可动态改变spi波特率（非通信期间）

SPI_Write_Read(SPI_TypeDef *SPIx, u8 data)函数说明：
	SPIx写一个字节的同时读回一个字节
	data： 待写数据
	返回值： 读回的字节

demo:使用SPI1驱动NF24L01
	首先确定从设备工作在SPI的哪个工作模式（确定时钟极性和采样边沿儿），确定SPI_MODE参数为SPI_MODE_4
	设置数据位宽度为SPI_8Bits_Mode
	设置SPI通信速度等级为3，SPI1_CLK = PCLK2/(2^速度等级) = 90M / (2^3) = 9M      (NRF24L01最大通信速度不能超过10M)
		SPI_init(SPI1, SPI_MODE_4, SPI_8Bits_Mode, 3);
	初始化完成！调用SPI_Write_Read函数即可与24L01进行通信。
*/
#include "stm32f429/spi.h"


void SPI_init(SPI_TypeDef *SPIx, u8 SPI_MODE, u8 width, u8 SPI_Speed_Grade)
{
	if(SPIx==SPI1)
		RCC->APB2ENR |= 1<<12;
	else if(SPIx==SPI2)
		RCC->APB1ENR |= 1<<14;
	else if(SPIx==SPI3)
		RCC->APB1ENR |= 1<<15;
	else if(SPIx==SPI4)
		RCC->APB2ENR |= 1<<13;
	else if(SPIx==SPI5)
		RCC->APB2ENR |= 1<<20;
	else if(SPIx==SPI6)
		RCC->APB2ENR |= 1<<21;
	
	SPIx->CR1 &= ~(1<<6);
	SPIx->CR1 = 0X0304;
	SPIx->CR1 |= (width/8 -1)<<11;
	SPIx->CR1 |= SPI_MODE; 

	SPIx->CR1 &= 0XFFC7;
	SPIx->CR1 |= (SPI_Speed_Grade-1)<<3;
	SPIx->CR1 |= 1<<6;
	
	SPI_Write_Read(SPIx,0XFF);
}

//写一个字节的同时读回一个字节
u8 SPI_Write_Read(SPI_TypeDef *SPIx, u8 data)
{
	while((SPIx->SR&1<<1)==0);		//等待发送区空 
	SPIx->DR=data;	 	  		//发送一个byte  
	while((SPIx->SR&1<<0)==0)
	{
	}		//等待接收完一个byte  
 	return SPIx->DR;          		//返回收到的数据
}


void SPI_close(SPI_TypeDef *SPIx)
{
	SPIx->CR1 &= ~(1 << 6);
}
