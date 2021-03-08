#include "stm32f429/sdram.h"
#include "stm32f429/delay.h"
#include "stm32f429/gpio.h"

 
//向SDRAM发送命令
//bankx:0,向BANK5上面的SDRAM发送指令
//      1,向BANK6上面的SDRAM发送指令
//cmd:指令(0,正常模式/1,时钟配置使能/2,预充电所有存储区/3,自动刷新/4,加载模式寄存器/5,自刷新/6,掉电)
//refresh:自刷新次数(cmd=3时有效)
//regval:模式寄存器的定义
//返回值:0,正常;1,失败.
u8 SDRAM_Send_Cmd(u8 bankx,u8 cmd,u8 refresh,u16 regval)
{
	u32 retry=0;
	u32 tempreg=0; 
	tempreg|=cmd<<0;			//设置指令
	tempreg|=1<<(4-bankx);		//设置发送指令到bank5还是6
	tempreg|=refresh<<5;		//设置自刷新次数
	tempreg|=regval<<9;			//设置模式寄存器的值
	FMC_Bank5_6->SDCMR=tempreg;	//配置寄存器
	while((FMC_Bank5_6->SDSR&(1<<5)))//等待指令发送完成 
	{
		retry++;
		if(retry>0X1FFFFF)return 1; 
	}
	return 0;	
} 

//SDRAM初始化
void SDRAM_Init(void)
{ 
	u32 sdctrlreg=0,sdtimereg=0;
	u16 mregval=0;
	
	RCC->AHB3ENR|=1<<0;     	//使能FMC时钟  
	RCC->AHB1ENR|=0X1F<<2;		//使能PC/PD/PE/PF/PG时钟  
	
	GPIO_Init(GPIOC,GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_3,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);			//PC0/2/3			
	GPIO_Init(GPIOD,3<<0|7<<8|3<<14,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);		//PD0/1/8/9/10/14/15		
	GPIO_Init(GPIOE,3<<0|0X1FF<<7,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);			//PE0/1/7~15				
	GPIO_Init(GPIOF,0X3F<<0|0X1F<<11,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);		//PG0~5/11~15					
	GPIO_Init(GPIOG,7<<0|3<<4|GPIO_PIN_8|GPIO_PIN_15,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);	//PF0~2/4/5/8/15				
 
 	GPIO_AF_Set(GPIOC,GPIO_PIN_0,12);	//PC0,AF12
 	GPIO_AF_Set(GPIOC,GPIO_PIN_2,12);	//PC2,AF12
 	GPIO_AF_Set(GPIOC,GPIO_PIN_3,12);	//PC3,AF12
	
 	GPIO_AF_Set(GPIOD,GPIO_PIN_0,12);	//PD0,AF12 
 	GPIO_AF_Set(GPIOD,GPIO_PIN_1,12);	//PD1,AF12 
 	GPIO_AF_Set(GPIOD,GPIO_PIN_8,12);	//PD8,AF12
 	GPIO_AF_Set(GPIOD,GPIO_PIN_9,12);	//PD9,AF12
 	GPIO_AF_Set(GPIOD,GPIO_PIN_10,12);	//PD10,AF12  
 	GPIO_AF_Set(GPIOD,GPIO_PIN_14,12);	//PD14,AF12
 	GPIO_AF_Set(GPIOD,GPIO_PIN_15,12);	//PD15,AF12
	
 	GPIO_AF_Set(GPIOE,GPIO_PIN_0,12);	//PE0,AF12 
 	GPIO_AF_Set(GPIOE,GPIO_PIN_1,12);	//PE1,AF12 
 	GPIO_AF_Set(GPIOE,GPIO_PIN_7,12);	//PE7,AF12
 	GPIO_AF_Set(GPIOE,GPIO_PIN_8,12);	//PE8,AF12
 	GPIO_AF_Set(GPIOE,GPIO_PIN_9,12);	//PE9,AF12
 	GPIO_AF_Set(GPIOE,GPIO_PIN_10,12);	//PE10,AF12
 	GPIO_AF_Set(GPIOE,GPIO_PIN_11,12);	//PE11,AF12
 	GPIO_AF_Set(GPIOE,GPIO_PIN_12,12);	//PE12,AF12
 	GPIO_AF_Set(GPIOE,GPIO_PIN_13,12);	//PE13,AF12
 	GPIO_AF_Set(GPIOE,GPIO_PIN_14,12);	//PE14,AF12
 	GPIO_AF_Set(GPIOE,GPIO_PIN_15,12);	//PE15,AF12

 	GPIO_AF_Set(GPIOF,GPIO_PIN_0,12);	//PF0,AF12 
 	GPIO_AF_Set(GPIOF,GPIO_PIN_1,12);	//PF1,AF12 
 	GPIO_AF_Set(GPIOF,GPIO_PIN_2,12);	//PF2,AF12
 	GPIO_AF_Set(GPIOF,GPIO_PIN_3,12);	//PF3,AF12
 	GPIO_AF_Set(GPIOF,GPIO_PIN_4,12);	//PF4,AF12
 	GPIO_AF_Set(GPIOF,GPIO_PIN_5,12);	//PF5,AF12
 	GPIO_AF_Set(GPIOF,GPIO_PIN_11,12);	//PF11,AF12
 	GPIO_AF_Set(GPIOF,GPIO_PIN_12,12);	//PF12,AF12
 	GPIO_AF_Set(GPIOF,GPIO_PIN_13,12);	//PF13,AF12
 	GPIO_AF_Set(GPIOF,GPIO_PIN_14,12);	//PF14,AF12
 	GPIO_AF_Set(GPIOF,GPIO_PIN_15,12);	//PF15,AF12
	
 	GPIO_AF_Set(GPIOG,GPIO_PIN_0,12);	//PG0,AF12 
 	GPIO_AF_Set(GPIOG,GPIO_PIN_1,12);	//PG1,AF12 
 	GPIO_AF_Set(GPIOG,GPIO_PIN_2,12);	//PG2,AF12
 	GPIO_AF_Set(GPIOG,GPIO_PIN_4,12);	//PG4,AF12
 	GPIO_AF_Set(GPIOG,GPIO_PIN_5,12);	//PG5,AF12  
 	GPIO_AF_Set(GPIOG,GPIO_PIN_8,12);	//PG8,AF12
 	GPIO_AF_Set(GPIOG,GPIO_PIN_15,12);	//PG15,AF12	
    
 	sdctrlreg|=1<<0;				//9位列地址
	sdctrlreg|=2<<2;				//13位行地址
	sdctrlreg|=1<<4;				//16位数据位宽
	sdctrlreg|=1<<6;				//4个内部存区(4 BANKS)
	sdctrlreg|=3<<7;				//3个CAS延迟
	sdctrlreg|=0<<9;				//允许写访问
	sdctrlreg|=2<<10;				//SDRAM时钟=HCLK/2=192M/2=96M=10.4ns
	sdctrlreg|=1<<12;				//使能突发访问 
	sdctrlreg|=0<<13;				//读通道延迟0个HCLK
 	FMC_Bank5_6->SDCR[0]=sdctrlreg;	//设置FMC BANK5 SDRAM控制寄存器(BANK5和6用于管理SDRAM).

	sdtimereg|=1<<0;				//加载模式寄存器到激活时间的延迟为2个时钟周期
	sdtimereg|=6<<4;				//退出自刷新延迟为7个时钟周期
	sdtimereg|=5<<8;				//自刷新时间为6个时钟周期
	sdtimereg|=5<<12;				//行循环延迟为6个时钟周期
	sdtimereg|=1<<16;				//恢复延迟为2个时钟周期
	sdtimereg|=1<<20;				//行预充电延迟为2个时钟周期
	sdtimereg|=1<<24;				//行到列延迟为2个时钟周期
 	FMC_Bank5_6->SDTR[0]=sdtimereg;	//设置FMC BANK5 SDRAM时序寄存器 

	SDRAM_Send_Cmd(0,1,0,0);		//时钟配置使能
	delay_us(500);					//至少延迟200us.
	SDRAM_Send_Cmd(0,2,0,0);		//对所有存储区预充电
	SDRAM_Send_Cmd(0,3,8,0);		//设置自刷新次数 
	mregval|=3<<0;					//设置突发长度:8(可以是1/2/4/8)
	mregval|=0<<3;					//设置突发类型:连续(可以是连续/交错)
	mregval|=3<<4;					//设置CAS值:3(可以是2/3)
	mregval|=0<<7;					//设置操作模式:0,标准模式
	mregval|=1<<9;					//设置突发写模式:1,单点访问
	SDRAM_Send_Cmd(0,4,0,mregval);	//设置SDRAM的模式寄存器
	
	//刷新频率计数器(以SDCLK频率计数),计算方法:
	//COUNT=SDRAM刷新周期/行数-20=SDRAM刷新周期(us)*SDCLK频率(Mhz)/行数
	//我们使用的SDRAM刷新周期为64ms,SDCLK=192/2=96Mhz,行数为8192(2^13).
	//所以,COUNT=64*1000*96/8192-20=730 
	FMC_Bank5_6->SDRTR=730<<1;		//设置刷新频率计数器
} 

//在指定地址(WriteAddr+Bank5_SDRAM_ADDR)开始,连续写入n个字节.
//pBuffer:字节指针
//WriteAddr:要写入的地址
//n:要写入的字节数
void FMC_SDRAM_WriteBuffer(u8 *pBuffer,u32 WriteAddr,u32 n)
{
	for(;n!=0;n--)
	{
		*(vu8*)(Bank5_SDRAM_ADDR+WriteAddr)=*pBuffer;
		WriteAddr++;
		pBuffer++;
	}
}

//在指定地址((WriteAddr+Bank5_SDRAM_ADDR))开始,连续读出n个字节.
//pBuffer:字节指针
//ReadAddr:要读出的起始地址
//n:要写入的字节数
void FMC_SDRAM_ReadBuffer(u8 *pBuffer,u32 ReadAddr,u32 n)
{
	for(;n!=0;n--)
	{
		*pBuffer++=*(vu8*)(Bank5_SDRAM_ADDR+ReadAddr);
		ReadAddr++;
	}
}


