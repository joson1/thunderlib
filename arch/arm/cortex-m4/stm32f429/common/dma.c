#include "stm32f429/dma.h"
#include "stddef.h"


// void (*DMA2_Stream0_IRQEvent)() = NULL;
// void (*DMA2_Stream1_IRQEvent)() = NULL;
// void (*DMA2_Stream2_IRQEvent)() = NULL;
// void (*DMA2_Stream3_IRQEvent)() = NULL;
// void (*DMA2_Stream4_IRQEvent)() = NULL;
// void (*DMA1_Stream0_IRQEvent)() = NULL;
// void (*DMA1_Stream1_IRQEvent)() = NULL;
// void (*DMA1_Stream2_IRQEvent)() = NULL;
// void (*DMA1_Stream3_IRQEvent)() = NULL;
// void (*DMA1_Stream4_IRQEvent)() = NULL;
// void (*DMA1_Stream5_IRQEvent)() = NULL;
// void (*DMA1_Stream6_IRQEvent)() = NULL;
//DMAx�ĸ�ͨ������
//����Ĵ�����ʽ�ǹ̶���,���Ҫ���ݲ�ͬ��������޸�
//�Ӵ洢��->����ģʽ/8λ���ݿ��/�洢������ģʽ
//DMA_Streamx:DMA������,DMA1_Stream0~7/DMA2_Stream0~7
//chx:DMAͨ��ѡ��,��Χ:0~7
//par:�����ַ
//mar:�洢����ַ
//ndtr:���ݴ�����
void DMA_Config(DMA_InitDef* DMA_str)
{
	DMA_TypeDef *DMAx;
	u8 streamx;

	if ((u32)(DMA_str->DMA_Streamx) > (u32)DMA2) //�õ���ǰstream������DMA2����DMA1
	{
		DMAx = DMA2;
		RCC->AHB1ENR |= 1 << 22; //DMA2ʱ��ʹ��
	}
	else
	{
		DMAx = DMA1;
		RCC->AHB1ENR |= 1 << 21; //DMA1ʱ��ʹ��
	}
	while (DMA_str->DMA_Streamx->CR & 0X01)
    {
        DMA_str->DMA_Streamx->CR &= (~0X01);
    
    }
																		 //�ȴ�DMA������
	streamx = (((u32)(DMA_str->DMA_Streamx) - (u32)DMAx) - 0X10) / 0X18; //�õ�streamͨ����
	if (streamx >= 6)
		DMAx->HIFCR |= 0X3D << (6 * (streamx - 6) + 16); //���֮ǰ��stream�ϵ������жϱ�־
	else if (streamx >= 4)
		DMAx->HIFCR |= 0X3D << 6 * (streamx - 4); //���֮ǰ��stream�ϵ������жϱ�־
	else if (streamx >= 2)
		DMAx->LIFCR |= 0X3D << (6 * (streamx - 2) + 16); //���֮ǰ��stream�ϵ������жϱ�־
	else
		DMAx->LIFCR |= 0X3D << 6 * streamx; //���֮ǰ��stream�ϵ������жϱ�־

	DMA_str->DMA_Streamx->PAR = DMA_str->PeriphAddr;			  //DMA�����ַ
	DMA_str->DMA_Streamx->M0AR = DMA_str->Memory0Addr;			  //DMA �洢��0��ַ
	DMA_str->DMA_Streamx->M1AR = DMA_str->Memory1Addr;			  //DMA �洢��1��ַ
	DMA_str->DMA_Streamx->NDTR = DMA_str->NumberOfData;			  					//������
	DMA_str->DMA_Streamx->CR = 0;								  //��ȫ����λCR�Ĵ���ֵ
	DMA_str->DMA_Streamx->CR |= (DMA_str->Direction) << 6;		  //�洢��������ģʽ
	DMA_str->DMA_Streamx->CR |= (DMA_str->Mode) << 8;			  //��ѭ��ģʽ(��ʹ����ͨģʽ)
	DMA_str->DMA_Streamx->CR |= (DMA_str->bPeriphInc) << 9;		  //���������ģʽ
	DMA_str->DMA_Streamx->CR |= (DMA_str->bMemInc) << 10;		  //�洢������ģʽ
	DMA_str->DMA_Streamx->CR |= (DMA_str->PeriphDataWidth) << 11; //�������ݳ���:8λ
	DMA_str->DMA_Streamx->CR |= (DMA_str->MemDataWidth) << 13;	//�洢�����ݳ���:8λ
	DMA_str->DMA_Streamx->CR |= (DMA_str->Priority) << 16;		  //�е����ȼ�
	DMA_str->DMA_Streamx->CR |= (DMA_str->PeriphBurst) << 21;	 //����ͻ�����δ���
	DMA_str->DMA_Streamx->CR |= (DMA_str->MemBurst) << 23;		  //�洢��ͻ�����δ���
	DMA_str->DMA_Streamx->CR |= (DMA_str->Channel) << 25;		  //ͨ��ѡ��
	DMA_str->DMA_Streamx->CR |= (DMA_str->Interrupt) << 1;
	if(DMA_str->Memory1Addr)
	{
		DMA_str->DMA_Streamx->CR |= 1<<18;				//˫����ģʽ
		DMA_str->DMA_Streamx->CR |= 1<<4;				//������������ж�
		
	}

	//DMA_Streamx->FCR=0X21;	//FIFO���ƼĴ���
}

void DMA_AddressSet(DMA_InitDef* DMA_str,u32 SrcAddress,u32 DstAddress)
{
	if(DMA_str->Direction == DMA_MEMORY_TO_PERIPH)
	{
		DMA_str->DMA_Streamx->PAR = DstAddress;
		DMA_str->DMA_Streamx->M0AR = SrcAddress;

	}else
	{
		DMA_str->DMA_Streamx->PAR = SrcAddress;
		DMA_str->DMA_Streamx->M0AR = DstAddress;		
	}
	
}


//����һ��DMA����
//DMA_str:DMA��ʼ���ṹ��
//DataLength:���ݴ�����
void DMA_Start(DMA_InitDef* DMA_str)
{
	DMA_str->DMA_Streamx->CR &= ~(1 << 0); //�ر�DMA����
	while (DMA_str->DMA_Streamx->CR & 0X1)
		;					   //ȷ��DMA���Ա�����

		DMA_str->DMA_Streamx->NDTR = DMA_str->NumberOfData ;  //DMA 
		


	DMA_str->DMA_Streamx->CR |= 1 << 0; //����DMA����

}

// DMA1_Stream0_IRQHandler 
// DMA1_Stream1_IRQHandler 
// DMA1_Stream2_IRQHandler 
// DMA1_Stream3_IRQHandler 
// DMA1_Stream4_IRQHandler 
// DMA1_Stream5_IRQHandler 
// DMA1_Stream6_IRQHandler 
// DMA1_Stream7_IRQHandler

// DMA2_Stream0_IRQHandler  
// DMA2_Stream1_IRQHandler  
// DMA2_Stream2_IRQHandler  
// DMA2_Stream3_IRQHandler  
// DMA2_Stream4_IRQHandler  
// DMA2_Stream5_IRQHandler  
// DMA2_Stream6_IRQHandler  
// DMA2_Stream7_IRQHandler  