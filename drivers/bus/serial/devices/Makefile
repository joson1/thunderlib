
objs-$(CONFIG_SERIAL_STM32F429)+=serial-stm32f429.o
objs-$(CONFIG_SERIAL_ZYNQ)+=serial-zynq.o

SUBDIRS =


all:$(objs-y)


$(objs-y):$(SUBDIRS)


%.o:%.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $< -MD -MF $(BUILD_DIR)/$@.d


$(SUBDIRS):
	make -C $@