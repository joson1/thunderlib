VPATH += :$(LVGL_DIR)/$(LVGL_DIR_NAME)/examples


LVGL_DIR = $(TOPDIR)/packages/gui
LVGL_DIR_NAME = lvgl
include lvgl.mk

CFLAGS += -DCONFIG_LV_CONF_SKIP
objs = $(patsubst %.c,%.o,$(CSRCS))

objs+= lvgl_test.o

all:$(objs)

%.o:%.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $< -MD -MF $(BUILD_DIR)/$@.d


