/*
 * @Author: your name
 * @Date: 2020-08-25 10:04:49
 * @LastEditTime: 2020-10-09 10:27:19
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\drivers\bus\spi\devices\spi-zynq.c
 */
#include <thunder/spi.h>
#include "zynq7000/zynq.h"





void spi_zynq_reset()
{
    int i=0; //i for delay
    // SLCR_UNLOCK = UNLOCK_KEY;
    //unlock SLCRs
    SLCR_UNLOCK();
    SLCR_SPI_RST = 0xF;
    //assert SPI reset
    for(i=0;i<1000;i++);
    //make sure Reset occurs
    SLCR_SPI_RST = 0;
    //deassert
    SLCR_LOCK();
    // SLCR_LOCK = LOCK_KEY;
    //relock SLCRs
}

static inline void setMode(SPI_TypeDef* spi,uint8_t Mode)
{
    spi->config &= ~(3<<1);
    switch (Mode)
    {
    case SPI_MODE_0:
        // spi->config &= ~(3<<(1));
        break;
    case SPI_MODE_1:
        // spi->config &= ~(1<<1);
        spi->config |=  (2<<1);
        /* code */
        break;
    case SPI_MODE_2:
        spi->config |=  (1<<1);    
        // spi->config &= ~(1<<2);
        /* code */
        break;
    case SPI_MODE_3:
        spi->config |=  (3<<1);    
        // spi->config |=  (1<<2);    
        /* code */
        break;
    
    default:
        break;
    }   
}

void setClockDivider(SPI_TypeDef* spi,uint8_t SPI_CLOCK_DIV)
{
    spi->config &= ~(SPI_CLOCK_DIV<<3);
    spi->config |=  (SPI_CLOCK_DIV<<3);
    spi->config |=  1;
}


static void spi_init(SPI_TypeDef* spi,uint8_t SPI_CLOCK_DIV,uint8_t Mode)
{
    spi->config |= (1<<14); //master modespi_dev_t
    spi->intrpt_en = 0xff;
    
    setClockDivider(spi,SPI_CLOCK_DIV);
    setMode(spi,Mode);

    spi->RX_thres = 1;
    spi->En = 1;
}

static int zynq_spi_transfer(SPI_TypeDef* spi,int data)
{
    int tmp = 0;
    spi->config &= ~(1<<10);
    spi->Tx_data = data;
    while(!(spi->intr_status&(1<<4)));
    spi->config |= (1<<10);
    spi->intr_status = 0xff;
    tmp = spi->Rx_data;
    if(spi->intr_status&(1<<4))
    {
        tmp = spi->Rx_data;
        spi->intr_status = 0xff;
    }

    return tmp;
}

static int zynq_spi_write(SPI_TypeDef* spi,int data)
{
    spi->config &= ~(1<<10);
    spi->intrpt_en = (1<<4);
    spi->Tx_data = data;
    // while(!(spi->intr_status&(1<<4)));

    return 0;
}



static int zynq_spi_read(SPI_TypeDef* spi)
{
    
    // while ( !(spi->intr_status&(1<<4)) );
    
    return spi->Rx_data;
}



static void spi0_setMode(uint32_t Mode)
{
    setMode(SPI0,Mode);
}

static int spi0_transfer(int data)
{
    return zynq_spi_transfer(SPI0,data);
}

static void spi0_init(uint32_t Mode)
{
    spi_init(SPI0,SPI_CLOCK_DIV32,Mode);
}
static void spi0_setClkDiv(uint8_t SPI_CLOCK_DIV)
{
    setClockDivider(SPI0,SPI_CLOCK_DIV);
    
}

int spi0_write(int data)
{
    zynq_spi_write(SPI0,data);
}

int spi0_read()
{
    return zynq_spi_read(SPI0);
}

spi_dev_t spi0 = 
{
    .id = 0,
    .init = spi0_init,
    .setMode = spi0_setMode,
    .setBitOrder=0,
    .setClkDiv=spi0_setClkDiv,
    .transfer = spi0_transfer,
    .write =spi0_write,
    .read =spi0_read,
};

void zynq_spi_init()
{
    spi_zynq_reset();
    spi_dev_attach(&spi0,0);

}
extern void zynq_spi_init();
