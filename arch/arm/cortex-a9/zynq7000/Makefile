

SOURCES  =$(wildcard *.c) 

objs += boot.o
objs += asm_vectors.o
objs += cp15_gcc.o
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
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$(MARCH)-$@ $< -MD -MF $(BUILD_DIR)/$(MARCH)-$@.d

%.o:%.S
	echo CF:$(CFLAGS) $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$(MARCH)-$@ $< -MD -MF $(BUILD_DIR)/$(MARCH)-$@.d

$(SUBDIRS):
	make -C $@
