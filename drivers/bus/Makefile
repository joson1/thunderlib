

SUBDIRS +=i2c
SUBDIRS +=serial

all:$(SUBDIRS)

%.o:%.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $< -MD -MF $(BUILD_DIR)/$@.d


$(SUBDIRS):ECHO
	make -C $@

ECHO: