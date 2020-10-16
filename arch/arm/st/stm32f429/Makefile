objs += init.o
objs += startup_stm32f429xx.o


SUBDIRS = common \
		boards

all:$(SUBDIRS)

$(SUBDIRS):$(objs)


%.o:%.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$(PART_NO)-$@ $< -MD -MF $(BUILD_DIR)/$(PART_NO)-$@.d

%.o:%.s
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$(PART_NO)-$@ $< -MD -MF $(BUILD_DIR)/$(PART_NO)-$@.d

$(SUBDIRS):
	make -C $@
