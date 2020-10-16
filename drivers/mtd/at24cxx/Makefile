
objs-$(at24cxx)+=at24cxx.o


all:$(objs-y)


%.o:%.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $< -MD -MF $(BUILD_DIR)/$@.d

