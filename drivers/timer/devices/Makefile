
objs-$(timer-stm32f429)+=timer-stm32f429.o
objs-$(timer-zynq)+=timer-zynq.o

SUBDIRS =


all:$(objs-y)


$(objs-y):$(SUBDIRS)


%.o:%.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $< -MD -MF $(BUILD_DIR)/$@.d


$(SUBDIRS):
	make -C $@