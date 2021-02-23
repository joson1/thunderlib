
# objs-$(spi-flash)+=spi-flash.o

objs-y+=spi-flash.o
all:$(objs-y)


%.o:%.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $< -MD -MF $(BUILD_DIR)/$@.d

