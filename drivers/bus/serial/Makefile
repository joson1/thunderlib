
objs-$(CONFIG_SERIAL_EN)+=serial.o
objs-$(CONFIG_SERIAL_EN)+=serial-irq.o

SUBDIRS =	\
		devices

all:$(SUBDIRS)


$(SUBDIRS):$(objs-y)


%.o:%.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $< -MD -MF $(BUILD_DIR)/$@.d


$(SUBDIRS):
	make -C $@