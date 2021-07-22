
objs =$(wildcard *.o) 
dep = $(wildcard *.d)
LDFLAGS+=-u_printf_float -lstdc++

# LDFLAGS+=-u_printf_float
all:
	@echo Linking
	$(CC) -T $(TOPDIR)/link.ld  $(objs) -o $(BIN_DIR)/$(TARGET).elf $(LDFLAGS) 

ifneq ($(dep),)
include $(dep)
endif
