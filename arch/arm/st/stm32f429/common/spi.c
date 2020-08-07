//SpeedSet:0~7   ��SPI2 ��SPI3(APB1)
//SPI�ٶ�=fAPB1/2^(SpeedSet+1)     
//fAPB1ʱ��һ��Ϊ45Mhz


//SpeedSet:0~7   ��SPI1,4,5,6(APB2)
//SPI �ٶ�=fAPB2/2^(SpeedSet+1)
//fAPB2 ʱ��һ��Ϊ 90Mhz

/*
SPIʱ��Դ˵����
	SPI2&SPI3:       PCLK1 = 45M
	SPI1,4,5,6:      PCLK2 = 90M
	
	��Ƶ������(�ٶȵȼ�:1~8):
	SPI2_CLK    	= 45M/(2^�ٶȵȼ�)
	SPI3_CLK    	= 45M/(2^�ٶȵȼ�)
	����SPI_CLK 	=  90M/(2^�ٶȵȼ�)

SPI_init(SPI_TypeDef *SPIx, u8 SPI_MODE, u8 width, u8 SPI_Speed_Grade)����˵����
Ĭ������:
	����ģʽ��    ����
	ͨ��ģʽ��	  ˫��˫��ȫ˫��
	Ӳ��CRCУ�飺 ������
	DMA��         ������
	������豸���� ���ã�SPI NSS�߲��ã�ʹ�����Ƭѡ��
	֡��ʽ��       �ȷ���MSB
����˵����
	SPIx��SPI1/SPI2/SPI3/SPI4/SPI5/SPI6
	SPI_MODE:
		SPI_MODE_1		ʱ�ӿ���״̬Ϊ�ߣ��½��ز���
		SPI_MODE_2		ʱ�ӿ���״̬Ϊ�ߣ������ز���
		SPI_MODE_3		ʱ�ӿ���״̬Ϊ�ͣ��½��ز���
		SPI_MODE_4		ʱ�ӿ���״̬Ϊ�ͣ������ز���
	width: ���ݴ�����8 or 16
		SPI_8Bits_Mode
		SPI_16Bits_Mode
	SPI_Speed_Grade: ����spi�ٶȵȼ�����1~8�˸��ȼ���
		��ѡ����Ϊ����1 ~ 8
		����Ϊ1ʱ��죬�ɶ�̬�ı�spi�����ʣ���ͨ���ڼ䣩

SPI_Write_Read(SPI_TypeDef *SPIx, u8 data)����˵����
	SPIxдһ���ֽڵ�ͬʱ����һ���ֽ�
	data�� ��д����
	����ֵ�� ���ص��ֽ�

demo:ʹ��SPI1����NF24L01
	����ȷ�����豸������SPI���ĸ�����ģʽ��ȷ��ʱ�Ӽ��ԺͲ������ض�����ȷ��SPI_MODE����ΪSPI_MODE_4
	��������λ���ΪSPI_8Bits_Mode
	����SPIͨ���ٶȵȼ�Ϊ3��SPI1_CLK = PCLK2/(2^�ٶȵȼ�) = 90M / (2^3) = 9M      (NRF24L01���ͨ���ٶȲ��ܳ���10M)
		SPI_init(SPI1, SPI_MODE_4, SPI_8Bits_Mode, 3);
	��ʼ����ɣ�����SPI_Write_Read����������24L01����ͨ�š�
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

//дһ���ֽڵ�ͬʱ����һ���ֽ�
u8 SPI_Write_Read(SPI_TypeDef *SPIx, u8 data)
{
	while((SPIx->SR&1<<1)==0);		//�ȴ��������� 
	SPIx->DR=data;	 	  		//����һ��byte  
	while((SPIx->SR&1<<0)==0)
	{
	}		//�ȴ�������һ��byte  
 	return SPIx->DR;          		//�����յ�������
}


void SPI_close(SPI_TypeDef *SPIx)
{
	SPIx->CR1 &= ~(1 << 6);
}
