
# ifeq ($(OS),Windows_NT)     # is Windows_NT on XP, 2000, 7, Vista, 10...
#     # SHELL=cmd.exe
# TOPDIR = /thunderlib
# else
# endif

TOPDIR := $(PWD)


LIBDIR =
SDK_VERSION=v1.0
# -L$(TOPDIR)/libs/newlib-cygwin/arm-none-eabi/lib
# 		/c/GNU Tools ARM Embedded/5.4 2016q3/lib/gcc/arm-none-eabi/5.4.1
# LIBDIR = -L /c/GNU Tools ARM Embedded/5.4 2016q3/lib/gcc/arm-none-eabi/5.4.1 /c/GNU Tools ARM Embedded/5.4 2016q3/arm-none-eabi/lib
#export vars in .config


# ARCH 	:= $(CONFIG_ARCH)
# CPU 	:= $(CONFIG_CPU)
# MARCH 	:= $(CONFIG_MARCH)
# BOARD 	:= $(CONFIG_BOARD)

# ARCH := arm
# CPU := cortex-m4
# MARCH :=stm32f429
# BOARD := thunderboard32
ARCH := arm
CPU := cortex-a9
MARCH :=zynq7000
BOARD := magicboard


CFLAGS = -Wall
include $(TOPDIR)/arch/$(ARCH)/$(CPU)/$(MARCH)/configs/$(MARCH).mk



# C includes
C_INCLUDES +=  \
-I$(TOPDIR)/include \
-I$(TOPDIR)/arch/$(ARCH)/$(CPU)/include  \
-I$(TOPDIR)/arch/$(ARCH)/$(CPU)/include/$(MARCH) \
-I$(TOPDIR)/packages \


include $(TOPDIR)/packages/Makefile.pk


ifeq (.config, $(wildcard .config))
    #文件存在
	config_cmd := menuconfig %_defconfig
	ifeq ($(filter $(config_cmd), $(MAKECMDGOALS)),)
	include $(TOPDIR)/.config
	CONFIG_EXPORT_VARS=$(patsubst %=y, %,$(filter %=y, $(shell cat $(TOPDIR)/.config)))
	export $(CONFIG_EXPORT_VARS)
	endif
endif

CROSS_COMPILE :=$(CONFIG_CROSS_COMPILE)


# for libs
C_INCLUDES +=  \
-I$(TOPDIR)/libs/include \
-I$(TOPDIR) \


SZ = $(CROSS_COMPILE)size

OPT = -O0
CFLAGS+= $(C_INCLUDES)
CFLAGS+= -g -gdwarf-2
CFLAGS+= $(OPT)

TARGET = thunderlib-$(MARCH)-$(BOARD)
BUILD_DIR = $(TOPDIR)/build_dir
BIN_DIR = $(TOPDIR)/bin


SUBDIRS = 	$(TOPDIR)/arch/$(ARCH)/$(CPU)/$(MARCH)\
		 	$(TOPDIR)/arch \
			$(TOPDIR)/libs \
			$(TOPDIR)/drivers \
			$(TOPDIR)/kernel \
			$(PKDIRS-y) \
			$(TOPDIR)/app \
#mconfig
# include $(TOPDIR)/Makefile.common

KCONFIG_FILE_PATH=$(TOPDIR)/Kconfig
KCONFIG_SRC_PATH=$(TOPDIR)/scripts/kconfig-frontends
export TOPDIR  SDK_VERSION KCONFIG_FILE_PATH KCONFIG_SRC_PATH



export  CC CPP LD MARCH CFLAGS LDFLAGS TARGET CROSS_COMPILE
export BUILD_DIR BIN_DIR TOPDIR LINK_SCRIPT
export CPU ARCH MARCH BOARD
ALL:$(TARGET)
	$(OBJCOPY) -O binary -S $(BIN_DIR)/$(TARGET).elf $(BIN_DIR)/$(TARGET).bin
	$(OBJDUMP) -D $(BIN_DIR)/$(TARGET).elf > $(BIN_DIR)/$(TARGET).dis
	@echo  "\033[32mbuild success \033[0m"
	@$(SZ) $(BIN_DIR)/$(TARGET).elf -G


$(TARGET):$(SUBDIRS)
	make -C $(BUILD_DIR)

$(SUBDIRS):ECHO
	@-mkdir -p bin
	@echo "CONFIG_LINK_RAM_BASE = $(CONFIG_LINK_RAM_BASE);\r\nCONFIG_LINK_RAM_SIZE = $(CONFIG_LINK_RAM_SIZE);\r\nCONFIG_STACK_SIZE = $(CONFIG_STACK_SIZE);\r\nCONFIG_HEAP_SIZE = $(CONFIG_HEAP_SIZE);" > $(TOPDIR)/link.ld
	@cat $(LINK_SCRIPT) >> $(TOPDIR)/link.ld
	@python $(TOPDIR)/scripts/Kconfiglib/genconfig.py
	@make -C $@
ECHO:

.PHONY : clean
clean:
	-rm $(BUILD_DIR)/*.o $(BIN_DIR)/*
distclean: clean
	-rm $(BUILD_DIR)/*.d
	-rm $(BUILD_DIR)/*.map

# menuclean:
# 	cd $(KCONFIG_SRC_PATH) &&make distclean

# $(TOPDIR)/scripts/kconfig-frontends/frontends/mconf/%onf:
# 	cd $(KCONFIG_SRC_PATH) && ./configure  CFLAGS="" LDFLAGS="" && make


# menuconfig:$(TOPDIR)/scripts/kconfig-frontends/frontends/mconf/kconfig-mconf
# 	$< $(KCONFIG_FILE_PATH)


genconfig:
	@python $(TOPDIR)/scripts/Kconfiglib/genconfig.py

menuconfig-win:
	@cmd.exe /c start python $(TOPDIR)/scripts/Kconfiglib/menuconfig.py $(KCONFIG_FILE_PATH)
	

menuconfig:
	@python $(TOPDIR)/scripts/Kconfiglib/menuconfig.py $(KCONFIG_FILE_PATH)

# %_defconfig:$(TOPDIR)/scripts/kconfig-frontends/frontends/mconf/kconfig-mconf
# 	cp $(TOPDIR)/arch/$(ARCH)/$(CPU)/$(MARCH)/configs/$@ ./.config
# 	$< $(KCONFIG_FILE_PATH) 

%_defconfig:
	@cp $(TOPDIR)/arch/$(ARCH)/$(CPU)/$(MARCH)/configs/$@ ./.config


