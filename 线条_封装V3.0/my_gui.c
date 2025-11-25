#include "my_gui.h"


/* 获取当前活动屏幕的宽高 */
#define scr_act_width() lv_obj_get_width(lv_scr_act())
#define scr_act_height() lv_obj_get_height(lv_scr_act())

lv_obj_t *label1;

#define SIN_POINTS_NUM   (200)
static lv_point_t sin_line_points[SIN_POINTS_NUM];              /* 正弦波坐标数组 */
static lv_point_t straigh_line_points[] = {{0,0},{100,0}};      /* 直线坐标数组 */

/**
 * @brief       产生正弦波坐标点
 * @param       maxval : 峰值
 * @param       samples: 坐标点的个数
 * @retval      无
 */
static void create_sin_buf(uint16_t maxval, uint16_t samples)
{
    uint16_t i;
    float y = 0;

    /*
     * 正弦波最小正周期为2π，约等于2 * 3.1415926
     * 曲线上相邻的两个点在x轴上的间隔 = 2 * 3.1415926 / 采样点数量
     */
    float inc = (2 * 3.1415926) / samples;                      /* 计算相邻两个点的x轴间隔 */

    for (i = 0; i < samples; i++)                               /* 连续产生samples个点 */
    {
        /*
         * 正弦波函数解析式：y = Asin(wx + φ）+ b
         * 计算每个点的y值，将峰值放大maxval倍，并将曲线向上偏移maxval到正数区域
         */
        y = maxval * sin(inc * i) + maxval;

        sin_line_points[i].x = 2 * i;                           /* 存入x轴坐标 */
        sin_line_points[i].y = y;                               /* 存入y轴坐标 */
    }
}



/** \brief 滑块部件的初始化函数,传入滑块本身、依附的父对象、想要的滑块类型即可完成滑块形式初始化
 *
 * \param 滑块部件自身
 * \param 滑块部件对齐时参考的父对象
 * \param 滑块部件样式结构体
 * \return 无
 *
 */
 void my_slider_init(lv_obj_t *my_main,const lv_obj_t *my_dad,str_slider *str)
 {
     if (str == NULL) {
         return;     // 保护性编程，防止空指针
     }
     lv_slider_set_mode(my_main,str->slider_mode);
     if (str->width) lv_obj_set_width(my_main, str->width);
     if (str->height) lv_obj_set_height(my_main, str->height);
     lv_obj_align_to(my_main,my_dad , str->position, str->x_ofs, str->y_ofs);
     if (str->min_value || str->max_value) lv_slider_set_range(my_main, str->min_value,str->max_value);
     if (str->right_value) lv_slider_set_value(my_main,str->right_value,str->anim_enable);
     if (str->left_value)  lv_slider_set_left_value(my_main, str->left_value, str->anim_enable);
     lv_obj_update_layout(my_main);
 }

 /** \brief 圆弧部件的初始化函数,传入圆弧本身、依附的父对象、想要的圆弧类型即可完成圆弧形式初始化
 *
 * \param 圆弧部件自身
 * \param 圆弧部件对齐时参考的父对象
 * \param 圆弧部件样式结构体
 * \return 无
 *
 */
 void my_arc_init(lv_obj_t *my_main,const lv_obj_t *my_dad,str_arc *str)
 {
     if (str == NULL) {
         return;     // 保护性编程，防止空指针
     }
     lv_arc_set_mode(my_main,str->arc_mode);
     if (str->width) lv_obj_set_width(my_main, str->width);
     if (str->height) lv_obj_set_height(my_main, str->height);
     if (str->arc_width)
     {
        lv_obj_set_style_arc_width(my_main,str->arc_width,LV_PART_MAIN);
        lv_obj_set_style_arc_width(my_main,str->arc_width,LV_PART_INDICATOR);
     }
     if (str->rotation) lv_arc_set_rotation(my_main, str->rotation);
     lv_obj_align_to(my_main,my_dad , str->position, str->x_ofs, str->y_ofs);
     if (str->min_value || str->max_value) lv_arc_set_range(my_main, str->min_value,str->max_value);
     if (str->start_value) lv_arc_set_value(my_main,str->start_value);
     if (str->bg_start_v || str->bf_end_v) lv_arc_set_bg_angles(my_main, str->bg_start_v, str->bf_end_v);
     if (str->my_arc_mode == MY_ARC_MONITOR)
     {
         lv_obj_remove_style(my_main,NULL,LV_PART_KNOB);
         lv_obj_clear_flag(my_main,LV_OBJ_FLAG_CLICKABLE);
     }
     lv_obj_update_layout(my_main);
 }


 /** \brief 生成一个文字标签，并指定文字(文字内容不可变）
  *
  * \param 生成时依附的父对象
  * \param 位移时依附的父对象
  * \param 与父对象的相对位置
  * \param 对于父对象的X轴偏移
  * \param 对于父对象的Y轴偏移
  * \param 对应的文字
  * \param 文字大小
  * \return 所创建的标签对象
  *
  */
lv_obj_t *label_text_create(const lv_obj_t *my_dad,const lv_obj_t *position_dad,lv_align_t position,lv_coord_t x_ofs,lv_coord_t y_ofs,const char* label_text,lv_font_t *font)
{
    lv_obj_t *label = lv_label_create(my_dad);
    lv_obj_set_style_text_font(label, font, LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_align_to(label,position_dad ,position, x_ofs, y_ofs);
    lv_label_set_text( label, label_text);
    return label;
}


 /** \brief 线条部件的初始化函数,传入线条部件样式结构体、依附的父对象、位置相对偏移的参考对象即可完成线条初始化
 *
 * \param my_dad:线条部件样式结构体
 * \param my_option_dad:创建依附的父对象
 * \param str:位置相对偏移的参考对象
 * \return 创建出来的线条对象
 *
 */
 lv_obj_t *my_line_init(const lv_obj_t *my_dad,const lv_obj_t *my_option_dad,my_str_line *str)
 {
     lv_obj_t *line = lv_line_create(my_dad);
     lv_line_set_points(line,str->line_points,str->point_num);
     if(str->line_width) lv_obj_set_style_line_width(line, str->line_width, LV_PART_MAIN);
     lv_obj_set_style_line_color(line,str->line_color,LV_PART_MAIN);
     lv_obj_set_style_line_rounded(line, str->rounded_enable, LV_PART_MAIN);
     lv_line_set_y_invert(line, str->invert_enable);
     lv_obj_align_to(line,my_option_dad , str->position, str->x_ofs, str->y_ofs);
     return line;
 }

void my_gui(void)
{
    lv_obj_t *act = lv_scr_act();

    create_sin_buf(scr_act_height()/4, SIN_POINTS_NUM);
    my_str_line my_str_line1 = {0};
    my_str_line1.line_points = sin_line_points;
    my_str_line1.point_num = SIN_POINTS_NUM;
    my_str_line1.line_width = 8;
    my_str_line1.line_color = lv_palette_main(LV_PALETTE_BLUE);
    my_str_line1.rounded_enable = true;
    my_str_line1.position = LV_ALIGN_CENTER;
    my_str_line1.x_ofs = 0;
    my_str_line1.y_ofs = 0;
    lv_obj_t *line = my_line_init(act,act,&my_str_line1);

    label1 = label_text_create(act,act,LV_ALIGN_TOP_LEFT,20,20,"Line",&lv_font_montserrat_30);

    my_str_line my_str_line2 = {0};
    my_str_line2.line_points = straigh_line_points;
    my_str_line2.point_num = 2;
    my_str_line2.position = LV_ALIGN_OUT_BOTTOM_MID;
    my_str_line2.x_ofs = 0;
    my_str_line2.y_ofs = 0;
    lv_obj_t *line2 = my_line_init(act,label1,&my_str_line2);


}



