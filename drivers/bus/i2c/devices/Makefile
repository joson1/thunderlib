
objs-$(i2c-stm32f429)+=i2c-stm32f429.o
objs-$(i2c-zynq)+=i2c-zynq.o

SUBDIRS =


all:$(objs-y)


$(objs-y):$(SUBDIRS)


%.o:%.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $< -MD -MF $(BUILD_DIR)/$@.d


$(SUBDIRS):
	make -C $@