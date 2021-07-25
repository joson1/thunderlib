/*
 * @Author: your name
 * @Date: 2020-08-10 18:03:51
 * @LastEditTime: 2021-01-15 11:21:59
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

extern GPIO_TypeDef GPIO_BANK0;
extern GPIO_TypeDef GPIO_BANK1;
extern GPIO_TypeDef GPIO_BANK2;
extern GPIO_TypeDef GPIO_BANK3;


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


#define MPCORE_BASE 0xF8F00000 


#define ICCICR        ((uint32_t*)(MPCORE_BASE+0x00000100))
#define ICCPMR        ((uint32_t*)(MPCORE_BASE+0x00000104))
#define ICCBPR        ((uint32_t*)(MPCORE_BASE+0x00000108))
#define ICCIAR        ((uint32_t*)(MPCORE_BASE+0x0000010C))
#define ICCEOIR       ((uint32_t*)(MPCORE_BASE+0x00000110))
#define ICCRPR        ((uint32_t*)(MPCORE_BASE+0x00000114))
#define ICCHPIR       ((uint32_t*)(MPCORE_BASE+0x00000118))
#define ICCABPR       ((uint32_t*)(MPCORE_BASE+0x0000011C))
#define ICCIDR        ((uint32_t*)(MPCORE_BASE+0x000001FC))

#define ICDDCR        ((uint32_t*)(MPCORE_BASE+0x00001000))
#define ICDICTR       ((uint32_t*)(MPCORE_BASE+0x00001004))
#define ICDIDIR       ((uint32_t*)(MPCORE_BASE+0x00001008))

#define ICDISR        ((uint32_t*)(MPCORE_BASE+0x00001080))

// ICDISR[0]
// ICDISR[1]
// ICDISR[2]
#define ICDISER       ((uint32_t*)(MPCORE_BASE+0x00001100))
//ICDISER[0]
//ICDISER[1]
//ICDISER[2]

#define ICDICER       ((uint32_t*)(MPCORE_BASE+0x00001180))
//ICDICER[0]
//ICDICER[1]
//ICDICER[2]

#define ICDISPR       ((uint32_t*)(MPCORE_BASE+0x00001200))
//ICDISPR[0]
//ICDISPR[1]
//ICDISPR[2]

#define ICDICPR       ((uint32_t*)(MPCORE_BASE+0x00001280))
//ICDICPR[0]
//ICDICPR[1]
//ICDICPR[2]

#define ICDABR       ((uint32_t*)(MPCORE_BASE+0x00001300))
//ICDABR[0]
//ICDABR[1]
//ICDABR[2]

#define ICDIPR       ((uint32_t*)(MPCORE_BASE+0x00001400))
//ICDPR[0]
//ICDPR[1]
//ICDPR[2]
//...
//ICDPR[23]
#define ICDIPTR       ((uint32_t*)(MPCORE_BASE+0x00001800))
//ICDIPTR[0]
//...
//ICDIPTR[23]
#define ICDICFR       ((uint32_t*)(MPCORE_BASE+0x00001C00))
//ICDICFR[0]
//...
//ICDICFR[5]

#define PPI_STATUS     ((uint32_t*)(MPCORE_BASE+0x00001D00))
#define SPI_STATUS     ((uint32_t*)(MPCORE_BASE+0x00001D04))
//SPI_STATUS[0]
//SPI_STATUS[1]
#define ICDSGIR         ((uint32_t*)(MPCORE_BASE+0x00001F00))

#define SLCRLOCK_ADDR		    *((uint32_t *)0xF8000004)
#define SLCRUNLOCK_ADDR		  *((uint32_t *)0xF8000008)
#define SLCR_IIC_RST 	  *((uint32_t *)0xF8000224)
#define SLCR_SPI_RST 	  *((uint32_t *)0xF800021C)
//lock and unlock keys
#define UNLOCK_KEY	0xDF0D
#define LOCK_KEY	  0x767B

//unlock SLCRs
#define SLCR_UNLOCK() \
  SLCRUNLOCK_ADDR = UNLOCK_KEY

//relock SLCRs
#define SLCR_LOCK() \
  SLCRLOCK_ADDR = LOCK_KEY



typedef struct
{
  volatile uint32_t Control;
  volatile uint32_t Status;
  volatile uint32_t address;
  volatile uint32_t data;
  volatile uint32_t Intrpt_status;
  volatile uint32_t Trans_size;
  volatile uint32_t Slave_mon_pause;
  volatile uint32_t Time_out;
  volatile uint32_t Intrpt_mask;
  volatile uint32_t Intrpt_enable;
  volatile uint32_t Intrpt_disable;
  
}I2C_TypeDef ;

#define I2C0            ((I2C_TypeDef*)(0xE0004000))
#define I2C1            ((I2C_TypeDef*)(0xE0005000))

typedef struct
{
  volatile uint32_t config;
  volatile uint32_t intr_status;
  volatile uint32_t intrpt_en;
  volatile uint32_t intrpt_dis;
  volatile uint32_t intrpt_mask;
  volatile uint32_t En;
  volatile uint32_t Delay;
  volatile uint32_t Tx_data;
  volatile uint32_t Rx_data;
  volatile uint32_t slave_idle_count;
  volatile uint32_t TX_thres;
  volatile uint32_t RX_thres;
  volatile uint32_t Mod_id;
  
}SPI_TypeDef;

#define SPI0 ((SPI_TypeDef*)(0xE0006000))
#define SPI1 ((SPI_TypeDef*)(0xE0007000))



typedef struct 
{
  volatile uint32_t clock_control[3];
  volatile uint32_t counter_control[3];
  volatile uint32_t counter_value[3];
  volatile uint32_t interval_counter[3];
  volatile uint32_t match_0_counter[3];
  volatile uint32_t match_1_counter[3];
  volatile uint32_t match_2_counter[3];
  volatile uint32_t ISR[3];
  volatile uint32_t IER[3];
  volatile uint32_t Event_Control_Timer[3];
  volatile uint32_t Event_Register[3];

}TTC_TypeDef ;


#define TTC0 ((TTC_TypeDef*)(0xF8001000))
#define TTC1 ((TTC_TypeDef*)(0xF8002000))




typedef struct
{
  volatile uint32_t LOAD;
  volatile uint32_t COUNTER;
  volatile uint32_t CONTROL;
  volatile uint32_t ISR;

} ptimer_reg_t;

/* Values for control register */
#define PRIVATE_TIMER_CONTROL_PRESCALER_MASK     0x0000FF00
#define PRIVATE_TIMER_CONTROL_PRESCALER_SHIFT    8
#define PRIVATE_TIMER_CONTROL_IRQ_ENABLE_MASK    0x00000004
#define PRIVATE_TIMER_CONTROL_AUTO_RELOAD_MASK   0x00000002
#define PRIVATE_TIMER_CONTROL_ENABLE_MASK        0x00000001

/* Values for ISR register */
#define PRIVATE_TIMER_ISR_EVENT_FLAG_MASK        0x00000001


#define PRIVATE_TIMER_BASE            0xF8F00600
#define PRIVATE_TIMER                ((ptimer_reg_t*)PRIVATE_TIMER_BASE)


