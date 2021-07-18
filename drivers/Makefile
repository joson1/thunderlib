


objs+=device.o

SUBDIRS-y +=pinmux
SUBDIRS-y +=bus
SUBDIRS-y +=sleep
SUBDIRS-$(CONFIG_INTERRUPT_EN) +=interrupt
SUBDIRS-$(CONFIG_DMA_EN) +=dma

SUBDIRS-$(CONFIG_GPIO_EN) +=gpio
SUBDIRS-$(CONFIG_PWM_EN) +=pwm
SUBDIRS-$(CONFIG_TIMER_EN) +=timer
SUBDIRS-$(CONFIG_TTY_EN) +=tty
SUBDIRS-$(CONFIG_FB_EN) +=video
SUBDIRS-y +=input
SUBDIRS-y +=mtd
SUBDIRS-y +=sensors
SUBDIRS-$(CONFIG_IIO_EN) +=iio



all:$(objs)

$(objs):$(SUBDIRS-y)

%.o:%.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $< -MD -MF $(BUILD_DIR)/$@.d


$(SUBDIRS-y):ECHO
	make -C $@

ECHO: