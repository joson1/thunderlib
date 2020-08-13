/*
 * @Author: your name
 * @Date: 2020-08-10 18:03:51
 * @LastEditTime: 2020-08-10 20:26:48
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\arch\arm\xilinx\include\zynq\zynq.h
 */
#include <stdint.h>




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


