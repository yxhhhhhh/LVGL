#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <lvgl.h>
#include "lv_port_disp_win32.h"
#include "lv_port_indev_win32.h"

extern void lv_demo_widgets(void);
extern void lv_demo_benchmark(void);
extern void lv_demo_stress(void);
extern void lv_demo_music(void);

int PASCAL WinMain(HINSTANCE hInst, HINSTANCE hPreInst, LPSTR lpszCmdLine, int nCmdShow)
{
    lv_init();

    lv_win32_disp_init();
    lv_win32_indev_init();

    lv_demo_widgets();
    
    lv_win32_indev_exit();
    lv_win32_disp_exit();
    return 0;
}
