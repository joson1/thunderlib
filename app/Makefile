objs += main.o

all:$(objs)
	@echo leaving

%.o:%.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $<