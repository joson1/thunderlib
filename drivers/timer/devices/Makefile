
objs-$(CONFIG_TIMER_STM32F429)+=timer-stm32f429.o
objs-$(CONFIG_TIMER_ZYNQ7000)+=timer-zynq.o

SUBDIRS =


all:$(objs-y)


$(objs-y):$(SUBDIRS)


%.o:%.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $< -MD -MF $(BUILD_DIR)/$@.d


$(SUBDIRS):
	make -C $@