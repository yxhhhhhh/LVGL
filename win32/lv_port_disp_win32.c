#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "lv_port_disp_win32.h"
#include "screen.h"

#define DISP_DRAW_BUF_SIZE (MY_DISP_HOR_RES * 10)
static lv_color_t         s_buf_1[DISP_DRAW_BUF_SIZE];
static lv_color_t         s_buf_2[DISP_DRAW_BUF_SIZE];
static lv_disp_draw_buf_t s_draw_buf_dsc = {};
static lv_disp_drv_t      s_disp_drv     = {};
static BMP               *s_disp_bmp     = &WINDOW;

static void disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    uint8_t *psrc, *pdst;
    int      n = area->x2 - area->x1 + 1, i;
    bitmap_lock(s_disp_bmp, area->x1, area->y1, area->x2, area->y2);
    psrc = (uint8_t*)color_p;
    pdst = (uint8_t*)s_disp_bmp->pdata;
    if (psrc && pdst) {
        pdst += area->y1 * s_disp_bmp->stride + area->x1 * sizeof(uint32_t);
        for (i = area->y1; i <=  area->y2; i++) {
            memcpy(pdst, psrc, n * sizeof(uint32_t));
            psrc += n * sizeof(uint32_t), pdst += s_disp_bmp->stride;
        }
    }
    bitmap_unlock(s_disp_bmp);
    lv_disp_flush_ready(disp_drv);
}

void lv_win32_disp_init(void)
{
    lv_disp_draw_buf_init(&s_draw_buf_dsc, s_buf_1, s_buf_2, DISP_DRAW_BUF_SIZE);
    lv_disp_drv_init(&s_disp_drv);

    s_disp_drv.hor_res  = MY_DISP_HOR_RES;
    s_disp_drv.ver_res  = MY_DISP_VER_RES;
    s_disp_drv.flush_cb = disp_flush;
    s_disp_drv.draw_buf = &s_draw_buf_dsc;
    s_disp_drv.sw_rotate= !!MY_DISP_ROTATE;

    lv_disp_t *disp = lv_disp_drv_register(&s_disp_drv);
    lv_disp_set_rotation(disp, MY_DISP_ROTATE);

    // create screen/window bitmap
    bitmap_create(s_disp_bmp, MY_DISP_HOR_RES, MY_DISP_VER_RES);
}

void lv_win32_disp_exit(void)
{
    uint32_t tick_last = get_tick_count(), tick_cur;
    int      show      = -1;

    while (!s_disp_bmp->closed) {
        tick_cur  = get_tick_count();
        lv_tick_inc((int32_t)tick_cur - (int32_t)tick_last);
        tick_last = tick_cur;
        lv_timer_handler();
        if (show == -1) show = bitmap_show(s_disp_bmp);
        usleep(10 * 1000);
    }

    // destory screen/window bitmap
    bitmap_destroy(s_disp_bmp, 0);
}
