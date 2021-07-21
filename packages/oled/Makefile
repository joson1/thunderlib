objs+=oled.o
objs+=ssd1306.o










all:$(objs)

%.o:%.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $< -MD -MF $(BUILD_DIR)/$@.d

%.o:%.cpp
	$(CPP) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $< -MD -MF $(BUILD_DIR)/$@.d



