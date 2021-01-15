/*
 * @Author: your name
 * @Date: 1970-01-01 08:00:00
 * @LastEditTime: 2021-01-14 20:09:28
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /ThunderLib/arch/arm/xilinx/zynq/gic.c
 */
#include "zynq/zynq.h"
#include "zynq/xil_exception.h"
#include "zynq/xscugic_hw.h"


extern void InterruptMaptoCpu( uint8_t Cpu_Id, uint32_t Int_Id);

void InterruptMaptoCpu( uint8_t Cpu_Id, uint32_t Int_Id)
{
	u32 RegValue;
	u32 Offset;
	RegValue = *(ICDDCR+XSCUGIC_SPI_TARGET_OFFSET_CALC(Int_Id));

	Offset = (Int_Id & 0x3U);
	Cpu_Id = (0x1U << Cpu_Id);

	RegValue = (RegValue & (~(0xFFU << (Offset*8U))));
	RegValue |= ((Cpu_Id) << (Offset*8U));
    *(ICDDCR+XSCUGIC_SPI_TARGET_OFFSET_CALC(Int_Id)) = RegValue;
	
}