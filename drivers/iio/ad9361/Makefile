CSRCS += ad9361.c
CSRCS += ad9361_api.c
CSRCS += ad9361_conv.c
CSRCS += util.c
CSRCS += platform.c

VPATH += :$(TOPDIR)/drivers/iio/ad9361/AD9361
VPATH += :$(TOPDIR)/drivers/iio/ad9361/Platform_Generic


CFLAGS += "-I$(TOPDIR)/drivers/iio/ad9361/AD9361"
CFLAGS += "-I$(TOPDIR)/drivers/iio/ad9361/Platform_Generic"

objs = $(patsubst %.c,%.o,$(CSRCS))

all:$(objs)

%.o:%.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $< -MD -MF $(BUILD_DIR)/$@.d




