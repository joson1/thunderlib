# ARCH := arm
# CROSS_COMPILE := arm-none-eabi-
# CFLAGS = -Wall

# OPT = -O0

# VENDOR := st
# PART_NO := stm32f429
LINK_SCRIPT := STM32F429IGTx_FLASH.ld

TOPDIR := $(PWD)
LIBDIR =
# -L$(TOPDIR)/libs/newlib-cygwin/arm-none-eabi/lib
# 		/c/GNU Tools ARM Embedded/5.4 2016q3/lib/gcc/arm-none-eabi/5.4.1
# LIBDIR = -L /c/GNU Tools ARM Embedded/5.4 2016q3/lib/gcc/arm-none-eabi/5.4.1 /c/GNU Tools ARM Embedded/5.4 2016q3/arm-none-eabi/lib

CONFIG_LINK_RAM_BASE:=0x20000000
CONFIG_LINK_RAM_SIZE:=192k

LIBS = -lc -lm -lnosys
# CPU = -mcpu=cortex-m4
FPU = -mfpu=fpv4-sp-d16
FLOAT-ABI = -mfloat-abi=hard 
MCU = -mcpu=$(CPU) -Wa,-mimplicit-it=thumb $(FPU) $(FLOAT-ABI)

# C defines
C_DEFS =  \
-DSTM32F429xx

CFLAGS+= $(MCU) $(C_DEFS) $(OPT)


LDFLAGS = -specs=nano.specs $(MCU) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

C_INCLUDES+= -I$(TOPDIR)/arch/$(ARCH)/$(CPU)/include/CMSIS





AS		= $(CROSS_COMPILE)as
LD		= $(CROSS_COMPILE)ld 
CC		= $(CROSS_COMPILE)gcc
CPP		= $(CROSS_COMPILE)gcc -lstdc++
AR		= $(CROSS_COMPILE)ar
NM		= $(CROSS_COMPILE)nm
STRIP		= $(CROSS_COMPILE)strip
OBJCOPY		= $(CROSS_COMPILE)objcopy
OBJDUMP		= $(CROSS_COMPILE)objdump


# SUBDIRS = 	$(TOPDIR)/arch/$(ARCH)/$(VENDOR)/$(PART_NO) \
# 			$(TOPDIR)/app \
# 			$(TOPDIR)/drivers 

LINK_SCRIPT := $(TOPDIR)/arch/$(ARCH)/$(CPU)/$(MARCH)/$(LINK_SCRIPT)
# export CC LD MARCH CFLAGS LDFLAGS TARGET
# export BUILD_DIR BIN_DIR TOPDIR LINK_SCRIPT
# export PART_NO
