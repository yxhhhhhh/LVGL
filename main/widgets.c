#include <stdio.h>
#include <lvgl.h>
#include "widgets.h"

static void arc_callback(lv_event_t * event)
{
    lv_obj_t *arc = lv_event_get_target(event);
    lv_obj_t *label = lv_event_get_user_data(event);
    lv_label_set_text_fmt(label, "%d%%", lv_arc_get_value(arc));
    lv_arc_rotate_obj_to_angle(arc, label, 25);
}

static void set_angle(void * obj, int32_t v)
{
    lv_arc_set_value(obj, v);
}

static void set_temp(void * bar, int32_t temp)
{
    lv_bar_set_value(bar, temp, LV_ANIM_ON);
}

static void set_value(void * bar, int32_t v)
{
    lv_bar_set_value(bar, v, LV_ANIM_OFF);
}

static void event_cb(lv_event_t * e)
{
    lv_obj_draw_part_dsc_t * dsc = lv_event_get_draw_part_dsc(e);
    if(dsc->part != LV_PART_INDICATOR) return;

    lv_obj_t * obj = lv_event_get_target(e);

    lv_draw_label_dsc_t label_dsc;
    lv_draw_label_dsc_init(&label_dsc);
    label_dsc.font = LV_FONT_DEFAULT;

    char buf[8];
    lv_snprintf(buf, sizeof(buf), "%d", (int)lv_bar_get_value(obj));

    lv_point_t txt_size;
    lv_txt_get_size(&txt_size, buf, label_dsc.font, label_dsc.letter_space, label_dsc.line_space, LV_COORD_MAX,
                    label_dsc.flag);

    lv_area_t txt_area;
    /*If the indicator is long enough put the text inside on the right*/
    if(lv_area_get_width(dsc->draw_area) > txt_size.x + 20) {
        txt_area.x2 = dsc->draw_area->x2 - 5;
        txt_area.x1 = txt_area.x2 - txt_size.x + 1;
        label_dsc.color = lv_color_white();
    }
    /*If the indicator is still short put the text out of it on the right*/
    else {
        txt_area.x1 = dsc->draw_area->x2 + 5;
        txt_area.x2 = txt_area.x1 + txt_size.x - 1;
        label_dsc.color = lv_color_black();
    }

    txt_area.y1 = dsc->draw_area->y1 + (lv_area_get_height(dsc->draw_area) - txt_size.y) / 2;
    txt_area.y2 = txt_area.y1 + txt_size.y - 1;

    lv_draw_label(dsc->draw_ctx, &label_dsc, &txt_area, buf, NULL);
}


void lv_myarc(void)
{
    lv_obj_t* label = lv_label_create(lv_scr_act());
    lv_obj_t* arc = lv_arc_create(lv_scr_act());
    lv_obj_set_size(arc, 100, 100); //大小
    lv_arc_set_bg_angles(arc, 0, 270); //弧线角度
    lv_arc_set_rotation(arc, 135); //从右水平顺时针（3点钟方向）算起
    lv_arc_set_value(arc, 30); //初始值 -- 百分比
    lv_obj_align(arc, LV_ALIGN_TOP_LEFT, 10, 10);  //位置
    lv_obj_add_event_cb(arc, arc_callback, LV_EVENT_VALUE_CHANGED, label); //貌似跟一个标签联动 但是没看出来
    lv_event_send(arc, LV_EVENT_VALUE_CHANGED, NULL);


    lv_obj_t * arc2 = lv_arc_create(lv_scr_act());
    lv_arc_set_bg_angles(arc2, 0, 360);
    lv_arc_set_rotation(arc2, 270);
    lv_obj_align(arc2, LV_ALIGN_TOP_LEFT, 300, 10);
    lv_obj_remove_style(arc2, NULL, LV_PART_KNOB);  //去掉圆弧的头
    lv_obj_clear_flag(arc2, LV_OBJ_FLAG_CLICKABLE); //不支持鼠标点击

    lv_anim_t anim;
    lv_anim_init(&anim);
    lv_anim_set_var(&anim, arc2);  //设置“动画制作”功能
    lv_anim_set_exec_cb(&anim, set_angle); //设置回调
    lv_anim_set_time(&anim, 1000);  //整个循环动画时长
    lv_anim_set_repeat_count(&anim, LV_ANIM_REPEAT_INFINITE); //重复次数。默认值为1。LV_ANIM_REPEAT_INFINIT用于无限重复
    lv_anim_set_repeat_delay(&anim, 500); //重复之前要延迟。默认为0 [ms]
    lv_anim_set_values(&anim, 0, 100); //开始和结束的值

    lv_anim_start(&anim); //应用动画效果
}

void lv_mybar(void)
{
    #if 1
    lv_obj_t * bar = lv_bar_create(lv_scr_act());
    lv_obj_set_size(bar, 200, 20);
    lv_obj_align(bar, LV_ALIGN_TOP_MID, 0, 10);
    lv_bar_set_value(bar, 80, LV_ANIM_OFF);  //设置初始值  百分比
    #endif

    #if 1
    static lv_style_t style_bg;
    lv_style_init(&style_bg);
    lv_style_set_border_color(&style_bg, lv_palette_main(LV_PALETTE_BLUE));  //外框颜色
    lv_style_set_border_width(&style_bg, 2);
    //lv_style_set_pad_all(&style_bg, 10);
    lv_style_set_pad_hor(&style_bg, 20); //外框宽度不能大于总的bar宽度
    lv_style_set_pad_ver(&style_bg, 5);
    lv_style_set_radius(&style_bg, 6); //bar的圆角
    lv_style_set_anim_time(&style_bg, 1000); //动画时间

    static lv_style_t style_indic;
    lv_style_init(&style_indic);
    lv_style_set_bg_opa(&style_indic, LV_OPA_COVER); //背景透明
    lv_style_set_bg_color(&style_indic, lv_palette_main(LV_PALETTE_BLUE));  //蓝色背景
    lv_style_set_radius(&style_indic, 3);

    lv_obj_t * bar1 = lv_bar_create(lv_scr_act());
    lv_obj_remove_style_all(bar1);  //外框和bar之间的淡蓝色样式会清掉
    lv_obj_add_style(bar1, &style_bg, 0);  //添加样式到对象
    lv_obj_add_style(bar1, &style_indic, LV_PART_INDICATOR); //此样式只针对bar区域。
    lv_obj_set_size(bar1, 200, 30);
    lv_obj_align(bar1, LV_ALIGN_TOP_MID, 0, 80);
    lv_bar_set_value(bar1, 80, LV_ANIM_ON);
    #endif
    #if 1
    static lv_style_t style_indic1;
    lv_style_init(&style_indic1);
    lv_style_set_bg_opa(&style_indic1, LV_OPA_50);
    lv_style_set_bg_color(&style_indic1, lv_palette_main(LV_PALETTE_RED));
    lv_style_set_bg_grad_color(&style_indic1, lv_palette_main(LV_PALETTE_BLUE));  //渐变色开始的颜色
    lv_style_set_bg_grad_dir(&style_indic1, LV_GRAD_DIR_VER);  //水平方向渐变
    lv_style_set_radius(&style_indic1, 3);

    lv_obj_t * bar2 = lv_bar_create(lv_scr_act());
    lv_obj_add_style(bar2, &style_indic1, LV_PART_INDICATOR); //此样式只针对bar区域
    lv_obj_set_size(bar2, 20, 200);
    lv_obj_align(bar2, LV_ALIGN_TOP_RIGHT, -50, 10);
    lv_bar_set_range(bar2, -20, 40);

    lv_anim_t anim1;
    lv_anim_init(&anim1);
    lv_anim_set_exec_cb(&anim1, set_temp);
    lv_anim_set_time(&anim1, 3000); //动画时长
    lv_anim_set_playback_time(&anim1, 3000); //在时间段内，会有一个回放的播放动画（递减效果）。默认值为0（禁用）[ms]
    lv_anim_set_var(&anim1, bar2);
    lv_anim_set_values(&anim1, -20, 30);  //回调函数中这个数值在这范围内递增变化 -20 -- 30
    lv_anim_set_repeat_count(&anim1, LV_ANIM_REPEAT_INFINITE); //重复次数。默认值为1。LV_ANIM_REPEAT_INFINIT用于无限重复
    lv_anim_start(&anim1);
    #endif
    #if 1
    LV_IMG_DECLARE(img_skew_strip);  //导入图片
    static lv_style_t style_indic2;

    lv_style_init(&style_indic2);
    lv_style_set_bg_img_src(&style_indic2, &img_skew_strip);  //斜线
    lv_style_set_bg_img_tiled(&style_indic2, true);  //重复
    lv_style_set_bg_img_opa(&style_indic2, LV_OPA_30);

    lv_obj_t * bar3 = lv_bar_create(lv_scr_act());
    lv_obj_add_style(bar3, &style_indic2, LV_PART_INDICATOR);

    lv_obj_set_size(bar3, 260, 20);
    lv_obj_align(bar3, LV_ALIGN_TOP_MID, 0, 150);
    lv_bar_set_mode(bar3, LV_BAR_MODE_RANGE);  //这个设置了 下面的lv_bar_set_start_value 函数才有效果
    lv_bar_set_value(bar3, 90, LV_ANIM_OFF);  //最大值
    lv_bar_set_start_value(bar3, 20, LV_ANIM_OFF); //起始值

    lv_obj_t * label = lv_label_create(lv_scr_act());
    lv_obj_set_style_base_dir(bar3, LV_BASE_DIR_RTL, 0); // 从右边开始绘画
    lv_label_set_text(label, "Right to Left base direction");
    lv_obj_align_to(label, bar3, LV_ALIGN_TOP_MID, 0, 25);
    #endif

    #if 1
    lv_obj_t * bar4 = lv_bar_create(lv_scr_act());
    lv_obj_add_event_cb(bar4, event_cb, LV_EVENT_DRAW_PART_END, NULL);
    lv_obj_set_size(bar4, 200, 20);
    lv_obj_align(bar4, LV_ALIGN_TOP_MID, 250, 100);

    lv_anim_t anim2;
    lv_anim_init(&anim2);
    lv_anim_set_var(&anim2, bar4);
    lv_anim_set_values(&anim2, 0, 100);
    lv_anim_set_exec_cb(&anim2, set_value);
    lv_anim_set_time(&anim2, 10000);
    lv_anim_set_playback_time(&anim2, 10000);
    lv_anim_set_repeat_count(&anim2, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&anim2);

    #endif
}


