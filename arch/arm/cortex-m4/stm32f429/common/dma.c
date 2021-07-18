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
//DMAx的各通道配置
//这里的传输形式是固定的,这点要根据不同的情况来修改
//从存储器->外设模式/8位数据宽度/存储器增量模式
//DMA_Streamx:DMA数据流,DMA1_Stream0~7/DMA2_Stream0~7
//chx:DMA通道选择,范围:0~7
//par:外设地址
//mar:存储器地址
//ndtr:数据传输量
void DMA_Config(DMA_InitDef* DMA_str)
{
	DMA_TypeDef *DMAx;
	u8 streamx;

	if ((u32)(DMA_str->DMA_Streamx) > (u32)DMA2) //得到当前stream是属于DMA2还是DMA1
	{
		DMAx = DMA2;
		RCC->AHB1ENR |= 1 << 22; //DMA2时钟使能
	}
	else
	{
		DMAx = DMA1;
		RCC->AHB1ENR |= 1 << 21; //DMA1时钟使能
	}
	while (DMA_str->DMA_Streamx->CR & 0X01)
    {
        DMA_str->DMA_Streamx->CR &= (~0X01);
    
    }
																		 //等待DMA可配置
	streamx = (((u32)(DMA_str->DMA_Streamx) - (u32)DMAx) - 0X10) / 0X18; //得到stream通道号
	if (streamx >= 6)
		DMAx->HIFCR |= 0X3D << (6 * (streamx - 6) + 16); //清空之前该stream上的所有中断标志
	else if (streamx >= 4)
		DMAx->HIFCR |= 0X3D << 6 * (streamx - 4); //清空之前该stream上的所有中断标志
	else if (streamx >= 2)
		DMAx->LIFCR |= 0X3D << (6 * (streamx - 2) + 16); //清空之前该stream上的所有中断标志
	else
		DMAx->LIFCR |= 0X3D << 6 * streamx; //清空之前该stream上的所有中断标志

	DMA_str->DMA_Streamx->PAR = DMA_str->PeriphAddr;			  //DMA外设地址
	DMA_str->DMA_Streamx->M0AR = DMA_str->Memory0Addr;			  //DMA 存储器0地址
	DMA_str->DMA_Streamx->M1AR = DMA_str->Memory1Addr;			  //DMA 存储器1地址
	DMA_str->DMA_Streamx->NDTR = DMA_str->NumberOfData;			  					//传输量
	DMA_str->DMA_Streamx->CR = 0;								  //先全部复位CR寄存器值
	DMA_str->DMA_Streamx->CR |= (DMA_str->Direction) << 6;		  //存储器到外设模式
	DMA_str->DMA_Streamx->CR |= (DMA_str->Mode) << 8;			  //非循环模式(即使用普通模式)
	DMA_str->DMA_Streamx->CR |= (DMA_str->bPeriphInc) << 9;		  //外设非增量模式
	DMA_str->DMA_Streamx->CR |= (DMA_str->bMemInc) << 10;		  //存储器增量模式
	DMA_str->DMA_Streamx->CR |= (DMA_str->PeriphDataWidth) << 11; //外设数据长度:8位
	DMA_str->DMA_Streamx->CR |= (DMA_str->MemDataWidth) << 13;	//存储器数据长度:8位
	DMA_str->DMA_Streamx->CR |= (DMA_str->Priority) << 16;		  //中等优先级
	DMA_str->DMA_Streamx->CR |= (DMA_str->PeriphBurst) << 21;	 //外设突发单次传输
	DMA_str->DMA_Streamx->CR |= (DMA_str->MemBurst) << 23;		  //存储器突发单次传输
	DMA_str->DMA_Streamx->CR |= (DMA_str->Channel) << 25;		  //通道选择
	DMA_str->DMA_Streamx->CR |= (DMA_str->Interrupt) << 1;
	if(DMA_str->Memory1Addr)
	{
		DMA_str->DMA_Streamx->CR |= 1<<18;				//双缓冲模式
		DMA_str->DMA_Streamx->CR |= 1<<4;				//开启传输完成中断
		
	}

	//DMA_Streamx->FCR=0X21;	//FIFO控制寄存器
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


//开启一次DMA传输
//DMA_str:DMA初始化结构体
//DataLength:数据传输量
void DMA_Start(DMA_InitDef* DMA_str)
{
	DMA_str->DMA_Streamx->CR &= ~(1 << 0); //关闭DMA传输
	while (DMA_str->DMA_Streamx->CR & 0X1)
		;					   //确保DMA可以被设置

		DMA_str->DMA_Streamx->NDTR = DMA_str->NumberOfData ;  //DMA 
		


	DMA_str->DMA_Streamx->CR |= 1 << 0; //开启DMA传输

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