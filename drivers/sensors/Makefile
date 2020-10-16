


SUBDIRS +=at24cxx
SUBDIRS +=spi-falsh


all:$(SUBDIRS)

%.o:%.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $< -MD -MF $(BUILD_DIR)/$@.d


$(SUBDIRS):ECHO
	make -C $@

ECHO: