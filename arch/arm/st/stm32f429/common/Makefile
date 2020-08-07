SOURCES  =$(wildcard *.c) 
objs = $(patsubst %.c,%.o,$(SOURCES))

all:$(objs)

%.o:%.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$(PART_NO)-$@ $< -MD -MF $(BUILD_DIR)/$(PART_NO)-$@.d

