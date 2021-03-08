
objs-$(CONFIG_FB_EN)+=fb_dev.o
objs-$(CONFIG_FB_EN)+=fbmm.o


SUBDIRS = devices


all:$(SUBDIRS)


$(SUBDIRS):$(objs-y)


%.o:%.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $< -MD -MF $(BUILD_DIR)/$@.d


$(SUBDIRS):
	make -C $@
