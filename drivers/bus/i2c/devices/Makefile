
objs-$(CONFIG_I2C_STM32F429)+=i2c-stm32f429.o
objs-$(CONFIG_SI2C_EN)+=i2c-soft.o
objs-$(CONFIG_I2C_ZYNQ)+=i2c-zynq.o

SUBDIRS =


all:$(objs-y)


$(objs-y):$(SUBDIRS)


%.o:%.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $< -MD -MF $(BUILD_DIR)/$@.d


$(SUBDIRS):
	make -C $@