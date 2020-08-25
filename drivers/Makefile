

SUBDIRS +=serial
SUBDIRS +=interrupt
SUBDIRS +=gpio
SUBDIRS +=timer
SUBDIRS +=tty


all:$(SUBDIRS)

%.o:%.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $< -MD -MF $(BUILD_DIR)/$@.d


$(SUBDIRS):ECHO
	make -C $@

ECHO: