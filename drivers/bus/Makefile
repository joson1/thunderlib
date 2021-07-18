

SUBDIRS-$(CONFIG_I2C_EN) +=i2c
SUBDIRS-$(CONFIG_SERIAL_EN) +=serial
SUBDIRS-$(CONFIG_SPI_EN) +=spi

all:$(SUBDIRS-y)

%.o:%.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $< -MD -MF $(BUILD_DIR)/$@.d


$(SUBDIRS-y):ECHO
	make -C $@

ECHO: