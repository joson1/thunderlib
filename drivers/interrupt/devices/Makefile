
objs-$(CONFIG_INTERRUPT_STM32F429)+=interrupt-stm32f429.o
objs-$(CONFIG_INTERRUPT_ZYNQ7000)+=interrupt-zynq.o

SUBDIRS =


all:$(objs-y)


$(objs-y):$(SUBDIRS)


%.o:%.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $< -MD -MF $(BUILD_DIR)/$@.d


$(SUBDIRS):
	make -C $@