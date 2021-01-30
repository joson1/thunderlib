

objs-$(CONFIG_DMA_STM32F429)+=axi-dma.o
objs-$(CONFIG_DMA_ZYNQ7000)+=dma-zynq7000.o


SUBDIRS =


all:$(objs-y)


$(objs-y):$(SUBDIRS)


%.o:%.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $< -MD -MF $(BUILD_DIR)/$@.d


$(SUBDIRS):
	make -C $@