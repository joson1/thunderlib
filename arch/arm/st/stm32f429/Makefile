objs += init.o
objs += startup_stm32f429xx.o
objs += stm32f429-gpio.o
objs += stm32f429-usart.o


all:$(objs)


%.o:%.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $< -MD -MF $(BUILD_DIR)/$@.d

%.o:%.s
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $< -MD -MF $(BUILD_DIR)/$@.d