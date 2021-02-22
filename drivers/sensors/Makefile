


SUBDIRS-$(CONFIG_US015) +=us015


all:$(SUBDIRS-y)

%.o:%.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $< -MD -MF $(BUILD_DIR)/$@.d


$(SUBDIRS-y):ECHO
	make -C $@

ECHO: