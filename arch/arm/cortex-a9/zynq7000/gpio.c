/*
 * @Author: your name
 * @Date: 2020-08-16 22:23:49
 * @LastEditTime: 2020-08-16 23:25:36
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\arch\arm\xilinx\zynq\gpio.c
 */
#include "zynq7000/zynq.h"



GPIO_TypeDef GPIO_BANK0 = 
{
    .MASK_DATA_LSW    = (uint32_t *)(GPIO_BASEADDR+0x00000000),
    .MASK_DATA_MSW    = (uint32_t *)(GPIO_BASEADDR+0x00000004),
    .DATA             = (uint32_t *)(GPIO_BASEADDR+0x00000040),
    .DATA_RO          = (uint32_t *)(GPIO_BASEADDR+0x00000060),
    .controller       = GPIO_CON0
};

GPIO_TypeDef GPIO_BANK1 = 
{
    .MASK_DATA_LSW    = (uint32_t *)(GPIO_BASEADDR+0x00000008),
    .MASK_DATA_MSW    = (uint32_t *)(GPIO_BASEADDR+0x0000000C),
    .DATA             = (uint32_t *)(GPIO_BASEADDR+0x00000044),
    .DATA_RO          = (uint32_t *)(GPIO_BASEADDR+0x00000064),
    .controller       = GPIO_CON1
};
GPIO_TypeDef GPIO_BANK2 = 
{
    .MASK_DATA_LSW    = (uint32_t *)(GPIO_BASEADDR+0x00000010),
    .MASK_DATA_MSW    = (uint32_t *)(GPIO_BASEADDR+0x00000014),
    .DATA             = (uint32_t *)(GPIO_BASEADDR+0x00000048),
    .DATA_RO          = (uint32_t *)(GPIO_BASEADDR+0x00000068),
    .controller       = GPIO_CON2
};
GPIO_TypeDef GPIO_BANK3 = 
{
    .MASK_DATA_LSW    = (uint32_t *)(GPIO_BASEADDR+0x00000018),
    .MASK_DATA_MSW    = (uint32_t *)(GPIO_BASEADDR+0x0000001C),
    .DATA             = (uint32_t *)(GPIO_BASEADDR+0x0000004C),
    .DATA_RO          = (uint32_t *)(GPIO_BASEADDR+0x0000006C),
    .controller       = GPIO_CON3
};

