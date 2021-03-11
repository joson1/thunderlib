#include "gt9147.h"
#include "string.h" 
#include <thunder/sleep.h>
#include <stdio.h>

#define TP_PRES_DOWN 0x80  //触屏被按下	  
#define TP_CATH_PRES 0x40  //有按键按下了 

input_dev_t inputdev_gt91;

//触摸屏控制器
typedef struct
{
	uint8_t (*init)(void);			//初始化触摸屏控制器
	uint8_t (*scan)(uint8_t);				//扫描触摸屏.0,屏幕扫描;1,物理坐标;	 
	void (*adjust)(void);		//触摸屏校准 
	uint16_t x[5]; 		//当前坐标
	uint16_t y[5];		//电容屏有最多10组坐标,电阻屏则用x[0],y[0]代表:此次扫描时,触屏的坐标,用
								//x[9],y[9]存储第一次按下时的坐标. 
	uint16_t sta;					//笔的状态 
								//b15:按下1/松开0; 
	                            //b14:0,没有按键按下;1,有按键按下. 
								//b13~b10:保留
								//b9~b0:电容触摸屏按下的点数(0,表示未按下,1表示按下)
/////////////////////触摸屏校准参数(电容屏不需要校准)//////////////////////								
	float xfac;					
	float yfac;
	short xoff;
	short yoff;	   
//新增的参数,当触摸屏的左右上下完全颠倒时需要用到.
//b0:0,竖屏(适合左右为X坐标,上下为Y坐标的TP)
//   1,横屏(适合左右为Y坐标,上下为X坐标的TP) 
//b1~6:保留.
//b7:0,电阻屏
//   1,电容屏 
	uint8_t touchtype;
}_m_tp_dev;

_m_tp_dev tp_dev;	 	//触屏控制器在touch.c里面定义

//GT9147配置参数表
//第一个字节为版本号(0X60),必须保证新的版本号大于等于GT9147内部
//flash原有版本号,才会更新配置.
const uint8_t GT9147_CFG_TBL[]=
{ 
	0X60,0XE0,0X01,0X20,0X03,0X05,0X35,0X00,0X02,0X08,
	0X1E,0X08,0X50,0X3C,0X0F,0X05,0X00,0X00,0XFF,0X67,
	0X50,0X00,0X00,0X18,0X1A,0X1E,0X14,0X89,0X28,0X0A,
	0X30,0X2E,0XBB,0X0A,0X03,0X00,0X00,0X02,0X33,0X1D,
	0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X32,0X00,0X00,
	0X2A,0X1C,0X5A,0X94,0XC5,0X02,0X07,0X00,0X00,0X00,
	0XB5,0X1F,0X00,0X90,0X28,0X00,0X77,0X32,0X00,0X62,
	0X3F,0X00,0X52,0X50,0X00,0X52,0X00,0X00,0X00,0X00,
	0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
	0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X0F,
	0X0F,0X03,0X06,0X10,0X42,0XF8,0X0F,0X14,0X00,0X00,
	0X00,0X00,0X1A,0X18,0X16,0X14,0X12,0X10,0X0E,0X0C,
	0X0A,0X08,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
	0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
	0X00,0X00,0X29,0X28,0X24,0X22,0X20,0X1F,0X1E,0X1D,
	0X0E,0X0C,0X0A,0X08,0X06,0X05,0X04,0X02,0X00,0XFF,
	0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
	0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
	0XFF,0XFF,0XFF,0XFF,
};  
//发送GT9147配置参数
//mode:0,参数不保存到flash
//     1,参数保存到flash
uint8_t GT9147_Send_Cfg(uint8_t mode)
{
	uint8_t buf[2];
	uint8_t i=0;
	buf[0]=0;
	buf[1]=mode;	//是否写入到GT9147 FLASH?  即是否掉电保存
	for(i=0;i<sizeof(GT9147_CFG_TBL);i++)buf[0]+=GT9147_CFG_TBL[i];//计算校验和
    buf[0]=(~buf[0])+1;
	GT9147_WR_Reg(GT_CFGS_REG,(uint8_t*)GT9147_CFG_TBL,sizeof(GT9147_CFG_TBL));//发送寄存器配置
	GT9147_WR_Reg(GT_CHECK_REG,buf,2);//写入校验和,和配置更新标记
	return 0;
} 
//向GT9147写入一次数据
//reg:起始寄存器地址
//buf:数据缓缓存区
//len:写数据长度
//返回值:0,成功;1,失败.
uint8_t GT9147_WR_Reg(uint16_t reg,uint8_t *buf,uint8_t len)
{
	uint8_t i;
	uint8_t ret=0;
    
    uint8_t tmp[512];
    tmp[0] = reg>>8;
    tmp[1] = reg&0XFF;
    memcpy(&tmp[2],buf,len);
    gt91->i2c_wirte(GT_CMD_WR>>1,tmp,2+len);
	// CT_IIC_Start();	
 	// CT_IIC_Send_Byte(GT_CMD_WR);   	//发送写命令 	 
	// CT_IIC_Wait_Ack();
	// CT_IIC_Send_Byte(reg>>8);   	//发送高8位地址
	// CT_IIC_Wait_Ack(); 	 										  		   
	// CT_IIC_Send_Byte(reg&0XFF);   	//发送低8位地址
	// CT_IIC_Wait_Ack();  
	// for(i=0;i<len;i++)
	// {	   
    // 	CT_IIC_Send_Byte(buf[i]);  	//发数据
	// 	ret=CT_IIC_Wait_Ack();
	// 	if(ret)break;  
	// }
    // CT_IIC_Stop();					//产生一个停止条件	    
	return ret; 
}
//从GT9147读出一次数据
//reg:起始寄存器地址
//buf:数据缓缓存区
//len:读数据长度			  
void GT9147_RD_Reg(uint16_t reg,uint8_t *buf,uint8_t len)
{
    uint8_t tmp[2];
    tmp[0] = reg>>8;
    tmp[1] = reg&0XFF;

    gt91->i2c_wirte(GT_CMD_WR>>1,tmp,2);
    gt91->i2c_read(GT_CMD_WR>>1,buf,len);

	// uint8_t i; 
 	// CT_IIC_Start();	
 	// CT_IIC_Send_Byte(GT_CMD_WR);   //发送写命令 	 
	// CT_IIC_Wait_Ack();
 	// CT_IIC_Send_Byte(reg>>8);   	//发送高8位地址
	// CT_IIC_Wait_Ack(); 	 										  		   
 	// CT_IIC_Send_Byte(reg&0XFF);   	//发送低8位地址
	// CT_IIC_Wait_Ack();  
 	// CT_IIC_Start();  	 	   
	// CT_IIC_Send_Byte(GT_CMD_RD);   //发送读命令		   
	// CT_IIC_Wait_Ack();	   
	// for(i=0;i<len;i++)
	// {	   
    // 	buf[i]=CT_IIC_Read_Byte(i==(len-1)?0:1); //发数据	  
	// } 
    // CT_IIC_Stop();//产生一个停止条件    
} 
//初始化GT9147触摸屏
//返回值:0,初始化成功;1,初始化失败 
uint8_t GT9147_Init(void)
{


    gt91 = i2c_open(0);
    // gt91->set_clock(I2C_CLOCK_400K);

	uint8_t temp[5]; 
	// RCC->AHB1ENR|=1<<7;    	//使能PORTH时钟 
	// RCC->AHB1ENR|=1<<8;    	//使能PORTI时钟  
	// GPIO_Set(GPIOH,PIN7,GPIO_MODE_IN,0,0,GPIO_PUPD_PU);	//PH7设置为上拉输入
	// GPIO_Set(GPIOI,PIN8,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//PI8设置为推挽输出

    gpio_pin_mode(GT_INT,GPIO_MODE_OUTPUT);
    gpio_pin_mode(GT_RST,GPIO_MODE_OUTPUT);

	// CT_IIC_Init();      	//初始化电容屏的I2C总线  
	// GT_RST=0;				//复位
    gpio_pin_write(GT_RST,0);
    gpio_pin_write(GT_INT,0);
    usleep(20);
    gpio_pin_write(GT_INT,1);
    usleep(200);
    gpio_pin_write(GT_RST,1);
    usleep(10*1000);
    gpio_pin_mode(GT_INT,GPIO_MODE_INPUT);

	// delay_ms(10);
 	// GT_RST=1;				//释放复位		
    // gpio_pin_write(GT_RST,1);

	// delay_ms(10); 
    // usleep(10*1000);

	// GPIO_Set(GPIOH,PIN7,GPIO_MODE_IN,0,0,GPIO_PUPD_NONE);//PH7设置为浮空输入
	// usleep(100*1000);  
	GT9147_RD_Reg(GT_PID_REG,temp,4);//读取产品ID
	temp[4]=0;
	printf("CTP ID:%s\r\n",temp);	//打印ID
	if(strcmp((char*)temp,"9147")==0)//ID==9147
	{
		temp[0]=0X02;			
		GT9147_WR_Reg(GT_CTRL_REG,temp,1);//软复位GT9147
		GT9147_RD_Reg(GT_CFGS_REG,temp,1);//读取GT_CFGS_REG寄存器
		if(temp[0]<0X60)//默认版本比较低,需要更新flash配置
		{
			printf("Default Ver:%d\r\n",temp[0]);
			// if(lcddev.id==0X5510)GT9147_Send_Cfg(1);//仅4.3寸MCU屏,更新并保存配置
			GT9147_Send_Cfg(1);
		}
		usleep(10*1000);
		temp[0]=0X00;	 
		GT9147_WR_Reg(GT_CTRL_REG,temp,1);//结束复位   
		return 0;
	}else
    {
        printf("TP:ERR\r\n");
    }
    
	return 1;
}
const uint16_t GT9147_TPX_TBL[5]={GT_TP1_REG,GT_TP2_REG,GT_TP3_REG,GT_TP4_REG,GT_TP5_REG};
//扫描触摸屏(采用查询方式)
//mode:0,正常扫描.
//返回值:当前触屏状态.
//0,触屏无触摸;1,触屏有触摸
uint8_t GT9147_Scan(uint8_t mode)
{
	uint8_t buf[4];
	uint8_t i=0;
	uint8_t res=0;
	uint8_t temp;
	uint8_t tempsta;

    GT9147_RD_Reg(GT_GSTID_REG,&mode,1);	//读取触摸点的状态  
    if(mode&0X80&&((mode&0XF)<6))
    {
        temp=0;
        GT9147_WR_Reg(GT_GSTID_REG,&temp,1);//清标志 		
    }		
    if((mode&0XF)&&((mode&0XF)<6))
    {
        temp=0XFF<<(mode&0XF);		//将点的个数转换为1的位数,匹配tp_dev.sta定义 
        tempsta=tp_dev.sta;			//保存当前的tp_dev.sta值
        tp_dev.sta=(~temp)|TP_PRES_DOWN|TP_CATH_PRES; 
        tp_dev.x[4]=tp_dev.x[0];	//保存触点0的数据
        tp_dev.y[4]=tp_dev.y[0];
        for(i=0;i<5;i++)
        {
            if(tp_dev.sta&(1<<i))	//触摸有效?
            {
                GT9147_RD_Reg(GT9147_TPX_TBL[i],buf,4);	//读取XY坐标值

                if(tp_dev.touchtype&0X01)//横屏
                {
                    tp_dev.x[i]=(((uint16_t)buf[1]<<8)+buf[0]);
                    tp_dev.y[i]=(((uint16_t)buf[3]<<8)+buf[2]);
                }
                //printf("x[%d]:%d,y[%d]:%d\r\n",i,tp_dev.x[i],i,tp_dev.y[i]);
            }			
        } 
        res=1;

    }
	
	if((mode&0X8F)==0X80)//无触摸点按下
	{ 
		if(tp_dev.sta&TP_PRES_DOWN)	//之前是被按下的
		{
			tp_dev.sta&=~(1<<7);	//标记按键松开
		}else						//之前就没有被按下
		{ 
			tp_dev.x[0]=0xffff;
			tp_dev.y[0]=0xffff;
			tp_dev.sta&=0XE0;	//清除点有效标记	
		}	 
	} 	

	return res;
}



int gt91_read(char* buf)
{
    int res = GT9147_Scan(0);
    ((uint16_t*)buf)[0] = tp_dev.x[0];
    ((uint16_t*)buf)[1] = tp_dev.y[0];


}

input_handler_t handler_gt91 = 
{
	.read=&gt91_read,

};
input_dev_t inputdev_gt91 = 
{

	.event_type=INPUT_EVT_TOUCHSCREEN,
	.input_handler=&handler_gt91,
};

extern void gt91_probe();
void gt91_probe()
{
    input_dev_register(&inputdev_gt91);
    GT9147_Init();
}
























