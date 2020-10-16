/*
 * @Author: your name
 * @Date: 2020-08-20 21:46:25
 * @LastEditTime: 2020-10-05 19:30:00
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\drivers\interrupt\devices\interrupt-zynq.c
 */
#include <thunder/interrput.h>
#include "zynq/zynq.h"
#include <stdio.h>
#include "zynq/xil_exception.h"
#include "zynq/xscugic_hw.h"
static u32 CpuId = 0; /**< CPU Core identifier */


static void DoDistributorInit(u32 cpuid)
{
	u32 Int_Id;
	u32 LocalCpuID = cpuid;
    *ICDDCR = 0;

	/*
	 * Set the security domains in the int_security registers for
	 * non-secure interrupts
	 * All are secure, so leave at the default. Set to 1 for non-secure
	 * interrupts.
	 */

	/*
	 * For the Shared Peripheral Interrupts INT_ID[MAX..32], set:
	 */

	/*
	 * 1. The trigger mode in the int_config register
	 * Only write to the SPI interrupts, so start at 32
	 */
	for (Int_Id = 32U; Int_Id < XSCUGIC_MAX_NUM_INTR_INPUTS;
			Int_Id = Int_Id+16U) {
		/*
		 * Each INT_ID uses two bits, or 16 INT_ID per register
		 * Set them all to be level sensitive, active HIGH.
		 */
		// XScuGic_DistWriteReg(InstancePtr,
		// 			XSCUGIC_INT_CFG_OFFSET_CALC(Int_Id),
		// 			0U);
        *(uint32_t*)((uint32_t)ICDDCR+XSCUGIC_INT_CFG_OFFSET_CALC(Int_Id)) = 0;
	}

#define DEFAULT_PRIORITY    0xa0a0a0a0U
    
	for (Int_Id = 0U; Int_Id < XSCUGIC_MAX_NUM_INTR_INPUTS;
			Int_Id = Int_Id+4U) {
		/*
		 * 2. The priority using int the priority_level register
		 * The priority_level and spi_target registers use one byte per
		 * INT_ID.
		 * Write a default value that can be changed elsewhere.
		 */
		// XScuGic_DistWriteReg(InstancePtr,
		// 			XSCUGIC_PRIORITY_OFFSET_CALC(Int_Id),
		// 			DEFAULT_PRIORITY);
        *(uint32_t*)((uint32_t)ICDDCR+XSCUGIC_PRIORITY_OFFSET_CALC(Int_Id)) = DEFAULT_PRIORITY;

        }
        
	for (Int_Id = 32U; Int_Id<XSCUGIC_MAX_NUM_INTR_INPUTS;Int_Id=Int_Id+4U) {
		/*
		 * 3. The CPU interface in the spi_target register
		 * Only write to the SPI interrupts, so start at 32
		 */
		LocalCpuID |= LocalCpuID << 8U;
		LocalCpuID |= LocalCpuID << 16U;

		// XScuGic_DistWriteReg(InstancePtr,
		// 			 XSCUGIC_SPI_TARGET_OFFSET_CALC(Int_Id),
		// 			 LocalCpuID);

        *(uint32_t*)((uint32_t)ICDDCR + XSCUGIC_SPI_TARGET_OFFSET_CALC(Int_Id)) = LocalCpuID;

	}

	for (Int_Id = 0U; Int_Id<XSCUGIC_MAX_NUM_INTR_INPUTS;Int_Id=Int_Id+32U) {
		/*
		 * 4. Enable the SPI using the enable_set register. Leave all
		 * disabled for now.
		 */
		// XScuGic_DistWriteReg(InstancePtr,
		// XSCUGIC_EN_DIS_OFFSET_CALC(XSCUGIC_DISABLE_OFFSET, Int_Id),
		// 	0xFFFFFFFFU);
        *(uint32_t*)((uint32_t)ICDDCR+XSCUGIC_EN_DIS_OFFSET_CALC(XSCUGIC_DISABLE_OFFSET, Int_Id)) 
                = 0xFFFFFFFFU;

	}

    *ICDDCR = XSCUGIC_EN_INT_MASK;

}

static void DistributorInit()
{
	u32 Int_Id;
	u32 LocalCpuID = CpuId+1;
	u32 RegValue;

    RegValue = *ICDDCR;
	if ((RegValue & XSCUGIC_EN_INT_MASK) == 0U) {
		DoDistributorInit(1);
		return;
	}

	/*
	 * The overall distributor should not be initialized in AMP case where
	 * another CPU is taking care of it.
	 */
	LocalCpuID |= LocalCpuID << 8U;
	LocalCpuID |= LocalCpuID << 16U;
	for (Int_Id = 32U; Int_Id < XSCUGIC_MAX_NUM_INTR_INPUTS;
			Int_Id = Int_Id+4U) {
		// RegValue = XScuGic_DistReadReg(InstancePtr,
		// 			XSCUGIC_SPI_TARGET_OFFSET_CALC(Int_Id));

        RegValue = *(uint32_t*)((uint32_t)ICDDCR+XSCUGIC_SPI_TARGET_OFFSET_CALC(Int_Id));

		RegValue |= LocalCpuID;
		// XScuGic_DistWriteReg(InstancePtr,
		// 		     XSCUGIC_SPI_TARGET_OFFSET_CALC(Int_Id),
		// 		     RegValue);
        *(uint32_t*)((uint32_t)ICDDCR + XSCUGIC_SPI_TARGET_OFFSET_CALC(Int_Id)) = RegValue;


	}
}

static inline void CPUInitialize()
{
	/*
	 * Program the priority mask of the CPU using the Priority mask register
	 */
    *(uint32_t*)((uint32_t)ICCICR+XSCUGIC_CPU_PRIOR_OFFSET) = 0xF0U;



	/*
	 * If the CPU operates in both security domains, set parameters in the
	 * control_s register.
	 * 1. Set FIQen=1 to use FIQ for secure interrupts,
	 * 2. Program the AckCtl bit
	 * 3. Program the SBPR bit to select the binary pointer behavior
	 * 4. Set EnableS = 1 to enable secure interrupts
	 * 5. Set EnbleNS = 1 to enable non secure interrupts
	 */

	/*
	 * If the CPU operates only in the secure domain, setup the
	 * control_s register.
	 * 1. Set FIQen=1,
	 * 2. Set EnableS=1, to enable the CPU interface to signal secure
	 *  interrupts. Only enable the IRQ output unless secure interrupts
	 * are needed.
	 */
    *(uint32_t*)((uint32_t)ICCICR + XSCUGIC_CONTROL_OFFSET) = 0x07U;
}

static inline void XScuGic_Stop()
{

    u32 Int_Id;
	u32 RegValue;
	u32 Target_Cpu;
	u32 DistDisable = 1; /* Track distributor status*/
    u32 LocalCpuID = ((u32)0x1 << CpuId);
    RegValue =  *ICDDCR ;

	LocalCpuID |= LocalCpuID << 8U;
	LocalCpuID |= LocalCpuID << 16U;


	/*
	 * Check if the interrupt are targeted to current cpu only or not.
	 * Also remove current cpu from interrupt target register for all
	 * interrupts.
	 */
	for (Int_Id = 32U; Int_Id < 95;
			Int_Id = Int_Id+4U) {

		// Target_Cpu = XScuGic_DistReadReg(InstancePtr,

        Target_Cpu = *(uint32_t*)((uint32_t)ICDDCR + XSCUGIC_SPI_TARGET_OFFSET_CALC(Int_Id));
		if ((Target_Cpu != LocalCpuID) && (Target_Cpu != 0)) {
			/*
			 * If any other CPU is also programmed to target
			 * register, GIC distributor can not be disabled.
			 */
			DistDisable = 0;
		}

		/* Remove current CPU from interrupt target register */
		Target_Cpu &= (~LocalCpuID);
		// XScuGic_DistWriteReg(InstancePtr,
		// 	XSCUGIC_SPI_TARGET_OFFSET_CALC(Int_Id), Target_Cpu);
        *(uint32_t*)((uint32_t)ICDDCR + XSCUGIC_SPI_TARGET_OFFSET_CALC(Int_Id)) = Target_Cpu;

        
	}

	/*
	 * If GIC distributor is safe to be disabled, disable all the interrupt
	 * and then disable distributor.
	 */
	if (DistDisable == 1) {
		for (Int_Id = 0U; Int_Id < 95;
				Int_Id = Int_Id+32U) {
			/*
			 * Disable all the interrupts
			 */
            *(uint32_t*)((uint32_t)ICDDCR + XSCUGIC_EN_DIS_OFFSET_CALC(0x00000180U,Int_Id)) = 0xFFFFFFFFU;

			// XScuGic_DistWriteReg(InstancePtr,
			//   XSCUGIC_EN_DIS_OFFSET_CALC(XSCUGIC_DISABLE_OFFSET,
			// 				Int_Id),
			// 0xFFFFFFFFU);

		}
		//XScuGic_DistWriteReg(InstancePtr, XSCUGIC_DIST_EN_OFFSET, 0U);
        *ICDDCR = 0U;


	}
    

}

void zynq_interrupt_init()
{


    XScuGic_Stop();
    DistributorInit();
    CPUInitialize();

    Xil_ExceptionEnable();


}
extern void zynq_interrupt_init();

int irq_register(uint32_t Irq_id,InterruptHandler handler,uint32_t Trigger_edge,void* Message,void (*CallBack))
{
    uint32_t n,m;
    n = Irq_id/16;
    m = (Irq_id%16);
    IRQ_vector_table[Irq_id].Handler = handler;
    IRQ_vector_table[Irq_id].data	 = Message;
    IRQ_vector_table[Irq_id].CallBack= CallBack;
    ICDICFR[n] &= ~(Trigger_edge<<(m*2));
    ICDICFR[n] |=  (Trigger_edge<<(m*2));

    n = Irq_id/32;
    m = Irq_id%32;
    ICDISER[n] |= (1<<m);
	
    return 0;
}



