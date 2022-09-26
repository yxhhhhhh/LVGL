#include <windows.h>
#include <stdio.h>
#include "lv_port_indev_win32.h"
#include "input.h"

/*------------------
 * Mouse
 * -----------------*/
static void mouse_init(void)
{
}

static void mouse_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    int x, y, b;
    input_getmouse(&x, &y, &b);
    data->point.x = x;
    data->point.y = y;
    data->state = (b & 1) ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
}

/*------------------
 * Keypad
 * -----------------*/
extern WNDPROC g_ffrge_input_wndproc;
#define MAX_KEYEVT_NUN   16
static uint32_t g_keyevt_buff[MAX_KEYEVT_NUN];
static uint32_t g_keyevt_head = 0;
static uint32_t g_keyevt_tail = 0;
static uint32_t g_keyevt_size = 0;
static LRESULT CALLBACK my_keybd_wndproc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (uMsg == WM_KEYUP || uMsg == WM_SYSKEYUP || uMsg == WM_KEYDOWN || uMsg == WM_SYSKEYDOWN) {
        uint32_t key;
        switch (wParam) {
        case VK_UP    : key = LV_KEY_UP       ; break;
        case VK_DOWN  : key = LV_KEY_DOWN     ; break;
        case VK_RIGHT : key = LV_KEY_RIGHT    ; break;
        case VK_LEFT  : key = LV_KEY_LEFT     ; break;
        case VK_ESCAPE: key = LV_KEY_ESC      ; break;
        case VK_DELETE: key = LV_KEY_DEL      ; break;
        case VK_BACK  : key = LV_KEY_BACKSPACE; break;
        case VK_RETURN: key = LV_KEY_ENTER    ; break;
        case VK_NEXT  : key = LV_KEY_NEXT     ; break;
        case VK_PRIOR : key = LV_KEY_PREV     ; break;
        case VK_HOME  : key = LV_KEY_HOME     ; break;
        case VK_END   : key = LV_KEY_END      ; break;
        default       : key = (uint32_t)-1    ; break;
        }
        if (key != (uint32_t)-1 && g_keyevt_size < MAX_KEYEVT_NUN) {
            int pressed = (uMsg == WM_KEYDOWN || uMsg == WM_SYSKEYDOWN);
            g_keyevt_buff[g_keyevt_tail++] = key | (pressed << 31);
            g_keyevt_tail %= MAX_KEYEVT_NUN;
            g_keyevt_size++;
        }
    }
    return 0;
}

static void keybd_init(void)
{
    g_ffrge_input_wndproc = my_keybd_wndproc;
}

static void keybd_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    if (g_keyevt_size > 0) {
        uint32_t key = g_keyevt_buff[g_keyevt_head++];
        data->key    =  key & ~(1 << 31);
        data->state  = (key &  (1 << 31)) ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;
        g_keyevt_head %= MAX_KEYEVT_NUN;
        g_keyevt_size--;
        printf("key: %d, %s\n", data->key, data->state == LV_INDEV_STATE_PRESSED ? "pressed" : "released"); fflush(stdout);
    }
}

static lv_indev_drv_t indev_drv_mouse;
static lv_indev_t *   indev_dev_mouse;
static lv_indev_drv_t indev_drv_keybd;
static lv_indev_t *   indev_dev_keybd;

void lv_win32_indev_init(void)
{
    /*------------------
     * Mouse
     * -----------------*/
    mouse_init();

    lv_indev_drv_init(&indev_drv_mouse);
    indev_drv_mouse.type    = LV_INDEV_TYPE_POINTER;
    indev_drv_mouse.read_cb = mouse_read;
    indev_dev_mouse         = lv_indev_drv_register(&indev_drv_mouse);

#if 0
    /* Set cursor. For simplicity set a HOME symbol now. */
    lv_obj_t * mouse_cursor = lv_img_create(lv_scr_act());
    lv_img_set_src(mouse_cursor, LV_SYMBOL_HOME);
    lv_indev_set_cursor(indev_dev_mouse, mouse_cursor);
#endif

    /*------------------
     * Keyboard
     * -----------------*/
    keybd_init();

    lv_indev_drv_init(&indev_drv_keybd);
    indev_drv_keybd.type    = LV_INDEV_TYPE_KEYPAD;
    indev_drv_keybd.read_cb = keybd_read;
    indev_dev_keybd         = lv_indev_drv_register(&indev_drv_keybd);
}

void lv_win32_indev_exit(void)
{
}
