#include "../lvgl.h"
#include <thunder/fb.h>
#include <thunder/sleep.h>
#include <thunder/timer.h>

// TFT_eSPI tft = TFT_eSPI(); /* TFT instance */
struct fb_info *fb;

static lv_disp_buf_t disp_buf;
static lv_color_t buf[LV_HOR_RES_MAX * 10];

#if USE_LV_LOG != 0
/* Serial debugging */
void my_print(lv_log_level_t level, const char *file, uint32_t line, const char *dsc)
{

    Serial.printf("%s@%d->%s\r\n", file, line, dsc);
    Serial.flush();
}
#endif

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t pos;

    struct fb_image image={
        .dx=area->x1,		/* Where to place image */
        .dy=area->y1,
        .width=(area->x2 - area->x1 + 1),		/* Size of image */
        .height=(area->y2 - area->y1 + 1),
        .data=(uint16_t*)color_p,	/* Pointer to image data */
    };

    fb->fbops->fb_imageblit(fb,&image);

    lv_disp_flush_ready(disp);
}

/*Read the touchpad*/
bool my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
    //uint16_t touchX, touchY;

    //bool touched = tft.getTouch(&touchX, &touchY, 600);

    // if(!touched) {
    //   data->state = LV_INDEV_STATE_REL;
    // } else {
    //   data->state = LV_INDEV_STATE_PR;

    //   /*Set the coordinates*/
    //   data->point.x = touchX;
    //   data->point.y = touchY;

    //   Serial.print("Data x");
    //   Serial.println(touchX);

    //   Serial.print("Data y");
    //   Serial.println(touchY);
    // }

    return false; /*Return `false` because we are not buffering and no more data to read*/
}

//按钮回调函数
static void event_handler(lv_obj_t *btn, lv_event_t event)
{

    if (event == LV_EVENT_CLICKED)
    {
        static uint8_t cnt = 0;
        cnt++;

        /*Get the first child of the button which is the label and change its text*/
        lv_obj_t *label = lv_obj_get_child(btn, NULL);
        lv_label_set_text_fmt(label, "Button: %d", cnt);
    }
}

void tmr_handler()
{
    lv_tick_inc(5);
}

void setup()
{
    // Serial.begin(115200); /* prepare for possible serial debug */
    fb = fb_open(0);
    lv_init();

    timer_setup(0, 5, 4, tmr_handler);

    lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * 10);

    /*Initialize the display*/
    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = fb->var.xres;
    disp_drv.ver_res = fb->var.yres;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.buffer = &disp_buf;
    lv_disp_drv_register(&disp_drv);

    /*Initialize the (dummy) input device driver*/
    // lv_indev_drv_t indev_drv;
    // lv_indev_drv_init(&indev_drv);
    // indev_drv.type = LV_INDEV_TYPE_POINTER;
    // indev_drv.read_cb = my_touchpad_read;
    // lv_indev_drv_register(&indev_drv);

    /* Try an example from the lv_examples repository
		 * https://github.com/lvgl/lv_examples*/
    // lv_ex_btn_1();
    // lv_obj_t *label;

    // lv_obj_t *btn1 = lv_btn_create(lv_scr_act(), NULL);
    // lv_obj_set_event_cb(btn1, event_handler); //按钮按下回调函数，可以不用设置，可以多按钮同一个回调函数
    // lv_obj_align(btn1, NULL, LV_ALIGN_CENTER, 0, -40);

    // label = lv_label_create(btn1, NULL);
    // lv_label_set_text(label, "Button");
    lv_obj_t * btn = lv_btn_create(lv_scr_act(), NULL);     /*Add a button the current screen*/
    lv_obj_set_pos(btn, 10, 10);                            /*Set its position*/
    lv_obj_set_size(btn, 120, 50);                          /*Set its size*/
    lv_obj_set_event_cb(btn, event_handler);                 /*Assign a callback to the button*/

    lv_obj_t * label = lv_label_create(btn, NULL);          /*Add a label to the button*/
    lv_label_set_text(label, "vvvvvvvv");                     /*Set the labels text*/    
}

void loop()
{

    lv_task_handler(); /* let the GUI do its work */
    usleep(5 * 1000);
}

void lvgl_test()
{
    setup();
    while (1)
    {
        loop();
    }
}
