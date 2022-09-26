#ifndef LV_PORT_DISP_WIN32_H
#define LV_PORT_DISP_WIN32_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "lvgl.h"

/*********************
 *      DEFINES
 *********************/
#define LV_HOR_RES_MAX   1280
#define LV_VER_RES_MAX   720
#define MY_DISP_HOR_RES  1280
#define MY_DISP_VER_RES  720
#define MY_DISP_ROTATE   0

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
void lv_win32_disp_init(void);
void lv_win32_disp_exit(void);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_PORT_DISP_TEMPL_H*/
