#include <stdlib.h>
#include <stdio.h>
#include <lvgl.h>
#include "widgets.h"
#include "lv_platform.h"

#ifdef LINUX
#include <unistd.h>
#include <sys/time.h>
#endif


int main(void)
{
    lv_init();
    lv_platform_init();

    lv_myarc();
    lv_mybar();

    lv_platform_exit();
    #ifdef LINUX
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
