
objs+=pinmux.o
SUBDIRS =	\
		devices

all:$(SUBDIRS)


$(SUBDIRS):$(objs)


%.o:%.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $< -MD -MF $(BUILD_DIR)/$@.d


$(SUBDIRS):
	make -C $@