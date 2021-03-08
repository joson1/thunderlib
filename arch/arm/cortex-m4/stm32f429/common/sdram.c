#include "stm32f429/sdram.h"
#include "stm32f429/delay.h"
#include "stm32f429/gpio.h"

 
//��SDRAM��������
//bankx:0,��BANK5�����SDRAM����ָ��
//      1,��BANK6�����SDRAM����ָ��
//cmd:ָ��(0,����ģʽ/1,ʱ������ʹ��/2,Ԥ������д洢��/3,�Զ�ˢ��/4,����ģʽ�Ĵ���/5,��ˢ��/6,����)
//refresh:��ˢ�´���(cmd=3ʱ��Ч)
//regval:ģʽ�Ĵ����Ķ���
//����ֵ:0,����;1,ʧ��.
u8 SDRAM_Send_Cmd(u8 bankx,u8 cmd,u8 refresh,u16 regval)
{
	u32 retry=0;
	u32 tempreg=0; 
	tempreg|=cmd<<0;			//����ָ��
	tempreg|=1<<(4-bankx);		//���÷���ָ�bank5����6
	tempreg|=refresh<<5;		//������ˢ�´���
	tempreg|=regval<<9;			//����ģʽ�Ĵ�����ֵ
	FMC_Bank5_6->SDCMR=tempreg;	//���üĴ���
	while((FMC_Bank5_6->SDSR&(1<<5)))//�ȴ�ָ������ 
	{
		retry++;
		if(retry>0X1FFFFF)return 1; 
	}
	return 0;	
} 

//SDRAM��ʼ��
void SDRAM_Init(void)
{ 
	u32 sdctrlreg=0,sdtimereg=0;
	u16 mregval=0;
	
	RCC->AHB3ENR|=1<<0;     	//ʹ��FMCʱ��  
	RCC->AHB1ENR|=0X1F<<2;		//ʹ��PC/PD/PE/PF/PGʱ��  
	
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
    
 	sdctrlreg|=1<<0;				//9λ�е�ַ
	sdctrlreg|=2<<2;				//13λ�е�ַ
	sdctrlreg|=1<<4;				//16λ����λ��
	sdctrlreg|=1<<6;				//4���ڲ�����(4 BANKS)
	sdctrlreg|=3<<7;				//3��CAS�ӳ�
	sdctrlreg|=0<<9;				//����д����
	sdctrlreg|=2<<10;				//SDRAMʱ��=HCLK/2=192M/2=96M=10.4ns
	sdctrlreg|=1<<12;				//ʹ��ͻ������ 
	sdctrlreg|=0<<13;				//��ͨ���ӳ�0��HCLK
 	FMC_Bank5_6->SDCR[0]=sdctrlreg;	//����FMC BANK5 SDRAM���ƼĴ���(BANK5��6���ڹ���SDRAM).

	sdtimereg|=1<<0;				//����ģʽ�Ĵ���������ʱ����ӳ�Ϊ2��ʱ������
	sdtimereg|=6<<4;				//�˳���ˢ���ӳ�Ϊ7��ʱ������
	sdtimereg|=5<<8;				//��ˢ��ʱ��Ϊ6��ʱ������
	sdtimereg|=5<<12;				//��ѭ���ӳ�Ϊ6��ʱ������
	sdtimereg|=1<<16;				//�ָ��ӳ�Ϊ2��ʱ������
	sdtimereg|=1<<20;				//��Ԥ����ӳ�Ϊ2��ʱ������
	sdtimereg|=1<<24;				//�е����ӳ�Ϊ2��ʱ������
 	FMC_Bank5_6->SDTR[0]=sdtimereg;	//����FMC BANK5 SDRAMʱ��Ĵ��� 

	SDRAM_Send_Cmd(0,1,0,0);		//ʱ������ʹ��
	delay_us(500);					//�����ӳ�200us.
	SDRAM_Send_Cmd(0,2,0,0);		//�����д洢��Ԥ���
	SDRAM_Send_Cmd(0,3,8,0);		//������ˢ�´��� 
	mregval|=3<<0;					//����ͻ������:8(������1/2/4/8)
	mregval|=0<<3;					//����ͻ������:����(����������/����)
	mregval|=3<<4;					//����CASֵ:3(������2/3)
	mregval|=0<<7;					//���ò���ģʽ:0,��׼ģʽ
	mregval|=1<<9;					//����ͻ��дģʽ:1,�������
	SDRAM_Send_Cmd(0,4,0,mregval);	//����SDRAM��ģʽ�Ĵ���
	
	//ˢ��Ƶ�ʼ�����(��SDCLKƵ�ʼ���),���㷽��:
	//COUNT=SDRAMˢ������/����-20=SDRAMˢ������(us)*SDCLKƵ��(Mhz)/����
	//����ʹ�õ�SDRAMˢ������Ϊ64ms,SDCLK=192/2=96Mhz,����Ϊ8192(2^13).
	//����,COUNT=64*1000*96/8192-20=730 
	FMC_Bank5_6->SDRTR=730<<1;		//����ˢ��Ƶ�ʼ�����
} 

//��ָ����ַ(WriteAddr+Bank5_SDRAM_ADDR)��ʼ,����д��n���ֽ�.
//pBuffer:�ֽ�ָ��
//WriteAddr:Ҫд��ĵ�ַ
//n:Ҫд����ֽ���
void FMC_SDRAM_WriteBuffer(u8 *pBuffer,u32 WriteAddr,u32 n)
{
	for(;n!=0;n--)
	{
		*(vu8*)(Bank5_SDRAM_ADDR+WriteAddr)=*pBuffer;
		WriteAddr++;
		pBuffer++;
	}
}

//��ָ����ַ((WriteAddr+Bank5_SDRAM_ADDR))��ʼ,��������n���ֽ�.
//pBuffer:�ֽ�ָ��
//ReadAddr:Ҫ��������ʼ��ַ
//n:Ҫд����ֽ���
void FMC_SDRAM_ReadBuffer(u8 *pBuffer,u32 ReadAddr,u32 n)
{
	for(;n!=0;n--)
	{
		*pBuffer++=*(vu8*)(Bank5_SDRAM_ADDR+ReadAddr);
		ReadAddr++;
	}
}


