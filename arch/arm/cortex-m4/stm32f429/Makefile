objs += systemInit.o
objs += startup_stm32f429xx.o


SUBDIRS = common \
		boards

all:$(SUBDIRS)

$(SUBDIRS):$(objs)


%.o:%.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$(MARCH)-$@ $< -MD -MF $(BUILD_DIR)/$(MARCH)-$@.d

%.o:%.s
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$(MARCH)-$@ $< -MD -MF $(BUILD_DIR)/$(MARCH)-$@.d

$(SUBDIRS):
	make -C $@
