
ARCH := arm
VENDOR := st
PART_NO := stm32f429
BOARD := thunderboard32

TOPDIR := $(PWD)
LIBDIR =
# -L$(TOPDIR)/libs/newlib-cygwin/arm-none-eabi/lib
# 		/c/GNU Tools ARM Embedded/5.4 2016q3/lib/gcc/arm-none-eabi/5.4.1
# LIBDIR = -L /c/GNU Tools ARM Embedded/5.4 2016q3/lib/gcc/arm-none-eabi/5.4.1 /c/GNU Tools ARM Embedded/5.4 2016q3/arm-none-eabi/lib

CFLAGS = -Wall
include $(TOPDIR)/arch/$(ARCH)/$(VENDOR)/configs/$(PART_NO)/$(PART_NO).mk
include $(TOPDIR)/arch/$(ARCH)/$(VENDOR)/configs/$(PART_NO)/$(BOARD).mk

# C includes
C_INCLUDES +=  \
-I$(TOPDIR)/include \
-I$(TOPDIR)/arch/$(ARCH)/$(VENDOR)/include \



CFLAGS+= $(C_INCLUDES)
CFLAGS+= -g -gdwarf-2
CFLAGS+= $(OPT)

TARGET = thunderlib-$(VENDOR)-$(PART_NO)-$(BOARD)
BUILD_DIR = $(TOPDIR)/build_dir
BIN_DIR = $(TOPDIR)/bin


export CC LD MARCH CFLAGS LDFLAGS TARGET
export BUILD_DIR BIN_DIR TOPDIR LINK_SCRIPT
export PART_NO
ALL:$(TARGET)
	$(OBJCOPY) -O binary -S $(BIN_DIR)/$(TARGET).elf $(BIN_DIR)/$(TARGET).bin
	$(OBJDUMP) -D $(BIN_DIR)/$(TARGET).elf > $(BIN_DIR)/$(TARGET).dis
	@echo -e "\033[32mbuild success \033[0m"
	@ls $(BIN_DIR)/ -l



$(TARGET):$(SUBDIRS)
	make -C $(BUILD_DIR)

$(SUBDIRS):ECHO
	make -C $@
ECHO:

.PHONY : clean
clean:
	rm $(BUILD_DIR)/*.o $(BIN_DIR)/*
distclean: clean
	rm $(BUILD_DIR)/*.d
	rm $(BUILD_DIR)/*.map