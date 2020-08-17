/*
 * @Author: your name
 * @Date: 2020-08-10 18:03:51
 * @LastEditTime: 2020-08-17 14:23:31
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\arch\arm\xilinx\include\zynq\zynq.h
 */
#pragma once
#include <stdint.h>

typedef struct
{
  volatile uint32_t DIRM; 
  volatile uint32_t OEN;
  volatile uint32_t INT_MASK;
  volatile uint32_t INT_EN;
  volatile uint32_t INT_DIS;
  volatile uint32_t INT_STAT;
  volatile uint32_t INT_TYPE;
  volatile uint32_t INT_POLARITY;
  volatile uint32_t INT_ANY;
}GPIO_CON_TypeDef;

#define GPIO_BASEADDR 0xE000A000

#define GPIO_CON0 ((GPIO_CON_TypeDef*)(0x00000204+GPIO_BASEADDR))
#define GPIO_CON1 ((GPIO_CON_TypeDef*)(0x00000244+GPIO_BASEADDR))
#define GPIO_CON2 ((GPIO_CON_TypeDef*)(0x00000284+GPIO_BASEADDR))
#define GPIO_CON3 ((GPIO_CON_TypeDef*)(0x000002C4+GPIO_BASEADDR))

typedef struct
{
  volatile uint32_t* MASK_DATA_LSW;
  volatile uint32_t* MASK_DATA_MSW;
  volatile uint32_t* DATA;
  volatile uint32_t* DATA_RO;
  volatile GPIO_CON_TypeDef* controller;
  
} GPIO_TypeDef;

GPIO_TypeDef GPIO_BANK0;
GPIO_TypeDef GPIO_BANK1;
GPIO_TypeDef GPIO_BANK2;
GPIO_TypeDef GPIO_BANK3;


typedef struct
{
  volatile uint32_t Control;    
  volatile uint32_t mode;   
  volatile uint32_t Intrp_en;  
  volatile uint32_t Intrp_dis;  
  volatile uint32_t Intrp_mask;      
  volatile uint32_t Chnl_int_sts;      
  volatile uint32_t Baud_rate_gen;    
  volatile uint32_t Rcvr_timout;    
  volatile uint32_t Rcvr_FIFO_trigger_level;     
  volatile uint32_t Modem_ctrl; 
  volatile uint32_t Modem_sts;  
  volatile uint32_t Channel_sts; 
  volatile uint32_t TX_RX_FIFO;   
  volatile uint32_t Baud_rate_divider;   
  volatile uint32_t Flow_delay;   
  volatile uint32_t Tx_FIFO_trigger_level;   
} UART_TypeDef;

#define UART_CLK_CTRL ((volatile unsigned int*)(0xF8000154))
#define UART0 ((UART_TypeDef*)(0xE0000000))
#define UART1 ((UART_TypeDef*)(0xE0001000))


