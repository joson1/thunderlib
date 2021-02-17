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


LIBS = -lc -lm -lnosys
# CPU = -mcpu=cortex-m4
FPU = -mfpu=fpv4-sp-d16
FLOAT-ABI = -mfloat-abi=hard 
MCU = -mcpu=$(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# C defines
C_DEFS =  \
-DSTM32F429xx

CFLAGS+= $(MCU) $(C_DEFS) $(OPT)


LDFLAGS = -specs=nano.specs $(MCU) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

C_INCLUDES+= -I$(TOPDIR)/arch/$(ARCH)/$(VENDOR)/include/CMSIS



AS		= $(CROSS_COMPILE)as
LD		= $(CROSS_COMPILE)ld
CC		= $(CROSS_COMPILE)gcc
CPP		= $(CC) -E
AR		= $(CROSS_COMPILE)ar
NM		= $(CROSS_COMPILE)nm
STRIP		= $(CROSS_COMPILE)strip
OBJCOPY		= $(CROSS_COMPILE)objcopy
OBJDUMP		= $(CROSS_COMPILE)objdump


# SUBDIRS = 	$(TOPDIR)/arch/$(ARCH)/$(VENDOR)/$(PART_NO) \
# 			$(TOPDIR)/app \
# 			$(TOPDIR)/drivers 

LINK_SCRIPT := $(TOPDIR)/arch/$(ARCH)/$(VENDOR)/$(PART_NO)/$(LINK_SCRIPT)
# export CC LD MARCH CFLAGS LDFLAGS TARGET
# export BUILD_DIR BIN_DIR TOPDIR LINK_SCRIPT
# export PART_NO