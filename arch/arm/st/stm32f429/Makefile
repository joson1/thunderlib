objs += startup_stm32f429xx.o

all:$(objs)

%.o:%.s
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $<