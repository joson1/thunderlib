#include <thunder/spi.h>
#include "stm32f429/spi.h"


spi_dev_t spi0;
spi_dev_t spi1;








static void spi0_init(uint32_t Mode)
{

    GPIO_AF_Set(((SPI_InitDef*)(spi0.spi_init_info))->mosi.GPIOx,((SPI_InitDef*)(spi0.spi_init_info))->mosi.PIN,((SPI_InitDef*)(spi0.spi_init_info))->AFn );
    GPIO_AF_Set(((SPI_InitDef*)(spi0.spi_init_info))->miso.GPIOx,((SPI_InitDef*)(spi0.spi_init_info))->miso.PIN,((SPI_InitDef*)(spi0.spi_init_info))->AFn );
    GPIO_AF_Set(((SPI_InitDef*)(spi0.spi_init_info))->sck.GPIOx,((SPI_InitDef*)(spi0.spi_init_info))->sck.PIN,((SPI_InitDef*)(spi0.spi_init_info))->AFn );


    SPI_init(SPI1, Mode, SPI_8Bits_Mode, 1);

}
static void spi0_setMode(uint32_t Mode)
{
    SPI_init(SPI1, Mode, SPI_8Bits_Mode, 1);

}

static void spi0_setClkDiv(uint32_t Div)
{
    // SPI_init(SPI1, Mode, SPI_8Bits_Mode, 1);
    SPI1->CR1 &= 0XFFC7;
	SPI1->CR1 |= (Div-1)<<3;
	SPI1->CR1 |= 1<<6;
	
}

static int spi0_transfer(int data)
{
    return SPI_Write_Read(SPI1,data);
}



spi_dev_t spi0 = 
{
    .id = 0,
    .init = spi0_init,
    .setMode = spi0_setMode,
    .setBitOrder=0,
    .setClkDiv=spi0_setClkDiv,
    .transfer = spi0_transfer,
};



static void spi1_init(uint32_t Mode)
{
    GPIO_AF_Set(((SPI_InitDef*)(spi1.spi_init_info))->mosi.GPIOx,((SPI_InitDef*)(spi1.spi_init_info))->mosi.PIN,((SPI_InitDef*)(spi1.spi_init_info))->AFn );
    GPIO_AF_Set(((SPI_InitDef*)(spi1.spi_init_info))->miso.GPIOx,((SPI_InitDef*)(spi1.spi_init_info))->miso.PIN,((SPI_InitDef*)(spi1.spi_init_info))->AFn );
    GPIO_AF_Set(((SPI_InitDef*)(spi1.spi_init_info))->sck.GPIOx,((SPI_InitDef*)(spi1.spi_init_info))->sck.PIN,((SPI_InitDef*)(spi1.spi_init_info))->AFn );


    SPI_init(SPI2, Mode, SPI_8Bits_Mode, 1);
    
}
static void spi1_setMode(uint32_t Mode)
{
    SPI_init(SPI2, Mode, SPI_8Bits_Mode, 1);

}

static void spi1_setClkDiv(uint32_t Div)
{
    // SPI_init(SPI1, Mode, SPI_8Bits_Mode, 1);
    SPI2->CR1 &= 0XFFC7;
	SPI2->CR1 |= (Div-1)<<3;
	SPI2->CR1 |= 1<<6;
	
}

static int spi1_transfer(int data)
{
    return SPI_Write_Read(SPI2,data);
}



spi_dev_t spi1 = 
{
    .id = 1,
    .init = spi1_init,
    .setMode = spi1_setMode,
    .setBitOrder=0,
    .setClkDiv=spi1_setClkDiv,
    .transfer = spi1_transfer,
};


void stm32f429_spi_init()
{
    spi_dev_attach(&spi0,0);
    spi_dev_attach(&spi1,0);


}
extern void stm32f429_spi_init();


