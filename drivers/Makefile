

SUBDIRS +=bus
SUBDIRS +=sleep
SUBDIRS +=interrupt
SUBDIRS +=gpio
SUBDIRS +=timer
SUBDIRS +=tty
SUBDIRS +=mtd


all:$(SUBDIRS)

%.o:%.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $< -MD -MF $(BUILD_DIR)/$@.d


$(SUBDIRS):ECHO
	make -C $@

ECHO: