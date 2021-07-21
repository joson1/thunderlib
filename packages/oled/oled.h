#ifndef __OLED_H_
#define __OLED_H_

#include "ssd1306.h"
#define WIDTH 128
#define HIGH  64

#define LINES (HIGH/8)
#define OLED_091 0
#define OLED_096 1

#define OLED_TYPE OLED_096

typedef struct _curser
{
    unsigned char x;
    unsigned char y;
} Curser;

 
extern  Curser  OLEDcurser;


extern void OLED_init(void);
extern void OLED_draw(unsigned char lines,unsigned char column,unsigned char pages,unsigned char width);
extern void OLED_clean(void);
extern void OLED_setPos(unsigned char x, unsigned char y);
extern void OLED_showChar(unsigned char x, unsigned char y,  char chr, unsigned char Char_Size);
extern void OLED_showNum(unsigned char x, unsigned char y, unsigned int num, unsigned char len, unsigned char size2);
extern void OLED_showString(unsigned char x, unsigned char y,  char *chr, unsigned char Char_Size);
unsigned int oled_pow(unsigned char m, unsigned char n);
extern void OLED_drawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
extern void OLED_printf( char *str,...);
extern void OLED_setCurser(unsigned char x,unsigned char y);
extern void OLED_putChar(char chr);

#endif
