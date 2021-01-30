/*
 * @Author: your name
 * @Date: 2020-09-01 08:18:57
 * @LastEditTime: 2020-10-01 21:36:05
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\arch\arm\xilinx\include\zynq\ttc.h
 */

#include <stdint.h>
#include "zynq7000/zynq.h"


/** TTC Interrupts IDs */
#define TTC0_TTCx_1_INTERRUPT	42
#define TTC0_TTCx_2_INTERRUPT	43
#define TTC0_TTCx_3_INTERRUPT	44
#define TTC1_TTCx_1_INTERRUPT	69
#define TTC1_TTCx_2_INTERRUPT	70
#define TTC1_TTCx_3_INTERRUPT	71

/** TTC Clock Control Register Flags */
#define TTC_CLK_CNTRL_EXT_EDGE 	(1 << 6) 
#define TTC_CLK_CNTRL_SRC     	(1 << 5) 
#define TTC_CLK_CNTRL_PS_EN  	(1 << 0)  
#define TTC_CLK_CNTRL_PS_VAL   	(4) 

/** TTC Counter Control Register Flags */
#define TTC_CNT_CNTRL_POL_WAVE	(1 << 6)        
#define TTC_CNT_CNTRL_EN_WAVE   (1 << 5)    
#define TTC_CNT_CNTRL_RST   	(1 << 4)   
#define TTC_CNT_CNTRL_MATCH 	(1 << 3) 
#define TTC_CNT_CNTRL_DEC  	(1 << 2) 
#define TTC_CNT_CNTRL_INT  	(1 << 1)   
#define TTC_CNT_CNTRL_DIS 	(1 << 0) 

/** TTC Interrupt Enable Register Flags */
#define TTC_INT_EN_EV    	(1 << 5) 
#define TTC_INT_EN_CNT_OVR 	(1 << 4)
#define TTC_INT_EN_MATCH3 	(1 << 3)  
#define TTC_INT_EN_MATCH2	(1 << 2)  
#define TTC_INT_EN_MATCH1 	(1 << 1) 
#define TTC_INT_EN_INTERVAL	(1 << 0)   

/** TTC Event Control Timer Register Flags */
#define TTC_EV_CNTRL_TIM_E_OV 	(1 << 2)
#define TTC_EV_CNTRL_TIM_E_LO	(1 << 1)
#define TTC_EV_CNTRL_TIM_E_EN 	(1 << 0)


#define TTC_CLK_SRC_EXT         1
#define TTC_CLK_SRC_PCLK        0
#define TTC_CLK_SRC_DEFAULT     TTC_CLK_SRC_PCLK


/** TTC Reset Configuration value */
/*Output waveform enable & disable counter*/
#define TTC_RESET_CONFIG   	(0x21) 

/** TTC Values */
#define TTC_INT_VALUE    	(111)         
#define TTC_MATCH1_VALUE 	(111)     

void ttc_reset(TTC_TypeDef* ttc,uint8_t n);
void ttc_set_clockSource(TTC_TypeDef* ttc,uint8_t n,uint8_t clocksrc);
void ttc_CalcIntervalFromFreq(uint32_t Freq,uint16_t *Interval, uint8_t *Prescaler);
void ttc_stop(TTC_TypeDef* ttc,uint8_t n);
void ttc_start(TTC_TypeDef* ttc,uint8_t n);

