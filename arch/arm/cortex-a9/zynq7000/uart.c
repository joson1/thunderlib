/*
 * @Author: your name
 * @Date: 2020-08-10 18:33:16
 * @LastEditTime: 2020-08-24 13:23:45
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\arch\arm\xilinx\zynq\uart.c
 */
#include "zynq7000/uart.h"
#define InputClockHz 100000000

void uart_init(UART_TypeDef* UART,uint32_t Baudrete)
{

    uint32_t IterBAUDDIV,BRGR_Value,CalcBaudRate,BaudError;
    uint32_t Best_Error = 0xFFFFFFFFU;
    uint32_t Best_BRGR = 0U;
    uint32_t Best_BAUDDIV = 0U;
    uint32_t PercentError;




	for (IterBAUDDIV = 4; IterBAUDDIV < 255; IterBAUDDIV++) {

		/* Calculate the value for BRGR register */
		BRGR_Value = InputClockHz / (Baudrete * (IterBAUDDIV + 1));

		/* Calculate the baud rate from the BRGR value */
		CalcBaudRate = InputClockHz/ (BRGR_Value * (IterBAUDDIV + 1));

		/* Avoid unsigned integer underflow */
		if (Baudrete > CalcBaudRate) {
			BaudError = Baudrete - CalcBaudRate;
		}
		else {
			BaudError = CalcBaudRate - Baudrete;
		}

		/* Find the calculated baud rate closest to requested baud rate. */
		if (Best_Error > BaudError) {

			Best_BRGR = BRGR_Value;
			Best_BAUDDIV = IterBAUDDIV;
			Best_Error = BaudError;
		}
	}

    /* Make sure the best error is not too large. */
    PercentError = (Best_Error * 100) / Baudrete;

    UART->mode = 0x00000020;
    UART->Control = 0x00000128;
    
    UART->Baud_rate_gen = Best_BRGR;
    UART->Baud_rate_divider = Best_BAUDDIV;

    UART->Control |= ((1<<(1))&&(1<<(0)));
    UART->Control &= ~( (1<<(3))&&(1<<(5)) );
    UART->Control |= ( (1<<(4))&&(1<<(2)) );
    
    UART->Rcvr_FIFO_trigger_level = 0;
    UART->Control = 0x00000117;    
    UART->Rcvr_timout = 0;
}

void uart_send(UART_TypeDef* UART ,char ch)
{
    while( (UART->Channel_sts&(1<<4)))  ;
    UART->TX_RX_FIFO = ch;
}

char uart_get(UART_TypeDef* UART)
{
    return UART->TX_RX_FIFO;
}