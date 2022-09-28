#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <lvgl.h>
#include "widgets.h"
#ifdef WINDOW
#include "lv_port_disp_win32.h"
#include "lv_port_indev_win32.h"
#elif LINUX
#include <unistd.h>
#include <sys/time.h>
#include "fbdev.h"
#include "evdev.h"
#define  DISP_BUF_SIZE (1024 * 1024)
#endif


int main(void)
{
    lv_init();
#ifdef WINDOW
    lv_win32_disp_init();
    lv_win32_indev_init();
#elif LINUX
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
#endif

    lv_myarc();
    lv_mybar();

#ifdef WINDOW
    lv_win32_indev_exit();
    lv_win32_disp_exit();
#elif
    while(1)
    {
        lv_timer_handler();
        usleep(5000);
    }
#endif
    return 0;
}
#ifdef LINUX
uint32_t custom_tick_get(void)
{
    static uint64_t start_ms = 0;
    if(start_ms == 0) {
        struct timeval tv_start;
        gettimeofday(&tv_start, NULL);
        start_ms = (tv_start.tv_sec * 1000000 + tv_start.tv_usec) / 1000;
    }

    struct timeval tv_now;
    gettimeofday(&tv_now, NULL);
    uint64_t now_ms;
    now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000;

    uint32_t time_ms = now_ms - start_ms;
    return time_ms;
}
#endif
