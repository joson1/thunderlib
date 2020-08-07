/*
 * @Author: your name
 * @Date: 2020-08-06 23:02:19
 * @LastEditTime: 2020-08-07 21:15:53
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\arch\arm\st\include\stm32f429\usart.h
 */
#ifndef __USART_H
#define __USART_H 
#include "stm32f429/sys.h"
#include "stdio.h"	  

#ifdef DEBUG

#define DEBUGPRINT(fmt,arg...)   printf(fmt,##arg)

#else

#define DEBUGPRINT(fmt,arg...) while(0)

#endif


#define PRINTTOLCD 0
#define PRINTTOUART1 1
#define PRINTTOOLED 2

#define INPUT_UART1 0
#define INPUT_TM1638 1

#define PRINTFTO PRINTTOUART1
                    //PRINTTOLCD
                    //PRINTTOUART1

#define INPUT_IN INPUT_UART1

//////////////////////////////////////////////////////////////////////////////////	   
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//串口1初始化 
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2015/12/4
//版本：V1.1
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved
//********************************************************************************
//修改说明 
//V1.1   20160120
//新增_ttywrch函数,修改使用HAL库时,可能报__use_no_semihosting的错误. 
////////////////////////////////////////////////////////////////////////////////// 
#define USART_REC_LEN  			512  	// 2^9 定义最大接收字节数 512
#define EN_USART1_RX 			0		//使能（1）/禁止（0）串口1接收
	  	
// extern char  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
// extern u16 USART_RX_STA;         		//接收状态标记	
extern char input_state ;
void uart_init(u32 pclk2, u32 bound,uint8_t int_en);
//初始化串口1 
//pclk2是PCLK2时钟频率，默认是90
//bound 波特率

void uart2_init(u32 pclk2, u32 bound ,uint8_t int_en);
// pclk 默认45
extern int uart2_putchar(int ch);
extern void uart2_init(u32 pclk2, u32 bound ,uint8_t int_en);
extern void uart2_send(char* pch);
extern char uart2_getKey();
extern unsigned int uart2_NumberOfData();
#endif	   
















