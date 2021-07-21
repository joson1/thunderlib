#include "ssd1306.h"
#include "oled.h"
#include "oledfonts.h"
#include <stdarg.h>
#include "math.h"

Curser  OLEDcurser={0,0};

void OLED_init()
{

    SSD1306_init();
#if OLED_TYPE == OLED_096
    SSD1306_writeConnand(0xAE);//--display off
	SSD1306_writeConnand(0x00);//---set low column address
	SSD1306_writeConnand(0x10);//---set high column address
	SSD1306_writeConnand(0x40);//--set start line address  
	SSD1306_writeConnand(0xB0);//--set page address
	SSD1306_writeConnand(0x81); // contract control
	SSD1306_writeConnand(0xFF);//--128   
	SSD1306_writeConnand(0xA1);//set segment remap 
	SSD1306_writeConnand(0xA6);//--normal / reverse
	SSD1306_writeConnand(0xA8);//--set multiplex ratio(1 to 64)
	SSD1306_writeConnand(0x3F);//--1/32 duty
	SSD1306_writeConnand(0xC8);//Com scan direction
	SSD1306_writeConnand(0xD3);//-set display offset
	SSD1306_writeConnand(0x00);//
	
	SSD1306_writeConnand(0xD5);//set osc division
	SSD1306_writeConnand(0x80);//
	
	SSD1306_writeConnand(0xD8);//set area color mode off
	SSD1306_writeConnand(0x05);//
	
	SSD1306_writeConnand(0xD9);//Set Pre-Charge Period
	SSD1306_writeConnand(0xF1);//
	
	SSD1306_writeConnand(0xDA);//set com pin configuartion
	SSD1306_writeConnand(0x12);//
	
	SSD1306_writeConnand(0xDB);//set Vcomh
	SSD1306_writeConnand(0x30);//
	
	SSD1306_writeConnand(0x8D);//set charge pump enable
	SSD1306_writeConnand(0x14);//
	
	SSD1306_writeConnand(0xAF);//--turn on oled panel
#elif OLED_TYPE == OLED_091
    SSD1306_writeConnand(0x40);//--display off
    SSD1306_writeConnand(0xB0);//---set low column ad
    SSD1306_writeConnand(0xC8);//---set high column a
    SSD1306_writeConnand(0x81);//--set start line add
    SSD1306_writeConnand(0xff);//--set page address
    SSD1306_writeConnand(0xa1); // contract control
    SSD1306_writeConnand(0xa6);//--128   
    SSD1306_writeConnand(0xa8);//set segment remap 
    SSD1306_writeConnand(0x1f);//--normal / reverse
    SSD1306_writeConnand(0xd3);//--set multiplex rati
    SSD1306_writeConnand(0x00);//--1/32 duty
    SSD1306_writeConnand(0xd5);//Com scan direction
    SSD1306_writeConnand(0xf0);//-set display offset
    SSD1306_writeConnand(0xd9);//
    SSD1306_writeConnand(0x22);//set osc division
    SSD1306_writeConnand(0xda);//
    SSD1306_writeConnand(0x02);//set area color mode 
    SSD1306_writeConnand(0xdb);//
    SSD1306_writeConnand(0x49);//Set Pre-Charge Perio
    SSD1306_writeConnand(0x8d);//
    SSD1306_writeConnand(0x14);//set com pin configua
    SSD1306_writeConnand(0xaf);//

#elif
 #error "please specify oled type : OLED_TYPE"
#endif
    
}

void OLED_clean()
{

	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		SSD1306_writeConnand(0xb0+i);    //设置页地址（0~7）
		SSD1306_writeConnand(0x00);      //设置显示位置—列低地址
		SSD1306_writeConnand(0x10);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)SSD1306_writeData(0); 
	} //更新显示

    OLEDcurser.x=0;
    OLEDcurser.y=0;
    
}

void OLED_setPos(unsigned char x, unsigned char y)
{
    SSD1306_writeConnand(0xb0 + y);
    SSD1306_writeConnand(((x & 0xf0) >> 4) | 0x10);
    SSD1306_writeConnand(x & 0x0f);
}
void OLED_putChar(char chr)
{

	if (OLEDcurser.x > 128)
	{
		OLEDcurser.x = 0;
		OLEDcurser.y += 1;
	}
	if (OLEDcurser.y > 7)
	{
		OLEDcurser.y = 0;
		OLED_clean();
	}

    switch (chr)
    {
    case '\r':
        OLEDcurser.x=0;
        break;
    case '\t':
        OLEDcurser.x+=(24);
        break;        
    case '\n':
            
            OLEDcurser.y++;
        break;

    default:
            OLED_showChar(OLEDcurser.x,OLEDcurser.y,chr,6);
            OLEDcurser.x+=(6);if(OLEDcurser.x>WIDTH-6) {OLEDcurser.y++; OLEDcurser.x = 0; }
        break;
    }

}
//在指定位置显示一个字符
//x:0~127
//y:0~63
//mode:0,反白显示;1,正常显示
//size:选择字体 16/6
void OLED_showChar(unsigned char x, unsigned char y,  char chr, unsigned char Char_Size)
{
    unsigned char  c = 0, i = 0;
    c = chr - ' '; //得到偏移后的??
    if (x > WIDTH - 1)
    {
        x = 0;
        y = y + 2;
    }
    if (Char_Size == 8)
    {
        OLED_setPos(x, y);
        for (i = 0; i < 8; i++)
            SSD1306_writeData(F8X16[c * 16 + i]);
        OLED_setPos(x, y + 1);
        for (i = 0; i < 8; i++)
            SSD1306_writeData(F8X16[c * 16 + i + 8]);
    }
    if(Char_Size==6)
    {
        OLED_setPos(x, y);
        for (i = 0; i < 6; i++)
            SSD1306_writeData(F6x8[c][i]);
    }
    if(Char_Size == 24)
    {
        OLED_setPos(x, y);
        for (i = 0; i < 24; i++)
            SSD1306_writeData(F2440[c][i]);
        OLED_setPos(x, y + 1);
        for (i = 0; i < 24; i++)
            SSD1306_writeData(F2440[c][i+24]);
        OLED_setPos(x, y + 2);
        for (i = 0; i < 24; i++)
            SSD1306_writeData(F2440[c][i+48]);
        OLED_setPos(x, y + 3);
        for (i = 0; i < 24; i++)
            SSD1306_writeData(F2440[c][i+72]);
        OLED_setPos(x, y + 4);
        for (i = 0; i < 24; i++)
            SSD1306_writeData(F2440[c][i+96]);
        OLED_setPos(x, y + 5);
        for (i = 0; i < 24; i++)
            SSD1306_writeData(F2440[c][i+120]);
    }
}

//显示的数字
//x,y :起点坐标
//len :数字的位数
//size:字体大小
//mode:填充模式	0,叠加模式;1,叠加模式
//num:数字(0~4294967295);
void OLED_showNum(unsigned char x, unsigned char y, unsigned int num, unsigned char len, unsigned char size2)
{
    unsigned char  t, temp;
    unsigned char  enshow = 0;
    for (t = 0; t < len; t++)
    {
        temp = (num / oled_pow(10, len - t - 1)) % 10;
        if (enshow == 0 && t < (len - 1))
        {
            if (temp == 0)
            {
                OLED_showChar(x + (size2+2 ) * t, y, '0', size2);
                continue;
            }
            else
                enshow = 1;
        }
        OLED_showChar(x + (size2+2 ) * t, y, temp + '0', size2);
    }
}

//显示字符串
void OLED_showString(unsigned char x, unsigned char y,  char *chr, unsigned char Char_Size)
{
    unsigned char  j = 0;
    while (chr[j])
    {
        OLED_showChar(x, y, chr[j], Char_Size);
        x += 8;
        if (x > 120)
        {
            x = 0;
            y += 2;
        }
        j++;
    }
}

unsigned int oled_pow(unsigned char m, unsigned char n)
{
    unsigned int  result = 1;
    while (n--)
        result *= m;
    return result;
}

void OLED_drawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int  j=0;
 unsigned char  x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
        OLED_setPos(x0,y);
		
    for(x=x0;x<x1;x++)
	    {
            SSD1306_writeData(BMP[j++]);      
	        	
	    }
	}
} 
void OLED_putNum(unsigned char x, unsigned char y, unsigned int num, unsigned char len)
{
    unsigned char  t, temp;
    unsigned char  enshow = 0;
    for (t = 0; t < len; t++)
    {
        temp = (num / oled_pow(10, len - t - 1)) % 10;
        if (enshow == 0 && t < (len - 1))
        {
            if (temp == 0)
            {
                OLED_putChar('0');
                continue;
            }
            else
                enshow = 1;
        }
        OLED_putChar(temp + '0');
    }
}
// 格式化输出在OLED上 目前支持的格式有 %d 整数 %f小数(2位小数点) %s 字符串 %c 字符
void OLED_printf( char *str,...)
{
    va_list  arg ;
    int arg_int = 0;
    double arg_double = 0.0;
    int len = 0;
    char* arg_ptr = 0;
    va_start(arg,str);


    while(*str!='\0')
    {
        switch (*str)
        {
        case '%':
            str++;
            if((*str)<':')
            {
                len = (*str)-'0';
                str++;
            } 
            switch (*str)
            {
            case 'D':
            case 'd':

                arg_int = va_arg(arg,int);
                if (arg_int<0)
                {
                    arg_int = -arg_int;
                    OLED_putChar('-');
                }
                
                if (len==0)
                {
                    len = (int)log10(arg_int)+1;
                }
                
                OLED_putNum(OLEDcurser.x,OLEDcurser.y,arg_int,len);
                len = 0;
                break;
            case 'C':
            case 'c':
                OLED_putChar(va_arg(arg,int));
                break;
            case 'F':
            case 'f':
                arg_double = va_arg(arg,double)*100;
                if (arg_double<0)
                {
                    arg_double = -arg_double;
                    OLED_putChar('-');
                }
                if (len==0)
                {
                    len = (int)log10((int)arg_double)+1;
                }
                
                arg_int = (int)arg_double/100;
                OLED_putNum(OLEDcurser.x,OLEDcurser.y,arg_int,len-2);
                OLED_putChar('.');
                arg_int = ((int)arg_double % 100 )+((int)arg_double % 10);
                OLED_putNum(OLEDcurser.x,OLEDcurser.y,arg_int,2);
                break;
            case 'S':
            case 's':
                arg_ptr = va_arg(arg,char*);
                while (*arg_ptr)
                {
                    OLED_putChar(*arg_ptr);
                    arg_ptr++;
                }
                
                break;
            default:str++;
                break;
            }

            break;
        
        default:
            OLED_putChar(*str);
            break;
        }
        str++;
    }
    va_end(arg);

}

void OLED_setCurser(unsigned char x,unsigned char y)
{
    OLEDcurser.x=x;
    OLEDcurser.y=y;
}
