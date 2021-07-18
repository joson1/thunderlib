
SUBDIRS-$(CONFIG_GUI_LVGL) +=lvgl
SUBDIRS-$(CONFIG_GUI_GUILITE) +=guilite


all:$(SUBDIRS-y)



$(SUBDIRS-y):ECHO
	make -C $@

ECHO:


%.o:%.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $< -MD -MF $(BUILD_DIR)/$@.d
