SOURCES  =$(wildcard *.c) 



objs += $(patsubst %.c,%.o,$(SOURCES))


all:$(objs)


%.o:%.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$(MARCH)-$@ $< -MD -MF $(BUILD_DIR)/$(MARCH)-$@.d

%.o:%.S
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$(MARCH)-$@ $< -MD -MF $(BUILD_DIR)/$(MARCH)-$@.d

