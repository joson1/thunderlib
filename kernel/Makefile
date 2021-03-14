

objs-$(CONFIG_KERNEL_EN)+=klist.o
objs-$(CONFIG_KERNEL_EN)+=kops.o
objs-$(CONFIG_KERNEL_EN)+=thread.o
objs-$(CONFIG_KERNEL_EN)+=scheduler.o
objs-$(CONFIG_KERNEL_EN)+=kernel.o
objs-$(CONFIG_KERNEL_EN)+=k-zynq.o

VPATH+=$(TOPDIR)/kernel/platform


all:$(objs-y)


%.o:%.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $< -MD -MF $(BUILD_DIR)/$@.d


$(SUBDIRS):
	make -C $@