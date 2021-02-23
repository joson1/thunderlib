


SUBDIRS-$(CONFIG_AT24CXX) +=at24cxx
SUBDIRS-$(CONFIG_SPI_FLASH) +=spi-falsh


all:$(SUBDIRS-y)

%.o:%.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $< -MD -MF $(BUILD_DIR)/$@.d


$(SUBDIRS-y):ECHO
	make -C $@

ECHO: