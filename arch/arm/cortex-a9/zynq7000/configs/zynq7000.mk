# ARCH := arm
# CROSS_COMPILE := arm-none-eabi-
# CFLAGS = -Wall

LINK_SCRIPT := lscript.ld

TOPDIR := $(PWD)
LIBDIR = -L$(TOPDIR)/arch/$(ARCH)/$(VENDOR)/$(PART_NO)

# 		/c/GNU Tools ARM Embedded/5.4 2016q3/lib/gcc/arm-none-eabi/5.4.1
# LIBDIR = -L /c/GNU Tools ARM Embedded/5.4 2016q3/lib/gcc/arm-none-eabi/5.4.1 /c/GNU Tools ARM Embedded/5.4 2016q3/arm-none-eabi/lib


LIBS = -lc -lm 
# CPU = cortex-a9
FPU = -mfpu=vfpv3
FLOAT-ABI = -mfloat-abi=hard
MCU = -mcpu=$(CPU) $(FPU) $(FLOAT-ABI)

# C defines
C_DEFS =  \

C_INCLUDES += 

CFLAGS+= $(MCU) $(C_DEFS) $(OPT)


LDFLAGS = -specs=$(TOPDIR)/arch/$(ARCH)/$(CPU)/$(MARCH)/Xilinx.spec  -specs=nosys.specs $(MCU) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map

AS		= $(CROSS_COMPILE)as
LD		= $(CROSS_COMPILE)ld
CC		= $(CROSS_COMPILE)gcc
CPP		= $(CC) -E
AR		= $(CROSS_COMPILE)ar
NM		= $(CROSS_COMPILE)nm
STRIP		= $(CROSS_COMPILE)strip
OBJCOPY		= $(CROSS_COMPILE)objcopy
OBJDUMP		= $(CROSS_COMPILE)objdump


LINK_SCRIPT := $(TOPDIR)/arch/$(ARCH)/$(CPU)/$(MARCH)/$(LINK_SCRIPT)
# export CC LD MARCH CFLAGS LDFLAGS TARGET
# export BUILD_DIR BIN_DIR TOPDIR LINK_SCRIPT
# export PART_NO
