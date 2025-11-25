#include "my_gui.h"


/* 获取当前活动屏幕的宽高 */
#define scr_act_width() lv_obj_get_width(lv_scr_act())
#define scr_act_height() lv_obj_get_height(lv_scr_act())

lv_obj_t *slider1;
lv_obj_t *slider2;
lv_obj_t *slider3;
lv_obj_t *slider4;
lv_obj_t *slider5;
lv_obj_t *slider6;
lv_obj_t *img1;

LV_IMG_DECLARE(image);

/** \brief 滑块部件的创建初始化函数
 *
 * \param 滑块创建依附的父对象
 * \param 滑块部件对齐时参考的父对象
 * \param 滑块部件样式结构体
 * \return 所创建的滑块部件
 *
 */
 lv_obj_t *my_slider_init(lv_obj_t *my_dad,const lv_obj_t *my_position_dad,my_str_slider_t *str)
 {
     if (str == NULL) {
         return;     // 保护性编程，防止空指针
     }
     lv_obj_t *slider = lv_slider_create(my_dad);
     lv_slider_set_mode(slider,str->slider_mode);
     if (str->width) lv_obj_set_width(slider, str->width);
     if (str->height) lv_obj_set_height(slider, str->height);
     if (str->main_color)  lv_obj_set_style_bg_color(slider,lv_color_hex(str->main_color), LV_PART_MAIN);
     if (str->indicator_color)  lv_obj_set_style_bg_color(slider,lv_color_hex(str->indicator_color), LV_PART_INDICATOR);
     if (str->konb_disable) lv_obj_remove_style(slider,NULL,LV_PART_KNOB);
     lv_obj_align_to(slider,my_position_dad , str->position, str->x_ofs, str->y_ofs);
     if (str->min_value || str->max_value) lv_slider_set_range(slider, str->min_value,str->max_value);
     if (str->right_value) lv_slider_set_value(slider,str->right_value,str->anim_enable);
     if (str->left_value)  lv_slider_set_left_value(slider, str->left_value, str->anim_enable);
     lv_obj_update_layout(slider);

     return slider;
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
     if (str == NULL) {
         return;     // 保护性编程，防止空指针
     }
     lv_obj_t *line = lv_line_create(my_dad);
     lv_line_set_points(line,str->line_points,str->point_num);
     if(str->line_width) lv_obj_set_style_line_width(line, str->line_width, LV_PART_MAIN);
     lv_obj_set_style_line_color(line,str->line_color,LV_PART_MAIN);
     lv_obj_set_style_line_rounded(line, str->rounded_enable, LV_PART_MAIN);
     lv_line_set_y_invert(line, str->invert_enable);
     lv_obj_align_to(line,my_option_dad , str->position, str->x_ofs, str->y_ofs);
     return line;
 }


 /** \brief 图片部件的初始化函数,传入图片部件样式结构体、依附的父对象、位置相对偏移的参考对象、图片源即可完成线条初始化
 *
 * \param my_dad:图片部件样式结构体
 * \param my_option_dad:创建依附的父对象
 * \param str:位置相对偏移的参考对象
 * \param img_source:图片源
 * \return 创建出来的图片对象
 *
 */
 lv_obj_t *my_img_init(const lv_obj_t *my_dad,const lv_obj_t *my_option_dad,my_str_img_t *str,const lv_img_dsc_t* img_source)
 {
     if (str == NULL) {
         return;     // 保护性编程，防止空指针
     }
     lv_obj_t *img = lv_img_create(my_dad);
     lv_img_set_src(img,img_source);
     if (str->pivot_x || str->pivot_y)
     {
         lv_obj_update_layout(img);
         lv_img_set_pivot(img,str->pivot_x,str->pivot_y);
     }
     if (str->zoom) lv_img_set_zoom(img,str->zoom);
     if ( str->angle!=0 && (str->angle<=360 && str->angle>=-360))
     {
         lv_img_set_angle(img,str->angle*10);
     }

     lv_obj_align_to(img,my_dad , str->position, str->x_ofs, str->y_ofs);
     lv_obj_update_layout(img);
     return img;
 }

 static void event_cb(lv_event_t *e)
{
    lv_obj_t *target = lv_event_get_target(e);
    if (target == slider1)
    {
        lv_img_set_zoom(img1,lv_slider_get_value(slider1));
    }
    if (target == slider2)
    {
        lv_img_set_angle(img1,lv_slider_get_value(slider2));
    }
    if (target == slider3 || target == slider4 || target == slider5)
    {
        lv_obj_set_style_img_recolor(img1,
                                     lv_color_make(lv_slider_get_value(slider3),lv_slider_get_value(slider4),lv_slider_get_value(slider5)),
                                     LV_PART_MAIN);
    }
    if (target == slider6)
    {
        lv_obj_set_style_img_recolor_opa(img1,lv_slider_get_value(slider6),LV_PART_MAIN);
    }
}


void my_gui(void)
{
    lv_obj_t *act = lv_scr_act();

    my_str_img_t my_str_img = {0};
    my_str_img.position = LV_ALIGN_LEFT_MID;
    my_str_img.x_ofs = scr_act_width()/5;
    my_str_img.y_ofs = 0;
    img1 = my_img_init(act,act,&my_str_img,&image);

    /*缩放控制模块*/
    my_str_slider_t my_str_slider1 = {0};
    my_str_slider1.position = LV_ALIGN_TOP_RIGHT;
    my_str_slider1.x_ofs = -scr_act_width()/7;
    my_str_slider1.y_ofs = scr_act_height()/5;
    my_str_slider1.main_color = 0x989c98;
    my_str_slider1.indicator_color = 0x989c98;
    my_str_slider1.konb_disable = 1;
    my_str_slider1.width = scr_act_width()/3;
    my_str_slider1.height = scr_act_height()/20;
    my_str_slider1.min_value = 256;
    my_str_slider1.max_value = 512;
    slider1 = my_slider_init(act,act,&my_str_slider1);
    lv_obj_add_event_cb(slider1,event_cb,LV_EVENT_VALUE_CHANGED,NULL);

    /*旋转控制模块*/
    my_str_slider_t my_str_slider2 = {0};
    my_str_slider2.position = LV_ALIGN_TOP_RIGHT;
    my_str_slider2.x_ofs = -scr_act_width()/7;
    my_str_slider2.y_ofs = scr_act_height()/5+50;
    my_str_slider2.main_color = 0x989c98;
    my_str_slider2.indicator_color = 0x989c98;
    my_str_slider2.konb_disable = 1;
    my_str_slider2.width = scr_act_width()/3;
    my_str_slider2.height = scr_act_height()/20;
    my_str_slider2.min_value = 0;
    my_str_slider2.max_value = 3600;
    slider2 = my_slider_init(act,act,&my_str_slider2);
    lv_obj_add_event_cb(slider2,event_cb,LV_EVENT_VALUE_CHANGED,NULL);

    /*图片红色分量控制模块*/
    my_str_slider_t my_str_slider3 = {0};
    my_str_slider3.position = LV_ALIGN_TOP_RIGHT;
    my_str_slider3.x_ofs = -scr_act_width()/7;
    my_str_slider3.y_ofs = scr_act_height()/5+100;
    my_str_slider3.main_color = 0xff0000;
    my_str_slider3.indicator_color = 0xff0000;
    my_str_slider3.konb_disable = 1;
    my_str_slider3.width = scr_act_width()/3;
    my_str_slider3.height = scr_act_height()/20;
    my_str_slider3.min_value = 0;
    my_str_slider3.max_value = 255;
    slider3 = my_slider_init(act,act,&my_str_slider3);
    lv_obj_add_event_cb(slider3,event_cb,LV_EVENT_VALUE_CHANGED,NULL);

    /*图片绿色分量控制模块*/
    my_str_slider_t my_str_slider4 = {0};
    my_str_slider4.position = LV_ALIGN_TOP_RIGHT;
    my_str_slider4.x_ofs = -scr_act_width()/7;
    my_str_slider4.y_ofs = scr_act_height()/5+150;
    my_str_slider4.main_color = 0x00ff00;
    my_str_slider4.indicator_color = 0x00ff00;
    my_str_slider4.konb_disable = 1;
    my_str_slider4.width = scr_act_width()/3;
    my_str_slider4.height = scr_act_height()/20;
    my_str_slider4.min_value = 0;
    my_str_slider4.max_value = 255;
    slider4 = my_slider_init(act,act,&my_str_slider4);
    lv_obj_add_event_cb(slider4,event_cb,LV_EVENT_VALUE_CHANGED,NULL);

    /*图片蓝色分量控制模块*/
    my_str_slider_t my_str_slider5 = {0};
    my_str_slider5.position = LV_ALIGN_TOP_RIGHT;
    my_str_slider5.x_ofs = -scr_act_width()/7;
    my_str_slider5.y_ofs = scr_act_height()/5+200;
    my_str_slider5.main_color = 0x0000ff;
    my_str_slider5.indicator_color = 0x0000ff;
    my_str_slider5.konb_disable = 1;
    my_str_slider5.width = scr_act_width()/3;
    my_str_slider5.height = scr_act_height()/20;
    my_str_slider5.min_value = 0;
    my_str_slider5.max_value = 255;
    slider5 = my_slider_init(act,act,&my_str_slider5);
    lv_obj_add_event_cb(slider5,event_cb,LV_EVENT_VALUE_CHANGED,NULL);

    /*图片透明度控制模块*/
    my_str_slider_t my_str_slider6 = {0};
    my_str_slider6.position = LV_ALIGN_TOP_RIGHT;
    my_str_slider6.x_ofs = -scr_act_width()/7;
    my_str_slider6.y_ofs = scr_act_height()/5+250;
    my_str_slider6.main_color = 0x000000;
    my_str_slider6.indicator_color = 0x000000;
    my_str_slider6.konb_disable = 1;
    my_str_slider6.width = scr_act_width()/3;
    my_str_slider6.height = scr_act_height()/20;
    my_str_slider6.min_value = 0;
    my_str_slider6.max_value = 255;
    slider6 = my_slider_init(act,act,&my_str_slider6);
    lv_obj_add_event_cb(slider6,event_cb,LV_EVENT_VALUE_CHANGED,NULL);
}



