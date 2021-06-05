


objs+=device.o

SUBDIRS +=pinmux
SUBDIRS +=bus
SUBDIRS +=sleep
SUBDIRS +=interrupt
SUBDIRS +=dma

SUBDIRS +=gpio
SUBDIRS +=pwm
SUBDIRS +=timer
SUBDIRS +=tty
SUBDIRS +=video
SUBDIRS +=input
SUBDIRS +=mtd
SUBDIRS +=sensors



all:$(objs)

$(objs):$(SUBDIRS)

%.o:%.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $< -MD -MF $(BUILD_DIR)/$@.d


$(SUBDIRS):ECHO
	make -C $@

ECHO: