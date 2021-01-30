/*
 * @Author: your name
 * @Date: 2020-08-25 10:21:38
 * @LastEditTime: 2020-08-31 20:40:47
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\drivers\i2c\devices\i2c-zynq.c
 */
#include "zynq7000/zynq.h"
#include <thunder/i2c.h>




static void reset_iic(void)
{
	volatile int i=0; //i for delay
	SLCR_UNLOCK();	//unlock SLCRs
	SLCR_IIC_RST = 0x3;	//assert I2C reset
	for(i=0;i<1000;i++); //wait
	SLCR_IIC_RST = 0;	//deassert
	SLCR_LOCK();		//relock SLCRs
}
#define XPAR_PS7_I2C_0_I2C_CLK_FREQ_HZ 111111115
void i2c_SetSClk(I2C_TypeDef* i2c ,uint32_t FsclHz)
{
	uint32_t Div_a;
	uint32_t Div_b;
	uint32_t ActualFscl;
	uint32_t Temp;
	uint32_t TempLimit;
	uint32_t LastError;
	uint32_t BestError;
	uint32_t CurrentError;
	uint32_t ControlReg;
	uint32_t CalcDivA;
	uint32_t CalcDivB;
	uint32_t BestDivA;
	uint32_t BestDivB;
	uint32_t FsclHzVar = FsclHz;


	/*
	 * Assume Div_a is 0 and calculate (divisor_a+1) x (divisor_b+1).
	 */
	Temp = (XPAR_PS7_I2C_0_I2C_CLK_FREQ_HZ) / ((uint32_t)22U * FsclHzVar);

	/*
	 * If the answer is negative or 0, the Fscl input is out of range.
	 */
	if ((uint32_t)(0U) == Temp) {
		while(1);
	}

	/*
	 * If frequency 400KHz is selected, 384.6KHz should be set.
	 * If frequency 100KHz is selected, 90KHz should be set.
	 * This is due to a hardware limitation.
	 */
	if(FsclHzVar > (uint32_t)384600U) {
		FsclHzVar = (uint32_t)384600U;
	}

	if((FsclHzVar <= (uint32_t)100000U) && (FsclHzVar > (uint32_t)90000U)) {
		FsclHzVar = (uint32_t)90000U;
	}

	/*
	 * TempLimit helps in iterating over the consecutive value of Temp to
	 * find the closest clock rate achievable with divisors.
	 * Iterate over the next value only if fractional part is involved.
	 */
	TempLimit = (((XPAR_PS7_I2C_0_I2C_CLK_FREQ_HZ) %
			((uint32_t)22 * FsclHzVar)) != 	(uint32_t)0x0U) ?
						Temp + (uint32_t)1U : Temp;
	BestError = FsclHzVar;

	BestDivA = 0U;
	BestDivB = 0U;
	for ( ; Temp <= TempLimit ; Temp++)
	{
		LastError = FsclHzVar;
		CalcDivA = 0U;
		CalcDivB = 0U;

		for (Div_b = 0U; Div_b < 64U; Div_b++) {

			Div_a = Temp / (Div_b + 1U);

			if (Div_a != 0U){
				Div_a = Div_a - (uint32_t)1U;
			}
			if (Div_a > 3U){
				continue;
			}
			ActualFscl = (XPAR_PS7_I2C_0_I2C_CLK_FREQ_HZ) /
						(22U * (Div_a + 1U) * (Div_b + 1U));

			if (ActualFscl > FsclHzVar){
				CurrentError = (ActualFscl - FsclHzVar);}
			else{
				CurrentError = (FsclHzVar - ActualFscl);}

			if (LastError > CurrentError) {
				CalcDivA = Div_a;
				CalcDivB = Div_b;
				LastError = CurrentError;
			}
		}

		/*
		 * Used to capture the best divisors.
		 */
		if (LastError < BestError) {
			BestError = LastError;
			BestDivA = CalcDivA;
			BestDivB = CalcDivB;
		}
	}


	/*
	 * Read the control register and mask the Divisors.
	 */
    ControlReg = i2c->Control;

	ControlReg &= ~((uint32_t)0x0000C000U | (uint32_t)0x00003F00U);
	ControlReg |= (BestDivA << 14) |
		(BestDivB << 8);


	// XIicPs_WriteReg(InstancePtr->Config.BaseAddress, (uint32_t)XIICPS_CR_OFFSET,
	// 		  ControlReg);
    i2c->Control = ControlReg;
	
}


/**
 * @description: 
 * @param uint8_t mode 0:Slave 1:Master 
 * @return {type} 
 */
static inline void i2c_init( I2C_TypeDef* i2c, uint32_t clock  )
{
    
    i2c_SetSClk(i2c,clock);
}


int XIicPs_MasterSendPolled(I2C_TypeDef* i2c,uint32_t slave_addr,uint8_t* buf,uint32_t length,int IsRepeatedStart)
{
	uint32_t IntrStatusReg;


	uint32_t Intrs;
	int Status;


	// SetupMaster
    i2c->Control|=(0x00000008U|0x00000040U|0x00000004U|0x00000002U );
    i2c->Control &= ~(0x00000001U);
	/*
	 * Intrs keeps all the error-related interrupts.
	 */
	Intrs = (uint32_t)0x00000200U | (uint32_t)0x00000040U |
		(uint32_t)0x00000004U;
	/*
	 * Clear the interrupt status register before use it to monitor.
	 */
	IntrStatusReg = i2c->Intrpt_status;
    i2c->Intrpt_status = IntrStatusReg;
	/*
	 * Transmit first FIFO full of data.
	 */
	uint32_t LoopCnt;
	/*
	 * Fill FIFO with amount determined above.
	 */
	for (LoopCnt = 0; LoopCnt < length; LoopCnt++) {
		i2c->data = buf[LoopCnt];
	}

    i2c->address = slave_addr;

	IntrStatusReg = i2c->Intrpt_status;

	while ((IntrStatusReg & 0x00000001U) != 0x00000001U){

		IntrStatusReg = i2c->Intrpt_status; //XIicPs_ReadReg(BaseAddr, XIICPS_ISR_OFFSET);
		/*
		 * If there is an error, tell the caller.
		 */
		if ((IntrStatusReg & Intrs) != 0U) {
			break;
		}
	}
	if ((IntrStatusReg & Intrs) != 0U) {
		if (IntrStatusReg & 0x00000200U) {
			Status = -1;   // XST_IIC_ARB_LOST;
		} else {
			Status = -2; ///(int)XST_FAILURE;
		}
	} else {
			Status = 0;//(int)XST_SUCCESS;
	}

	return Status;
}


int XIicPs_MasterRecvPolled(I2C_TypeDef* i2c, uint8_t *buf ,int length, uint16_t SlaveAddr)
{
	uint32_t IntrStatusReg;
	uint32_t Intrs;

	int Result;

	// SetupMaster

    i2c->Control|=(0x00000008U|0x00000040U|0x00000004U|0x00000002U );
    i2c->Control |= (0x00000001U);
	/*
	 * Intrs keeps all the error-related interrupts.
	 */
	Intrs = (uint32_t)0x00000200U | (uint32_t)0x00000040U |
		(uint32_t)0x00000004U;

	/*
	 * Clear the interrupt status register before use it to monitor.
	 */
	IntrStatusReg = i2c->Intrpt_status;
    i2c->Intrpt_status = IntrStatusReg;

    i2c->Trans_size = length;
    i2c->address = SlaveAddr;

    Intrs = (0x00000200U|0x00000020U|0x00000080U|0x00000004U);

	IntrStatusReg =  i2c->Intrpt_status ;//XIicPs_ReadReg(BaseAddr, XIICPS_ISR_OFFSET);

    while( (!(i2c->Intrpt_status&&0x1)) )
    {
        
    }
    //fifo 16byte
    for (uint32_t i = 0; i < length; i++)
    {
        buf[i] = i2c->data;
    }
	if ((IntrStatusReg & Intrs) != 0U) {
		if (IntrStatusReg & 0x00000200U) {
			Result = -1;///(int) XST_IIC_ARB_LOST;
		} else {
			Result = -2;//(int)XST_FAILURE;
		}
	} else {
		Result = 0;//(int)XST_SUCCESS;
	}

	return Result;
}



static inline int i2c_master_transmit(I2C_TypeDef* i2c,uint32_t slave_addr,uint8_t* buf,uint32_t length)
{
    uint32_t intrpt_s;

    i2c->Control = 0x40;    //Set Direction of transfer as write and Clear the FIFOs.
    i2c->Control |=( (1<<1)|(1<<3)|(1<<2));    //Set Direction of transfer as write and Clear the FIFOs.
    intrpt_s = i2c->Intrpt_status; //Clear Interrupts
    i2c->Intrpt_status = intrpt_s;

    //fifo 16byte
    for (uint32_t i = 0; i < length; i++)
    {
        i2c->data = buf[i];
    }
    i2c->address = slave_addr;
    while((!(i2c->Intrpt_status&&0x1)))
    {
        if (i2c->Intrpt_status&&(1<<3))
        {
            while(1);
        }
        
    }
    while((!(i2c->Intrpt_status&&0x1)))
    {
        if (i2c->Intrpt_status&&(1<<3))
        {
            while(1);
        }
        
    }

    return 0;
    
}
static inline int i2c_master_receive(I2C_TypeDef* i2c,uint32_t slave_addr,uint8_t* buf,uint32_t length)
{
    i2c->Control = 0x40;    //Set direction of transfer as read and clear the FIFOs
    i2c->Control |=(1|(1<<1)|(1<<3)|(1<<2));
    uint32_t intrpt_s = i2c->Intrpt_status; //Clear Interrupts
    i2c->Intrpt_status = intrpt_s;
    i2c->Trans_size = length;
    i2c->address = slave_addr;
    while( (!(i2c->Intrpt_status&&0x1)) )
    {
        
    }
    //fifo 16byte
    for (uint32_t i = 0; i < length; i++)
    {
        buf[i] = i2c->data;
    }
    return 0;
}


int i2c0_write(uint32_t slave_addr,uint8_t* buf,uint32_t length)
{
    return XIicPs_MasterSendPolled(I2C0,slave_addr,buf,length,0);
    // return i2c_master_transmit(I2C0,slave_addr,buf,length);
}
int i2c0_read(uint32_t slave_addr,uint8_t* buf,uint32_t length)
{
    // return i2c_master_receive(I2C0,slave_addr,buf,length);
    return XIicPs_MasterRecvPolled(I2C0,buf,length,slave_addr);
}
int i2c1_write(uint32_t slave_addr,uint8_t* buf,uint32_t length)
{
    return XIicPs_MasterSendPolled(I2C1,slave_addr,buf,length,0);
    // return i2c_master_transmit(I2C0,slave_addr,buf,length);
}
int i2c1_read(uint32_t slave_addr,uint8_t* buf,uint32_t length)
{
    // return i2c_master_receive(I2C0,slave_addr,buf,length);
    return XIicPs_MasterRecvPolled(I2C1,buf,length,slave_addr);
}


i2c_dev_t i2c0 = {
    .id = 0,
    .i2c_wirte = i2c0_write,
    .i2c_read  = i2c0_read

};
i2c_dev_t i2c1 = {
    .id = 1,
    .i2c_wirte = i2c1_write,
    .i2c_read  = i2c1_read

};
extern void zynq_i2c_init();
void zynq_i2c_init()
{
    reset_iic();
    i2c_init(I2C0,100000);
    i2c_init(I2C1,100000);
    i2c_dev_attach(&i2c0);
    i2c_dev_attach(&i2c1);
}

