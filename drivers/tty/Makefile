
objs+=ttyio.o
objs+=tty.o
objs+=sysfuncs.o


SUBDIRS =


all:$(objs)


$(objs):$(SUBDIRS)


%.o:%.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $< -MD -MF $(BUILD_DIR)/$@.d


$(SUBDIRS):
	make -C $@