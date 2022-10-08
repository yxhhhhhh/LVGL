#include "fbdev.h"
#include "evdev.h"

#define  DISP_BUF_SIZE (1024 * 1024)

void lv_platform_init(void)
{
    lv_color_t         color_buf[DISP_BUF_SIZE];
    lv_disp_draw_buf_t disp_buf;
    lv_disp_drv_t      disp_drv;
    lv_indev_drv_t     indev_drv;

    fbdev_init();
    lv_disp_draw_buf_init(&disp_buf, color_buf, NULL, DISP_BUF_SIZE);

    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf   = &disp_buf;
    disp_drv.flush_cb   = fbdev_flush;
    disp_drv.sw_rotate  = 1;
    disp_drv.rotated    = LV_DISP_ROT_90;
    lv_disp_drv_register(&disp_drv);

    evdev_init();
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = evdev_read;
    lv_indev_drv_register(&indev_drv);
}

void lv_platform_exit(void)
{
}