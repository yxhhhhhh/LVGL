#include <windows.h>
#include "input.h"

extern HWND g_ffrge_hwnd;

void input_getmouse(int *x, int *y, int *btns)
{
    if (g_ffrge_hwnd) {
        POINT point;
        GetCursorPos  (&point);
        ScreenToClient(g_ffrge_hwnd, &point);
        if (x   ) *x = point.x;
        if (y   ) *y = point.y;
        if (btns) {
            *btns  = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) ? (1 << 0): 0;
            *btns |= (GetAsyncKeyState(VK_RBUTTON) & 0x8000) ? (1 << 1): 0;
            *btns |= (GetAsyncKeyState(VK_MBUTTON) & 0x8000) ? (1 << 4): 0;
        }
    }
}
