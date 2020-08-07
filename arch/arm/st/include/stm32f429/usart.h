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
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//����1��ʼ�� 
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/12/4
//�汾��V1.1
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved
//********************************************************************************
//�޸�˵�� 
//V1.1   20160120
//����_ttywrch����,�޸�ʹ��HAL��ʱ,���ܱ�__use_no_semihosting�Ĵ���. 
////////////////////////////////////////////////////////////////////////////////// 
#define USART_REC_LEN  			512  	// 2^9 �����������ֽ��� 512
#define EN_USART1_RX 			0		//ʹ�ܣ�1��/��ֹ��0������1����
	  	
// extern char  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
// extern u16 USART_RX_STA;         		//����״̬���	
extern char input_state ;
void uart_init(u32 pclk2, u32 bound,uint8_t int_en);
//��ʼ������1 
//pclk2��PCLK2ʱ��Ƶ�ʣ�Ĭ����90
//bound ������

void uart2_init(u32 pclk2, u32 bound ,uint8_t int_en);
// pclk Ĭ��45
extern int uart2_putchar(int ch);
extern void uart2_init(u32 pclk2, u32 bound ,uint8_t int_en);
extern void uart2_send(char* pch);
extern char uart2_getKey();
extern unsigned int uart2_NumberOfData();
#endif	   
















