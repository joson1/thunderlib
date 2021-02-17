
objs-$(CONFIG_TTY_EN)+=ttyio.o
objs-$(CONFIG_TTY_EN)+=tty.o
objs-$(CONFIG_TTY_EN)+=sysfuncs.o


SUBDIRS =


all:$(objs-y)


$(objs-y):$(SUBDIRS)


%.o:%.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $< -MD -MF $(BUILD_DIR)/$@.d


$(SUBDIRS):
	make -C $@