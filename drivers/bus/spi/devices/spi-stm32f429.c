#include <thunder/spi.h>
#include "stm32f429/spi.h"
#include <thunder/device.h>
#include <config.h>

spi_dev_t spi0;
spi_dev_t spi1;








static void spi0_init(uint32_t Mode)
{

    // GPIO_AF_Set(((SPI_InitDef*)(spi0.spi_init_info))->mosi.GPIOx,((SPI_InitDef*)(spi0.spi_init_info))->mosi.PIN,((SPI_InitDef*)(spi0.spi_init_info))->AFn );
    // GPIO_AF_Set(((SPI_InitDef*)(spi0.spi_init_info))->miso.GPIOx,((SPI_InitDef*)(spi0.spi_init_info))->miso.PIN,((SPI_InitDef*)(spi0.spi_init_info))->AFn );
    // GPIO_AF_Set(((SPI_InitDef*)(spi0.spi_init_info))->sck.GPIOx,((SPI_InitDef*)(spi0.spi_init_info))->sck.PIN,((SPI_InitDef*)(spi0.spi_init_info))->AFn );


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

static int stm32_spi_transfer(spi_dev_t* pdev,int data)
{
    return SPI_Write_Read((typeof(SPI1))(pdev->prv_data),data);
}

static int spi_write(spi_dev_t* pdev,int data)
{
    SPI_Write_Read((typeof(SPI1))(pdev->prv_data),data);
    return 0;
}
static int spi_read(spi_dev_t* pdev)
{
    return SPI_Write_Read((typeof(SPI1))(pdev->prv_data),0);
}


static void spi_setup(spi_dev_t* pdev,uint32_t mode,uint32_t bitOrder)
{
    SPI_init((typeof(SPI1))(pdev->prv_data) , mode, SPI_8Bits_Mode, 1);
}

#if CONFIG_STM32_SPI1_EN
spi_dev_t spi0 = 
{
    .id = 0,
    .prv_data = SPI1,
    .setup = spi_setup,
    .transfer = stm32_spi_transfer,
    .write = spi_write,
    .read = spi_read
};

#endif

#if CONFIG_STM32_SPI2_EN
spi_dev_t spi1 = 
{
    .id = 1,
    .prv_data = SPI2,
    .setup = spi_setup,
    .transfer = stm32_spi_transfer,
    .write = spi_write,
    .read = spi_read
};
#endif

#if CONFIG_STM32_SPI3_EN
spi_dev_t spi2= 
{
    .id = 2,
    .prv_data = SPI3,
    .setup = spi_setup,
    .transfer = stm32_spi_transfer,
    .write = spi_write,
    .read = spi_read
};

#endif
#if CONFIG_STM32_SPI4_EN
spi_dev_t spi3 = 
{
    .id = 3,
    .prv_data = SPI4,
    .setup = spi_setup,
    .transfer = stm32_spi_transfer,
    .write = spi_write,
    .read = spi_read
};
#endif
void stm32f429_spi_init()
{
#if CONFIG_STM32_SPI1_EN
    spi_dev_attach(&spi0);
#endif

#if CONFIG_STM32_SPI2_EN
    spi_dev_attach(&spi1);
#endif

#if CONFIG_STM32_SPI3_EN
    spi_dev_attach(&spi2);
#endif

#if CONFIG_STM32_SPI4_EN
    spi_dev_attach(&spi3);
#endif

}

DEV_INIT(stm32f429_spi_init);
