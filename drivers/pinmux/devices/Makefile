
objs-$(PIN_MUX_STM32F429)+=pinmux-stm32f429.o
SUBDIRS =


all:$(objs-y)


$(objs-y):$(SUBDIRS)


%.o:%.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $< -MD -MF $(BUILD_DIR)/$@.d


$(SUBDIRS):
	make -C $@