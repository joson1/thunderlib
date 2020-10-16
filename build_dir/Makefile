
objs =$(wildcard *.o) 
dep = $(wildcard *.d)

all:
	@echo Linking
	$(CC) -T $(LINK_SCRIPT)  $(objs) -o $(BIN_DIR)/$(TARGET).elf $(LDFLAGS)

ifneq ($(dep),)
include $(dep)
endif
