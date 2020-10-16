/*
 * @Author: your name
 * @Date: 2020-08-10 18:31:57
 * @LastEditTime: 2020-08-21 12:28:04
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\arch\arm\xilinx\include\zynq\uart.h
 */
#include "zynq/zynq.h"

void uart_init(UART_TypeDef* UART,uint32_t Baudrete);
void uart_send(UART_TypeDef* UART ,char ch);
char uart_get(UART_TypeDef* UART);
