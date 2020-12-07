

SOURCES  =$(wildcard *.c) 

objs += boot.o
objs += asm_vectors.o
objs += cpu_init.o
objs += xil-crt0.o
objs += translation_table.o
objs += contex_rvds.o


objs += $(patsubst %.c,%.o,$(SOURCES))

SUBDIRS = boards

all:$(SUBDIRS)


$(SUBDIRS):$(objs)

%.o:%.c
	echo CF:$(CFLAGS) $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$(PART_NO)-$@ $< -MD -MF $(BUILD_DIR)/$(PART_NO)-$@.d

%.o:%.S
	echo CF:$(CFLAGS) $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$(PART_NO)-$@ $< -MD -MF $(BUILD_DIR)/$(PART_NO)-$@.d

$(SUBDIRS):
	make -C $@
