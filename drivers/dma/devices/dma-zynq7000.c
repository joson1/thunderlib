#include "zynq7000/xdmaps.h"
#include <thunder/dma.h>
#include <thunder/irq.h>





XDmaPs DmaInstance;
extern XDmaPs DmaInstance;

XDmaPs_Config *DmaCfg;
extern XDmaPs_Config *DmaCfg;
extern int zynq_dma_start(uint8_t ch, uint32_t dst,uint32_t src,uint32_t nBrOfBytes);
int zynq_dma_start(uint8_t ch, uint32_t dst,uint32_t src,uint32_t nBrOfBytes)
{

	int Status;

	XDmaPs *DmaInst = &DmaInstance;
	XDmaPs_Cmd DmaCmd;

	memset(&DmaCmd, 0, sizeof(XDmaPs_Cmd));

	DmaCmd.ChanCtrl.SrcBurstSize = 4;
	DmaCmd.ChanCtrl.SrcBurstLen = 4;
	DmaCmd.ChanCtrl.SrcInc = 1;
	DmaCmd.ChanCtrl.DstBurstSize = 4;
	DmaCmd.ChanCtrl.DstBurstLen = 4;
	DmaCmd.ChanCtrl.DstInc = 1;
	DmaCmd.BD.SrcAddr = (u32) src;
	DmaCmd.BD.DstAddr = (u32) dst;
	DmaCmd.BD.Length = nBrOfBytes;


    Status = XDmaPs_Start(DmaInst, ch, &DmaCmd, 0);
    if (Status != XST_SUCCESS) {
        return XST_FAILURE;
    }



}

void dma0_start(uint32_t dst,uint32_t src,uint32_t nBrOfBytes)
{
    zynq_dma_start(0,dst,src,nBrOfBytes);
    
}

dmac_dev_t dmac0 = {
    .id = 0,
    .isLocked = 0,
    .start = dma0_start

};

void dma1_start(uint32_t dst,uint32_t src,uint32_t nBrOfBytes)
{
    zynq_dma_start(1,dst,src,nBrOfBytes);
    
}
dmac_dev_t dmac1 = {
    .id = 1,
    .isLocked = 0,
    .start = dma1_start

};


void dma2_start(uint32_t dst,uint32_t src,uint32_t nBrOfBytes)
{
    zynq_dma_start(2,dst,src,nBrOfBytes);
    
}
dmac_dev_t dmac2 = {
    .id = 2,
    .isLocked = 0,
    .start = dma2_start

};

void dma3_start(uint32_t dst,uint32_t src,uint32_t nBrOfBytes)
{
    zynq_dma_start(3,dst,src,nBrOfBytes);
    
}
dmac_dev_t dmac3 = {
    .id = 3,
    .isLocked = 0,
    .start = dma3_start

};

void dma4_start(uint32_t dst,uint32_t src,uint32_t nBrOfBytes)
{
    zynq_dma_start(4,dst,src,nBrOfBytes);
    
}
dmac_dev_t dmac4 = {
    .id = 4,
    .isLocked = 0,
    .start = dma4_start

};

void dma5_start(uint32_t dst,uint32_t src,uint32_t nBrOfBytes)
{
    zynq_dma_start(5,dst,src,nBrOfBytes);
    
}
dmac_dev_t dmac5 = {
    .id = 5,
    .isLocked = 0,
    .start = dma5_start

};

void dma6_start(uint32_t dst,uint32_t src,uint32_t nBrOfBytes)
{
    zynq_dma_start(6,dst,src,nBrOfBytes);
    
}
dmac_dev_t dmac6 = {
    .id = 6,
    .isLocked = 0,
    .start = dma6_start

};

void dma7_start(uint32_t dst,uint32_t src,uint32_t nBrOfBytes)
{
    zynq_dma_start(7,dst,src,nBrOfBytes);
    
}
dmac_dev_t dmac7 = {
    .id = 7,
    .isLocked = 0,
    .start = dma7_start

};
void zynq7000_dma_init()
{
	int Status;

	/*
	 * Initialize the DMA Driver
	 */
	DmaCfg = XDmaPs_LookupConfig(1);
	if (DmaCfg == NULL) {
		return XST_FAILURE;
	}

	Status = XDmaPs_CfgInitialize(&DmaInstance,
				   DmaCfg,
				   DmaCfg->BaseAddress);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
    irq_register(XPAR_XDMAPS_0_DONE_INTR_0,XDmaPs_DoneISR_0,TRIGGER_EDGE_HIGHLEVEL,&DmaInstance,0);
    irq_register(XPAR_XDMAPS_0_DONE_INTR_1,XDmaPs_DoneISR_1,TRIGGER_EDGE_HIGHLEVEL,&DmaInstance,0);
    irq_register(XPAR_XDMAPS_0_DONE_INTR_2,XDmaPs_DoneISR_2,TRIGGER_EDGE_HIGHLEVEL,&DmaInstance,0);
    irq_register(XPAR_XDMAPS_0_DONE_INTR_3,XDmaPs_DoneISR_3,TRIGGER_EDGE_HIGHLEVEL,&DmaInstance,0);
    irq_register(XPAR_XDMAPS_0_DONE_INTR_4,XDmaPs_DoneISR_4,TRIGGER_EDGE_HIGHLEVEL,&DmaInstance,0);
    irq_register(XPAR_XDMAPS_0_DONE_INTR_5,XDmaPs_DoneISR_5,TRIGGER_EDGE_HIGHLEVEL,&DmaInstance,0);
    irq_register(XPAR_XDMAPS_0_DONE_INTR_6,XDmaPs_DoneISR_6,TRIGGER_EDGE_HIGHLEVEL,&DmaInstance,0);
    irq_register(XPAR_XDMAPS_0_DONE_INTR_7,XDmaPs_DoneISR_7,TRIGGER_EDGE_HIGHLEVEL,&DmaInstance,0);
    dmac_dev_attach(&dmac0);
    dmac_dev_attach(&dmac1);
    dmac_dev_attach(&dmac2);
    dmac_dev_attach(&dmac3);
    dmac_dev_attach(&dmac4);
    dmac_dev_attach(&dmac5);
    dmac_dev_attach(&dmac6);
    dmac_dev_attach(&dmac7);


}
extern void zynq7000_dma_init();

extern void (__dma_interrupt_register)(uint8_t ch,void* handler);    

void __dma_interrupt_register(uint8_t ch,void* handler)
{
			XDmaPs_SetDoneHandler(&DmaInstance,
					       ch,
					       handler,
					       0);
}
