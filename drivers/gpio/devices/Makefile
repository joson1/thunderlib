
objs-$(CONFIG_GPIO_STM32F429)+=gpio-stm32f429.o
objs-$(CONFIG_GPIO_ZYNQ7000)+=gpio-zynq.o

SUBDIRS =


all:$(objs-y)


$(objs-y):$(SUBDIRS)


%.o:%.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $< -MD -MF $(BUILD_DIR)/$@.d


$(SUBDIRS):
	make -C $@