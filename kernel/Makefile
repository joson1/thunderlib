

objs-$(CONFIG_KERNEL_EN)+=klist.o
objs-$(CONFIG_KERNEL_EN)+=kops.o
objs-$(CONFIG_KERNEL_EN)+=thread.o
objs-$(CONFIG_KERNEL_EN)+=scheduler.o
objs-$(CONFIG_KERNEL_EN)+=kernel.o
objs-$(CONFIG_KERNEL_ZYNQ7000)+=k-zynq7000.o
objs-$(CONFIG_KERNEL_STM32F429)+=k-stm32f429.o

VPATH+=$(TOPDIR)/kernel/platform


all:$(objs-y)


%.o:%.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $< -MD -MF $(BUILD_DIR)/$@.d


$(SUBDIRS):
	make -C $@