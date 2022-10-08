#include "lv_port_disp_win32.h"
#include "lv_port_indev_win32.h"

void lv_platform_init(void)
{
    lv_win32_disp_init();
    lv_win32_indev_init();
}

void lv_platform_exit(void)
{
    lv_win32_indev_exit();
    lv_win32_disp_exit();
}
