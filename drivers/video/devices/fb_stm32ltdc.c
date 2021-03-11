#include <thunder/fb.h>
#include <stm32f429/sys.h>
#include "stm32f429/gpio.h"
#include <thunder/gpio.h>

struct fb_info fb_stm32ltdc;

/* LTDC main registers */
#define LTDC_IDR	0x00	/* IDentification */
#define LTDC_LCR	0x04	/* Layer Count */
#define LTDC_SSCR	0x08	/* Synchronization Size Configuration */
#define LTDC_BPCR	0x0C	/* Back Porch Configuration */
#define LTDC_AWCR	0x10	/* Active Width Configuration */
#define LTDC_TWCR	0x14	/* Total Width Configuration */
#define LTDC_GCR	0x18	/* Global Control */
#define LTDC_GC1R	0x1C	/* Global Configuration 1 */
#define LTDC_GC2R	0x20	/* Global Configuration 2 */
#define LTDC_SRCR	0x24	/* Shadow Reload Configuration */
#define LTDC_GACR	0x28	/* GAmma Correction */
#define LTDC_BCCR	0x2C	/* Background Color Configuration */
#define LTDC_IER	0x34	/* Interrupt Enable */
#define LTDC_ISR	0x38	/* Interrupt Status */
#define LTDC_ICR	0x3C	/* Interrupt Clear */
#define LTDC_LIPCR	0x40	/* Line Interrupt Position Conf. */
#define LTDC_CPSR	0x44	/* Current Position Status */
#define LTDC_CDSR	0x48	/* Current Display Status */

/* LTDC layer 1 registers */
#define LTDC_L1LC1R	0x80	/* L1 Layer Configuration 1 */
#define LTDC_L1LC2R	0x84	/* L1 Layer Configuration 2 */
#define LTDC_L1CR	0x84	/* L1 Control */
#define LTDC_L1WHPCR	0x88	/* L1 Window Hor Position Config */
#define LTDC_L1WVPCR	0x8C	/* L1 Window Vert Position Config */
#define LTDC_L1CKCR	0x90	/* L1 Color Keying Configuration */
#define LTDC_L1PFCR	0x94	/* L1 Pixel Format Configuration */
#define LTDC_L1CACR	0x98	/* L1 Constant Alpha Config */
#define LTDC_L1DCCR	0x9C	/* L1 Default Color Configuration */
#define LTDC_L1BFCR	0xA0	/* L1 Blend Factors Configuration */
#define LTDC_L1FBBCR	0xA4	/* L1 FrameBuffer Bus Control */
#define LTDC_L1AFBCR	0xA8	/* L1 AuxFB Control */
#define LTDC_L1CFBAR	0xAC	/* L1 Color FrameBuffer Address */
#define LTDC_L1CFBLR	0xB0	/* L1 Color FrameBuffer Length */
#define LTDC_L1CFBLNR	0xB4	/* L1 Color FrameBuffer Line Nb */
#define LTDC_L1AFBAR	0xB8	/* L1 AuxFB Address */
#define LTDC_L1AFBLR	0xBC	/* L1 AuxFB Length */
#define LTDC_L1AFBLNR	0xC0	/* L1 AuxFB Line Number */
#define LTDC_L1CLUTWR	0xC4	/* L1 CLUT Write */

/* Bit definitions */
#define SSCR_VSH	GENMASK(10, 0)	/* Vertical Synchronization Height */
#define SSCR_HSW	GENMASK(27, 16)	/* Horizontal Synchronization Width */

#define BPCR_AVBP	GENMASK(10, 0)	/* Accumulated Vertical Back Porch */
#define BPCR_AHBP	GENMASK(27, 16)	/* Accumulated Horizontal Back Porch */

#define AWCR_AAH	GENMASK(10, 0)	/* Accumulated Active Height */
#define AWCR_AAW	GENMASK(27, 16)	/* Accumulated Active Width */

#define TWCR_TOTALH	GENMASK(10, 0)	/* TOTAL Height */
#define TWCR_TOTALW	GENMASK(27, 16)	/* TOTAL Width */

#define GCR_LTDCEN	BIT(0)		/* LTDC ENable */
#define GCR_DEN		BIT(16)		/* Dither ENable */
#define GCR_PCPOL	BIT(28)		/* Pixel Clock POLarity-Inverted */
#define GCR_DEPOL	BIT(29)		/* Data Enable POLarity-High */
#define GCR_VSPOL	BIT(30)		/* Vertical Synchro POLarity-High */
#define GCR_HSPOL	BIT(31)		/* Horizontal Synchro POLarity-High */

#define GC1R_WBCH	GENMASK(3, 0)	/* Width of Blue CHannel output */
#define GC1R_WGCH	GENMASK(7, 4)	/* Width of Green Channel output */
#define GC1R_WRCH	GENMASK(11, 8)	/* Width of Red Channel output */
#define GC1R_PBEN	BIT(12)		/* Precise Blending ENable */
#define GC1R_DT		GENMASK(15, 14)	/* Dithering Technique */
#define GC1R_GCT	GENMASK(19, 17)	/* Gamma Correction Technique */
#define GC1R_SHREN	BIT(21)		/* SHadow Registers ENabled */
#define GC1R_BCP	BIT(22)		/* Background Colour Programmable */
#define GC1R_BBEN	BIT(23)		/* Background Blending ENabled */
#define GC1R_LNIP	BIT(24)		/* Line Number IRQ Position */
#define GC1R_TP		BIT(25)		/* Timing Programmable */
#define GC1R_IPP	BIT(26)		/* IRQ Polarity Programmable */
#define GC1R_SPP	BIT(27)		/* Sync Polarity Programmable */
#define GC1R_DWP	BIT(28)		/* Dither Width Programmable */
#define GC1R_STREN	BIT(29)		/* STatus Registers ENabled */
#define GC1R_BMEN	BIT(31)		/* Blind Mode ENabled */

#define GC2R_EDCA	BIT(0)		/* External Display Control Ability  */
#define GC2R_STSAEN	BIT(1)		/* Slave Timing Sync Ability ENabled */
#define GC2R_DVAEN	BIT(2)		/* Dual-View Ability ENabled */
#define GC2R_DPAEN	BIT(3)		/* Dual-Port Ability ENabled */
#define GC2R_BW		GENMASK(6, 4)	/* Bus Width (log2 of nb of bytes) */
#define GC2R_EDCEN	BIT(7)		/* External Display Control ENabled */

#define SRCR_IMR	BIT(0)		/* IMmediate Reload */
#define SRCR_VBR	BIT(1)		/* Vertical Blanking Reload */

#define LXCR_LEN	BIT(0)		/* Layer ENable */
#define LXCR_COLKEN	BIT(1)		/* Color Keying Enable */
#define LXCR_CLUTEN	BIT(4)		/* Color Look-Up Table ENable */

#define LXWHPCR_WHSTPOS	GENMASK(11, 0)	/* Window Horizontal StarT POSition */
#define LXWHPCR_WHSPPOS	GENMASK(27, 16)	/* Window Horizontal StoP POSition */

#define LXWVPCR_WVSTPOS	GENMASK(10, 0)	/* Window Vertical StarT POSition */
#define LXWVPCR_WVSPPOS	GENMASK(26, 16)	/* Window Vertical StoP POSition */

#define LXPFCR_PF	GENMASK(2, 0)	/* Pixel Format */

#define LXCACR_CONSTA	GENMASK(7, 0)	/* CONSTant Alpha */

#define LXBFCR_BF2	GENMASK(2, 0)	/* Blending Factor 2 */
#define LXBFCR_BF1	GENMASK(10, 8)	/* Blending Factor 1 */

#define LXCFBLR_CFBLL	GENMASK(12, 0)	/* Color Frame Buffer Line Length */
#define LXCFBLR_CFBP	GENMASK(28, 16)	/* Color Frame Buffer Pitch in bytes */

#define LXCFBLNR_CFBLN	GENMASK(10, 0)	/* Color Frame Buffer Line Number */

#define BF1_PAXCA	0x600		/* Pixel Alpha x Constant Alpha */
#define BF1_CA		0x400		/* Constant Alpha */
#define BF2_1PAXCA	0x007		/* 1 - (Pixel Alpha x Constant Alpha) */
#define BF2_1CA		0x005		/* 1 - Constant Alpha */

#define LCD_FRAME_BUF_ADDR			0XC0000000  	

#define ltdc_lcd_framebuf ((uint32_t *)LCD_FRAME_BUF_ADDR)


struct stm32_ltdc_priv {
	void  *regs;
	uint32_t l2bpp;
	uint32_t bg_col_argb;
	uint32_t crop_x, crop_y, crop_w, crop_h;
	uint32_t alpha;
};







//LTDC开关
//sw:1,打开;0,关闭
void LTDC_Switch(uint8_t sw)
{
	if (sw == 1)
		LTDC->GCR |= 1 << 0; //打开LTDC
	else if (sw == 0)
		LTDC->GCR &= ~(1 << 0); //关闭LTDC
}

//开关指定层
//layerx:层号;0,第一层;1,第二层;
//sw:1,打开;0,关闭
void LTDC_Layer_Switch(uint8_t layerx, uint8_t sw)
{
	if (sw == 1)
	{
		if (layerx == 0)
			LTDC_Layer1->CR |= 1 << 0; //开启层1
		else
			LTDC_Layer2->CR |= 1 << 0; //开启层2
	}
	else if (sw == 0)
	{
		if (layerx == 0)
			LTDC_Layer1->CR &= ~(1 << 0); //关闭层1
		else
			LTDC_Layer2->CR &= ~(1 << 0); //关闭层2
	}
	LTDC->SRCR |= 1 << 0; //重新加载配置
}


//LTDC时钟(Fdclk)设置函数
//Fvco=Fin*pllsain;
//Fdclk=Fvco/pllsair/2*2^pllsaidivr=Fin*pllsain/pllsair/2*2^pllsaidivr;

//Fvco:VCO频率
//Fin:输入时钟频率一般为1Mhz(来自系统时钟PLLM分频后的时钟,见时钟树图)
//pllsain:SAI时钟倍频系数N,取值范围:50~432.
//pllsair:SAI时钟的分频系数R,取值范围:2~7
//pllsaidivr:LCD时钟分频系数,取值范围:0~3,对应分频2^(pllsaidivr+1)
//假设:外部晶振为25M,pllm=25的时候,Fin=1Mhz.
//例如:要得到20M的LTDC时钟,则可以设置:pllsain=400,pllsair=5,pllsaidivr=1
//Fdclk=1*396/3/2*2^1=396/12=33Mhz
//返回值:0,成功;1,失败。
u8 LTDC_Clk_Set(u32 pllsain, u32 pllsair, u32 pllsaidivr)
{
	u16 retry = 0;
	u8 status = 0;
	u32 tempreg = 0;
	RCC->CR &= ~(1 << 28); //关闭SAI时钟
	while (((RCC->CR & (1 << 29))) && (retry < 0X1FFF))
		retry++; //等待SAI时钟失锁
	if (retry == 0X1FFF)
		status = 1; //LTDC时钟关闭失败
	else
	{
		tempreg |= pllsain << 6;
		tempreg |= pllsair << 28;
		RCC->PLLSAICFGR = tempreg;		  //设置LTDC的倍频和分频
		RCC->DCKCFGR &= ~(3 << 16);		  //清除原来的设置.
		RCC->DCKCFGR |= pllsaidivr << 16; //设置fdclk分频

		RCC->CR |= 1 << 28; //开启SAI时钟
		while (((RCC->CR & (1 << 29)) == 0) && (retry < 0X1FFF))
			retry++; //等待SAI时钟锁定
		if (retry == 0X1FFF)
			status = 2;
	}
	return status;
}



//LTDC,层窗口设置,窗口以LCD面板坐标系为基准
//注意:此函数必须在LTDC_Layer_Parameter_Config之后再设置.另外,当设置的窗口值不等于面板的尺
//寸时,GRAM的操作(读/写点函数),也要根据窗口的宽高来进行修改,否则显示不正常(本例程就未做修改).
//layerx:层值,0/1.
//sx,sy:起始坐标
//width,height:宽度和高度
void LTDC_Layer_Window_Config(u8 layerx, u16 sx, u16 sy, u16 width, u16 height)
{
	u32 temp;
	u8 pixformat = 0;
	if (layerx == 0)
	{
		temp = (sx + width + ((LTDC->BPCR & 0X0FFF0000) >> 16)) << 16;
		LTDC_Layer1->WHPCR = (sx + ((LTDC->BPCR & 0X0FFF0000) >> 16) + 1) | temp; //设置行起始和结束位置
		temp = (sy + height + (LTDC->BPCR & 0X7FF)) << 16;
		LTDC_Layer1->WVPCR = (sy + (LTDC->BPCR & 0X7FF) + 1) | temp; //设置列起始和结束位置
		pixformat = LTDC_Layer1->PFCR & 0X07;						 //得到颜色格式
		if (pixformat == 0)
			temp = 4; //ARGB8888,一个点4个字节
		else if (pixformat == 1)
			temp = 3; //RGB888,一个点3个字节
		else if (pixformat == 5 || pixformat == 6)
			temp = 1; //L8/AL44,一个点1个字节
		else
			temp = 2;													//其他格式,一个点2个字节
		LTDC_Layer1->CFBLR = (width * temp << 16) | (width * temp + 3); //帧缓冲区长度设置(字节为单位)
		LTDC_Layer1->CFBLNR = height;									//帧缓冲区行数设置
	}
	else
	{
		temp = (sx + width + ((LTDC->BPCR & 0X0FFF0000) >> 16)) << 16;
		LTDC_Layer2->WHPCR = (sx + ((LTDC->BPCR & 0X0FFF0000) >> 16) + 1) | temp; //设置行起始和结束位置
		temp = (sy + height + (LTDC->BPCR & 0X7FF)) << 16;
		LTDC_Layer2->WVPCR = (sy + (LTDC->BPCR & 0X7FF) + 1) | temp; //设置列起始和结束位置
		pixformat = LTDC_Layer2->PFCR & 0X07;						 //得到颜色格式
		if (pixformat == 0)
			temp = 4; //ARGB8888,一个点4个字节
		else if (pixformat == 1)
			temp = 3; //RGB888,一个点3个字节
		else if (pixformat == 5 || pixformat == 6)
			temp = 1; //L8/AL44,一个点1个字节
		else
			temp = 2;													//其他格式,一个点2个字节
		LTDC_Layer2->CFBLR = (width * temp << 16) | (width * temp + 3); //帧缓冲区长度设置(字节为单位)
		LTDC_Layer2->CFBLNR = height;									//帧缓冲区行数设置
	}
	LTDC_Layer_Switch(layerx, 1); //层使能
}
//LTDC填充矩形,DMA2D填充
//(sx,sy),(ex,ey):填充矩形对角坐标,区域大小为:(ex-sx+1)*(ey-sy+1)
//注意:sx,ex,不能大于lcddev.width-1;sy,ey,不能大于lcddev.height-1!!!
//color:要填充的颜色
void LTDC_Fill(u16 sx, u16 sy, u16 ex, u16 ey, u32 color)
{
	u32 psx, psy, pex, pey; //以LCD面板为基准的坐标系,不随横竖屏变化而变化
	u32 timeout = 0;
	u16 offline;
	u32 addr;

	psx = sx;
	psy = sy;
	pex = ex;
	pey = ey;

	offline = fb_stm32ltdc.var.xres - (pex - psx + 1);
	addr = ((u32)fb_stm32ltdc.screen_base + (fb_stm32ltdc.var.bits_per_pixel/8) * (fb_stm32ltdc.var.xres * psy + psx));
	RCC->AHB1ENR |= 1 << 23;								//使能DM2D时钟
	DMA2D->CR &= ~(1 << 0);									//先停止DMA2D
	DMA2D->CR = 3 << 16;									//寄存器到存储器模式
	DMA2D->OPFCCR = PF_RGB565;							//设置颜色格式
	DMA2D->OOR = offline;									//设置行偏移
	DMA2D->OMAR = addr;										//输出存储器地址
	DMA2D->NLR = (pey - psy + 1) | ((pex - psx + 1) << 16); //设定行数寄存器
	DMA2D->OCOLR = color;									//设定输出颜色寄存器
	DMA2D->CR |= 1 << 0;									//启动DMA2D
	while ((DMA2D->ISR & (1 << 1)) == 0)					//等待传输完成
	{
		timeout++;
		if (timeout > 0X1FFFFF)
			break; //超时退出
	}
	DMA2D->IFCR |= 1 << 1; //清除传输完成标志
}




//LCD清屏
//color:颜色值
void LTDC_Clear(u32 color)
{
	LTDC_Fill(0, 0, fb_stm32ltdc.var.xres - 1, fb_stm32ltdc.var.yres - 1, color);
}
//LTDC,基本参数设置.
//注意:此函数,必须在LTDC_Layer_Window_Config之前设置.
//layerx:层值,0/1.
//bufaddr:层颜色帧缓存起始地址
//pixformat:颜色格式.0,ARGB8888;1,RGB888;2,RGB565;3,ARGB1555;4,ARGB4444;5,L8;6;AL44;7;AL88
//alpha:层颜色Alpha值,0,全透明;255,不透明
//alpha0:默认颜色Alpha值,0,全透明;255,不透明
//bfac1:混合系数1,4(100),恒定的Alpha;6(101),像素Alpha*恒定Alpha
//bfac2:混合系数2,5(101),恒定的Alpha;7(111),像素Alpha*恒定Alpha
//bkcolor:层默认颜色,32位,低24位有效,RGB888格式
//返回值:无
void LTDC_Layer_Parameter_Config(u8 layerx, u32 bufaddr, u8 pixformat, u8 alpha, u8 alpha0, u8 bfac1, u8 bfac2, u32 bkcolor)
{
	if (layerx == 0)
	{
		LTDC_Layer1->CFBAR = bufaddr;					   //设置层颜色帧缓存起始地址
		LTDC_Layer1->PFCR = pixformat;					   //设置层颜色格式
		LTDC_Layer1->CACR = alpha;						   //设置层颜色Alpha值,255分频;设置255,则不透明
		LTDC_Layer1->DCCR = ((u32)alpha0 << 24) | bkcolor; //设置默认颜色Alpha值,以及默认颜色
		LTDC_Layer1->BFCR = ((u32)bfac1 << 8) | bfac2;	 //设置层混合系数
	}
	else
	{
		LTDC_Layer2->CFBAR = bufaddr;					   //设置层颜色帧缓存起始地址
		LTDC_Layer2->PFCR = pixformat;					   //设置层颜色格式
		LTDC_Layer2->CACR = alpha;						   //设置层颜色Alpha值,255分频;设置255,则不透明
		LTDC_Layer2->DCCR = ((u32)alpha0 << 24) | bkcolor; //设置默认颜色Alpha值,以及默认颜色
		LTDC_Layer2->BFCR = ((u32)bfac1 << 8) | bfac2;	 //设置层混合系数
	}
}
#define LTDC_BACKLAYERCOLOR			0X00000000	

static int stm32_ltdc_init()
{

	struct stm32_ltdc_priv *priv = fb_stm32ltdc.par; 
	u32 tempreg = 0;
	u16 lcdid = 0;

														  //读取LCD面板ID
	RCC->APB2ENR |= 1 << 26;																				  //开启LTDC时钟
	RCC->AHB1ENR |= 1 << 1;																					  //使能PORTB时钟
	RCC->AHB1ENR |= 0XF << 5;																				  //使能PF/PG/PH/PI时钟
	GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_OUT, GPIO_OTYPE_PP, GPIO_SPEED_50M, GPIO_PUPD_PU);				  //PB5 推挽输出,控制背光
	GPIO_Init(GPIOF, GPIO_PIN_10, GPIO_MODE_AF, GPIO_OTYPE_PP, GPIO_SPEED_100M, GPIO_PUPD_PU);				  //PF10
	GPIO_Init(GPIOG, 3 << 6 | 1 << 11, GPIO_MODE_AF, GPIO_OTYPE_PP, GPIO_SPEED_100M, GPIO_PUPD_PU);			  //PG6/7/11
	GPIO_Init(GPIOH, 0X7F << 9, GPIO_MODE_AF, GPIO_OTYPE_PP, GPIO_SPEED_100M, GPIO_PUPD_PU);				  //PH9~15
	GPIO_Init(GPIOI, 7 << 0 | 0XF << 4 | 3 << 9, GPIO_MODE_AF, GPIO_OTYPE_PP, GPIO_SPEED_100M, GPIO_PUPD_PU); //PI0~2/4~7/9/10

	GPIO_AF_Set(GPIOF, GPIO_PIN_10, 14); //PF10,AF14

	GPIO_AF_Set(GPIOG, GPIO_PIN_6, 14);  //PG6,AF14
	GPIO_AF_Set(GPIOG, GPIO_PIN_7, 14);  //PG7,AF14
	GPIO_AF_Set(GPIOG, GPIO_PIN_11, 14); //PG11,AF14

	GPIO_AF_Set(GPIOH, GPIO_PIN_9, 14);  //PH9,AF14
	GPIO_AF_Set(GPIOH, GPIO_PIN_10, 14); //PH10,AF14
	GPIO_AF_Set(GPIOH, GPIO_PIN_11, 14); //PH11,AF14
	GPIO_AF_Set(GPIOH, GPIO_PIN_12, 14); //PH12,AF14
	GPIO_AF_Set(GPIOH, GPIO_PIN_13, 14); //PH13,AF14
	GPIO_AF_Set(GPIOH, GPIO_PIN_14, 14); //PH14,AF14
	GPIO_AF_Set(GPIOH, GPIO_PIN_15, 14); //PH15,AF14

	GPIO_AF_Set(GPIOI, GPIO_PIN_0, 14);  //PI0,AF14
	GPIO_AF_Set(GPIOI, GPIO_PIN_1, 14);  //PI1,AF14
	GPIO_AF_Set(GPIOI, GPIO_PIN_2, 14);  //PI2,AF14
	GPIO_AF_Set(GPIOI, GPIO_PIN_4, 14);  //PI4,AF14
	GPIO_AF_Set(GPIOI, GPIO_PIN_5, 14);  //PI5,AF14
	GPIO_AF_Set(GPIOI, GPIO_PIN_6, 14);  //PI6,AF14
	GPIO_AF_Set(GPIOI, GPIO_PIN_7, 14);  //PI7,AF14
	GPIO_AF_Set(GPIOI, GPIO_PIN_9, 14);  //PI9,AF14
	GPIO_AF_Set(GPIOI, GPIO_PIN_10, 14); //PI10,AF14

	LTDC_Clk_Set(288, 4, 2); //设置像素时钟  9Mhz

	tempreg = 0 << 28; //像素时钟极性:不反向
	tempreg |= 0 << 29;					//数据使能极性:低电平有效
	tempreg |= 0 << 30;					//垂直同步极性:低电平有效
	tempreg |= 0 << 31;					//水平同步极性:低电平有效
	LTDC->GCR = tempreg;				//设置全局控制寄存器

	tempreg = (fb_stm32ltdc.var.vsync_len-1)<<0;
	tempreg |= (fb_stm32ltdc.var.hsync_len-1)<<16;
	LTDC->SSCR = tempreg;				//设置同步大小配置寄存器

	tempreg = (fb_stm32ltdc.var.vsync_len+fb_stm32ltdc.var.upper_margin-1)<<0;
	tempreg |= (fb_stm32ltdc.var.hsync_len+fb_stm32ltdc.var.left_margin-1)<<16;
	LTDC->BPCR = tempreg;							  //设置后沿配置寄存器

	tempreg = (fb_stm32ltdc.var.vsync_len + fb_stm32ltdc.var.upper_margin + fb_stm32ltdc.var.yres -1)<<0;
	tempreg |= (fb_stm32ltdc.var.hsync_len + fb_stm32ltdc.var.left_margin + fb_stm32ltdc.var.xres -1)<<16;
	LTDC->AWCR = tempreg;							  //

	tempreg = (fb_stm32ltdc.var.vsync_len + fb_stm32ltdc.var.upper_margin + fb_stm32ltdc.var.yres + fb_stm32ltdc.var.lower_margin -1)<<0;
	tempreg |= (fb_stm32ltdc.var.hsync_len + fb_stm32ltdc.var.left_margin + fb_stm32ltdc.var.xres + fb_stm32ltdc.var.right_margin -1)<<16;
	LTDC->TWCR = tempreg;	
							  //
	LTDC->BCCR = LTDC_BACKLAYERCOLOR; //设置背景层颜色寄存器(RGB888格式)
	LTDC_Switch(1);					  //开启LTDC

	RCC->AHB1ENR |= 1 << 23;								//使能DM2D时钟

	fb_stm32ltdc.screen_buffer = ltdc_lcd_framebuf;
	LTDC_Layer_Parameter_Config(0, (uint32_t)fb_stm32ltdc.screen_buffer, PF_RGB565, 255, 0, 6, 7, 0X000000); //层参数配置
	LTDC_Layer_Window_Config(0, 0, 0, fb_stm32ltdc.var.xres, fb_stm32ltdc.var.yres);							  //层窗口配置,以LCD面板坐标系为基准,不要随便修改!
	LTDC_Clear(0);


}



void ltdc_fb_imageblit(struct fb_info *info, const struct fb_image *image)
{

	u32 timeout = 0;
	u16 offline;
	u32 addr;
	uint32_t pixSize = info->var.bits_per_pixel/8;

	static i = 0;

	if(i==0)
	{
		DMA2D->IFCR |= 1 << 1; //清除传输完成标志

		offline = fb_stm32ltdc.var.xres-image->width; //lcdltdc.pwidth - (pex - psx + 1);
		addr = (info->screen_base + ( (info->var.xres)*(image->dy) )*pixSize );
		//((u32)ltdc_framebuf[lcdltdc.activelayer] + lcdltdc.pixsize * (lcdltdc.pwidth * psy + psx));
		RCC->AHB1ENR |= 1 << 23;								//使能DM2D时钟
		DMA2D->CR &= ~(1 << 0);									//先停止DMA2D
		DMA2D->CR = 0 << 16;									//存储器到存储器模式
		DMA2D->FGPFCCR = PF_RGB565;							//设置颜色格式
		DMA2D->FGOR = 0;										//前景层行偏移为0
		DMA2D->OOR = offline;									//设置行偏移
		DMA2D->FGMAR = (u32)image->data;								//源地址
		DMA2D->OMAR = addr;										//输出存储器地址
		DMA2D->NLR = (image->height) | ((image->width) << 16); //设定行数寄存器
		DMA2D->CR |= 1 << 0;									//启动DMA2D

		i=1;
	}else
	{
		while ((DMA2D->ISR & (1 << 1)) == 0) //等待传输完成
		{
			timeout++;
			if (timeout > 0X1FFFFF)
				break;
		}
		DMA2D->IFCR |= 1 << 1; //清除传输完成标志

		offline = fb_stm32ltdc.var.xres-image->width; //lcdltdc.pwidth - (pex - psx + 1);
		addr = (info->screen_base + ( (info->var.xres)*(image->dy) )*pixSize );
		//((u32)ltdc_framebuf[lcdltdc.activelayer] + lcdltdc.pixsize * (lcdltdc.pwidth * psy + psx));
		RCC->AHB1ENR |= 1 << 23;								//使能DM2D时钟
		DMA2D->CR &= ~(1 << 0);									//先停止DMA2D
		DMA2D->CR = 0 << 16;									//存储器到存储器模式
		DMA2D->FGPFCCR = PF_RGB565;							//设置颜色格式
		DMA2D->FGOR = 0;										//前景层行偏移为0
		DMA2D->OOR = offline;									//设置行偏移
		DMA2D->FGMAR = (u32)image->data;								//源地址
		DMA2D->OMAR = addr;										//输出存储器地址
		DMA2D->NLR = (image->height) | ((image->width) << 16); //设定行数寄存器
		DMA2D->CR |= 1 << 0;									//启动DMA2D

	}
	


}

void ltdc_fb_fillrect(struct fb_info *info, const struct fb_fillrect *rect)
{
	u32 timeout = 0;
	u16 offline;
	u32 addr;
	uint32_t pixSize = info->var.bits_per_pixel/8;

	DMA2D->IFCR |= 1 << 1; //清除传输完成标志

	
	offline = info->var.xres-(rect->width);  //lcdltdc.pwidth - (pex - psx + 1);
	addr =  (info->screen_base + ( (info->var.xres)*(rect->dy) )*pixSize );//+ lcdltdc.pixsize * (lcdltdc.pwidth * psy + psx));
	RCC->AHB1ENR |= 1 << 23;								//使能DM2D时钟
	DMA2D->CR &= ~(1 << 0);									//先停止DMA2D
	DMA2D->CR = 3 << 16;									//存储器到存储器模式
	DMA2D->FGPFCCR = PF_RGB565;							//设置颜色格式
	DMA2D->FGOR = 0;										//前景层行偏移为0
	DMA2D->OOR = offline;									//设置行偏移
	DMA2D->OMAR = addr;										//输出存储器地址
	DMA2D->NLR = (rect->height) | ((rect->width) << 16); //设定行数寄存器
	DMA2D->OCOLR = rect->color;									//设定输出颜色寄存器

	DMA2D->CR |= 1 << 0;									//启动DMA2D



}

struct fb_ops ltdc_ops = {
	.fb_fillrect = &ltdc_fb_fillrect,
	.fb_imageblit=&ltdc_fb_imageblit,
};


struct fb_ops ops_ltdc;
struct fb_info fb_stm32ltdc = 
{
	.id = 0,
	.var = {
			.bits_per_pixel = 16,
			.grayscale = 0,
			.pix_fmt = PF_RGB565,
			.height = 150, 
			.width =350,
			.xres = 480,
			.yres = 272,
			.pixclock=9*10^6, //9MHz
			.left_margin=40,
			.right_margin=5,
			.upper_margin=8,
			.lower_margin=8,
			.hsync_len=1,
			.vsync_len=1,

	},
	.fbops = &ltdc_ops,
};


extern int fb_stm32ltdc_init();
int fb_stm32ltdc_init()
{
	// fb_stm32ltdc.screen_buffer = ltdc_lcd_framebuf;
	gpio_pin_mode(163,GPIO_MODE_OUTPUT);
	gpio_pin_set(163);

    fb_dev_attach(&fb_stm32ltdc,0);
	stm32_ltdc_init();
	
}

