
objs-$(CONFIG_SPI_ZYNQ)+=spi-zynq.o
objs-$(CONFIG_SPI_STM32F429)+=spi-stm32f429.o


SUBDIRS =


all:$(objs-y)


$(objs-y):$(SUBDIRS)


%.o:%.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $< -MD -MF $(BUILD_DIR)/$@.d


$(SUBDIRS):
	make -C $@