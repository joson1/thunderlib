

SOURCES  =$(wildcard *.c) 

objs += boot.o
objs += asm_vectors.o
objs += cpu_init.o
objs += xil-crt0.o
objs += translation_table.o

objs += $(patsubst %.c,%.o,$(SOURCES))


all:$(objs)


%.o:%.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$(PART_NO)-$@ $< -MD -MF $(BUILD_DIR)/$(PART_NO)-$@.d

%.o:%.s
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$(PART_NO)-$@ $< -MD -MF $(BUILD_DIR)/$(PART_NO)-$@.d

