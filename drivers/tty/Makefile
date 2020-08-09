
objs-$(tty)+=ttyio.o
objs-$(tty)+=tty.o
objs-$(tty)+=sysfuncs.o


SUBDIRS =


all:$(objs-y)


$(objs-y):$(SUBDIRS)


%.o:%.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $< -MD -MF $(BUILD_DIR)/$@.d


$(SUBDIRS):
	make -C $@