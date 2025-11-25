#include "my_gui.h"


/* 获取当前活动屏幕的宽高 */
#define scr_act_width() lv_obj_get_width(lv_scr_act())
#define scr_act_height() lv_obj_get_height(lv_scr_act())

lv_obj_t *slider_label;
lv_obj_t *msgbox;

/** \brief 基础部件的创建初始化函数
 *
 * \param 基础创建依附的父对象
 * \param 基础部件对齐时参考的父对象
 * \param 基础部件样式结构体
 * \return 所创建的基础部件
 *
 */
 lv_obj_t *my_obj_init(lv_obj_t *my_dad,const lv_obj_t *my_position_dad,my_str_obj_t *str)
 {
     if (str == NULL) {
         return;     // 保护性编程，防止空指针
     }

     lv_obj_t *obj = lv_obj_create(my_dad);
     if (str->width) lv_obj_set_width(obj, str->width);
     if (str->height) lv_obj_set_height(obj, str->height);
     lv_obj_align_to(obj,my_position_dad , str->position, str->x_ofs, str->y_ofs);
     if (str->bg_color)  lv_obj_set_style_bg_color(obj,lv_color_hex(str->bg_color), LV_PART_MAIN);
     if (str->bg_opa)  lv_obj_set_style_bg_opa(obj,str->bg_opa, LV_PART_MAIN);
     if (str->radius)  lv_obj_set_style_radius(obj,str->radius, LV_PART_MAIN);
     if (str->border_disable) lv_obj_set_style_border_width(obj,0,LV_PART_MAIN);
     if (str->scrollbar_disable) lv_obj_remove_style(obj,NULL,LV_PART_SCROLLBAR);
     lv_obj_update_layout(obj);

     return obj;
 }


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
lv_obj_t *my_label_text_create(const lv_obj_t *my_dad,const lv_obj_t *position_dad,lv_align_t position,lv_coord_t x_ofs,lv_coord_t y_ofs,const char* label_text,lv_font_t *font)
{
    lv_obj_t *label = lv_label_create(my_dad);
    lv_label_set_text( label, label_text);
    lv_obj_set_style_text_font(label, font, LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_align_to(label,position_dad ,position, x_ofs, y_ofs);
    return label;
}


 /** \brief 线条部件的初始化函数,传入线条部件样式结构体、依附的父对象、位置相对偏移的参考对象即可完成线条初始化
 *
 * \param my_dad:线条部件样式结构体
 * \param my_position_dad:创建依附的父对象
 * \param str:位置相对偏移的参考对象
 * \return 创建出来的线条对象
 *
 */
 lv_obj_t *my_line_init(const lv_obj_t *my_dad,const lv_obj_t *my_position_dad,my_str_line_t *str)
 {
     if (str == NULL) {
         return;     // 保护性编程，防止空指针
     }
     lv_obj_t *line = lv_line_create(my_dad);
     lv_line_set_points(line,str->line_points,str->point_num);
     if(str->line_width) lv_obj_set_style_line_width(line, str->line_width, LV_PART_MAIN);
     if(str->line_color) lv_obj_set_style_line_color(line,lv_color_hex(str->line_color),LV_PART_MAIN);
     lv_obj_set_style_line_rounded(line, str->rounded_enable, LV_PART_MAIN);
     lv_line_set_y_invert(line, str->invert_enable);
     lv_obj_align_to(line,my_position_dad , str->position, str->x_ofs, str->y_ofs);
     return line;
 }

static lv_point_t vertical_line_points[] = {{0,0},{0,0}};
  /** \brief 竖直线创建函数
 *
 * \param my_position_dad:位置相对偏移的参考对象
 * \param position:位置对齐的形式
 * \param x_ofs: x偏移
 * \param y_ofs: y偏移
 * \param len: 线条的长度
 * \param line_color: 线条的颜色
 * \return 创建出来的线条对象
 *
 */
 lv_obj_t *my_vertical_line_create(const lv_obj_t *my_position_dad,lv_align_t position,lv_coord_t x_ofs,lv_coord_t y_ofs,uint16_t len,uint32_t line_color)
 {
     vertical_line_points[1].y = len;
     lv_obj_t *line = lv_line_create(lv_scr_act());
     lv_line_set_points(line,vertical_line_points,2);
     lv_obj_set_style_line_color(line,lv_color_hex(line_color),LV_STATE_DEFAULT);
     lv_obj_align_to(line,my_position_dad ,position,x_ofs,y_ofs);
     return line;
 }

 /** \brief 图片部件的初始化函数,传入图片部件样式结构体、依附的父对象、位置相对偏移的参考对象、图片源即可完成线条初始化
 *
 * \param my_dad:创建依附的父对象
 * \param my_position_dad:位置相对偏移的参考对象
 * \param str:图片部件样式结构体
 * \param img_source:图片源
 * \return 创建出来的图片对象
 *
 */
 lv_obj_t *my_img_init(const lv_obj_t *my_dad,const lv_obj_t *my_position_dad,my_str_img_t *str,const lv_img_dsc_t* img_source)
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
     if (str->bg_color) lv_obj_set_style_img_recolor(img, lv_color_hex(str->bg_color), LV_PART_MAIN);
     if (str->opa)  lv_obj_set_style_img_recolor_opa(img, str->opa, LV_PART_MAIN);
     if ( str->angle!=0 && (str->angle<=360 && str->angle>=-360))
     {
         lv_img_set_angle(img,str->angle*10);
     }

     lv_obj_align_to(img,my_position_dad , str->position, str->x_ofs, str->y_ofs);
     lv_obj_update_layout(img);
     return img;
 }

  /** \brief 按钮矩阵部件的初始化函数,传入按钮矩阵样式结构体、依附的父对象、位置相对偏移的参考对象、按钮数组即可完成线条初始化
 *
 * \param my_dad:创建依附的父对象
 * \param my_position_dad:位置相对偏移的参考对象
 * \param str:按钮矩阵部件样式结构体
 * \param btn_arr:按钮数组
 * \return 创建出来的按钮矩阵对象
 *
 */
 lv_obj_t *my_btnm_init(const lv_obj_t *my_dad,const lv_obj_t *my_position_dad,my_str_btnm_t *str,const char* btn_arr)
 {
     if (str == NULL) {
         return;     // 保护性编程，防止空指针
     }
     lv_obj_t *btnm = lv_btnmatrix_create(my_dad);
     lv_btnmatrix_set_map(btnm, btn_arr);
     if (str->width) lv_obj_set_width(btnm, str->width);
     if (str->height) lv_obj_set_height(btnm, str->height);
     if (str->text_font) lv_obj_set_style_text_font(btnm,str->text_font,LV_PART_ITEMS);
     if (str->bg_opa_to_zero)  lv_obj_set_style_bg_opa(btnm,0, LV_PART_MAIN);
     if (str->item_opa_to_zero)  lv_obj_set_style_bg_opa(btnm,0, LV_PART_ITEMS);
     if (str->border_disable) lv_obj_set_style_border_width(btnm,0,LV_PART_MAIN);
     if (str->shadow_disable) lv_obj_set_style_shadow_width(btnm,0,LV_PART_ITEMS);
     lv_obj_align_to(btnm,my_position_dad , str->position, str->x_ofs, str->y_ofs);
     return btnm;
 }

  /** \brief 按钮矩阵部件中的按键样式改变函数
 *
 * \param my_btnm:所要更改的按钮矩阵部件
 * \param my_btn_id:所要配置的按钮的序号
 * \param continue_set_value:按键连续配置数量（填0则否，若要连续配置则填入需要连续配置的个数（从0开始））
 * \param str:样式结构体
 * \return 无
 *
 */
 void my_btnm_btn_set_style(const lv_obj_t *my_btnm,uint16_t continue_set_value,const my_str_btnm_btn_t *str)
 {
     if (str == NULL) {
         return;     // 保护性编程，防止空指针
     }
     for(uint16_t i=0;i<continue_set_value;i++)
     {
         lv_btnmatrix_set_btn_width(my_btnm, i, str->width);
     }
 }


/** \brief 文本区域部件的创建初始化函数
 *
 * \param 创建依附的父对象
 * \param 对齐时参考的父对象
 * \param 样式结构体
 * \return 所创建的部件
 *
 */
 lv_obj_t *my_ta_init(lv_obj_t *my_dad,const lv_obj_t *my_position_dad,my_str_ta_t *str)
 {
     if (str == NULL) {
         return;     // 保护性编程，防止空指针
     }

     lv_obj_t *ta = lv_textarea_create(my_dad);
     if (str->width) lv_obj_set_width(ta, str->width);
     if (str->height) lv_obj_set_height(ta, str->height);
     if (str->text_font) lv_obj_set_style_text_font(ta,str->text_font,LV_PART_MAIN);
     lv_obj_align_to(ta,my_position_dad , str->position, str->x_ofs, str->y_ofs);
     if (str->max_length) lv_textarea_set_max_length(ta,str->max_length);
     if (str->one_line) lv_textarea_set_one_line(ta, true);
     if (str->password_mode) lv_textarea_set_password_mode(ta,true);
     if (str->password_show_time) lv_textarea_set_password_show_time(ta,str->password_show_time);
     if (str->accepted_chars) lv_textarea_set_accepted_chars(ta,str->accepted_chars);
     if (str->placeholder_text) lv_textarea_set_placeholder_text(ta, str->placeholder_text);
     lv_obj_update_layout(ta);

     return ta;
 }

/** \brief 键盘部件的创建初始化函数
 *
 * \param 创建依附的父对象
 * \param 样式结构体
 * \return 所创建的部件
 *
 */
 lv_obj_t *my_kb_init(lv_obj_t *my_dad,my_str_kb_t *str)
 {
     if (str == NULL) {
         return;     // 保护性编程，防止空指针
     }

     lv_obj_t *kb = lv_keyboard_create(my_dad);
     if (str->popovers) lv_keyboard_set_popovers(kb, true);
     if (str->kb_mode) lv_keyboard_set_mode(kb, str->kb_mode);
     lv_obj_update_layout(kb);

     return kb;
 }

 /** \brief 图片按钮部件的创建初始化函数
 *
 * \param 创建依附的父对象
 * \param 对齐时参考的父对象
 * \param 样式结构体
 * \return 所创建的部件
 *
 */
 lv_obj_t *my_imgbtn_init(const lv_obj_t *my_dad,const lv_obj_t *my_position_dad,my_str_imgbtn_t *str)
 {
     if (str == NULL) {
         return;     // 保护性编程，防止空指针
     }

     lv_obj_t *imgbtn = lv_imgbtn_create(my_dad);
     lv_obj_set_size(imgbtn, str->width, str->height);
     lv_imgbtn_set_src(imgbtn, str->state, NULL, str->src_mid, NULL);
     lv_obj_align_to(imgbtn,my_position_dad , str->position, str->x_ofs, str->y_ofs);
     lv_obj_update_layout(imgbtn);

     return imgbtn;
 }


 /** \brief 选项卡部件的创建初始化函数
 *
 * \param 创建依附的父对象
 * \param 对齐时参考的父对象
 * \param 样式结构体
 * \return 所创建的部件
 *
 */
 lv_obj_t *my_tabview_init(const lv_obj_t *my_dad,const lv_obj_t *my_position_dad,my_str_tabview_t *str)
 {
     if (str == NULL) {
         return;     // 保护性编程，防止空指针
     }

     lv_obj_t *tabview = lv_tabview_create(my_dad,str->tab_pos,str->tab_size);
     if (str->text_font) lv_obj_set_style_text_font(tabview,str->text_font,LV_STATE_DEFAULT);

     lv_obj_t *btn = lv_tabview_get_tab_btns(tabview);
     if (str->default_bg_color) lv_obj_set_style_bg_color(btn, lv_color_hex(str->default_bg_color), LV_PART_ITEMS|LV_STATE_DEFAULT);
     if (str->default_bg_opa) lv_obj_set_style_bg_opa(btn, str->default_bg_opa, LV_PART_ITEMS|LV_STATE_DEFAULT);
     if (str->default_text_color) lv_obj_set_style_text_color(btn, lv_color_hex(str->default_text_color), LV_PART_ITEMS|LV_STATE_DEFAULT);

     if (str->checked_bg_color)
     {
         lv_obj_set_style_bg_color(btn, lv_color_hex(str->checked_bg_color), LV_PART_ITEMS|LV_STATE_CHECKED);
         lv_obj_set_style_border_width(btn, 0, LV_PART_ITEMS| LV_STATE_CHECKED);
     }
     if (str->checked_bg_opa) lv_obj_set_style_bg_opa(btn, str->checked_bg_opa, LV_PART_ITEMS|LV_STATE_CHECKED);
     if (str->checked_text_color) lv_obj_set_style_text_color(btn, lv_color_hex(str->checked_text_color), LV_PART_ITEMS|LV_STATE_CHECKED);

     lv_obj_t *obj = lv_tabview_get_content(tabview);
     if (str->main_bg_color) lv_obj_set_style_bg_color(obj, lv_color_hex(str->main_bg_color), LV_STATE_DEFAULT);
     if (str->main_bg_opa) lv_obj_set_style_bg_opa(obj, str->main_bg_opa, LV_STATE_DEFAULT);

     lv_obj_update_layout(tabview);
     return tabview;
}


 /** \brief 窗口部件的创建初始化函数
 *
 * \param 创建依附的父对象
 * \param 对齐时参考的父对象
 * \param 样式结构体
 * \return 所创建的部件
 *
 */
 lv_obj_t *my_win_init(const lv_obj_t *my_dad,const lv_obj_t *my_position_dad,my_str_win_t *str)
 {
     if (str == NULL) {
         return;     // 保护性编程，防止空指针
     }

     lv_obj_t *win = lv_win_create(my_dad,str->header_height);
     if (str->width) lv_obj_set_width(win, str->width);
     if (str->height) lv_obj_set_height(win, str->height);
     lv_obj_align_to(win,my_position_dad , str->position, str->x_ofs, str->y_ofs);
     if (str->border_width) lv_obj_set_style_border_width(win, str->border_width, LV_STATE_DEFAULT);
     if (str->border_color) lv_obj_set_style_border_color(win,lv_color_hex(str->border_color), LV_STATE_DEFAULT);
     if (str->border_opa) lv_obj_set_style_border_opa(win,str->border_opa, LV_STATE_DEFAULT);
     if (str->border_radius) lv_obj_set_style_radius(win, str->border_radius, LV_STATE_DEFAULT);

     lv_obj_update_layout(win);
     return win;
}

 /** \brief 往窗口添加按钮函数
 *
 * \param target_win:目标窗口
 * \param icon:按钮图标
 * \param opa:按钮透明度
 * \return 所创建的部件
 *
 */
lv_obj_t *my_win_add_btn(lv_obj_t* target_win,const char* icon,lv_coord_t btn_w,lv_coord_t opa,lv_coord_t shadow_width,uint32_t text_color_default,uint32_t text_color_checked)
{
    lv_obj_t *win_btn = lv_win_add_btn(target_win, icon,btn_w);
    lv_obj_set_style_bg_opa(win_btn, opa, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(win_btn, shadow_width, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(win_btn, lv_color_hex(text_color_default), LV_STATE_DEFAULT);
    if(text_color_checked != 0x1000000) lv_obj_set_style_text_color(win_btn, lv_color_hex(text_color_checked), LV_STATE_PRESSED);
    return win_btn;
}

static const char *btns[] = { " ", " ", "OK", "" };

 /** \brief 消息框部件的创建初始化函数
 *
 * \param 创建依附的父对象
 * \param 对齐时参考的父对象
 * \param 样式结构体
 * \return 所创建的部件
 *
 */
 lv_obj_t *my_msgbox_init(const lv_obj_t *my_dad,const lv_obj_t *my_position_dad,my_str_msgbox_t *str)
 {
     if (str == NULL) {
         return;     // 保护性编程，防止空指针
     }

     msgbox = lv_msgbox_create(my_dad,str->title,str->txt,str->btn_txt,str->btn_close);
     if (str->width) lv_obj_set_width(msgbox, str->width);
     if (str->height) lv_obj_set_height(msgbox, str->height);
     lv_obj_align_to(msgbox,my_position_dad , str->position, str->x_ofs, str->y_ofs);
     if (str->border_disable) lv_obj_set_style_border_width(msgbox,0,LV_STATE_DEFAULT);
     if (str->shadow_width) lv_obj_set_style_shadow_width(msgbox, str->shadow_width, LV_STATE_DEFAULT);
     if (str->shadow_color) lv_obj_set_style_shadow_color(msgbox,lv_color_hex(str->shadow_color), LV_STATE_DEFAULT);
     if (str->pad_top) lv_obj_set_style_pad_top(msgbox,str->pad_top,LV_STATE_DEFAULT);
     if (str->pad_left) lv_obj_set_style_pad_left(msgbox,str->pad_left,LV_STATE_DEFAULT);

     lv_obj_t *title = lv_msgbox_get_title(msgbox);
     if (str->title_font) lv_obj_set_style_text_font(title,str->title_font,LV_STATE_DEFAULT);
     if (str->title_color) lv_obj_set_style_text_color(title, lv_color_hex(str->title_color),LV_STATE_DEFAULT);

     lv_obj_t *content = lv_msgbox_get_content(msgbox);
     if (str->content_font) lv_obj_set_style_text_font(content,str->content_font,LV_STATE_DEFAULT);
     if (str->content_color) lv_obj_set_style_text_color(content, lv_color_hex(str->content_color), LV_STATE_DEFAULT);
     if (str->content_pad_top) lv_obj_set_style_pad_top(content,str->content_pad_top,LV_STATE_DEFAULT);

     lv_obj_t *btn = lv_msgbox_get_btns(msgbox);
     if (str->btn_opa_enable) lv_obj_set_style_bg_opa(btn, 0, LV_PART_ITEMS);
     if (str->btn_shadow_disable) lv_obj_set_style_shadow_width(btn, 0, LV_PART_ITEMS);
     if (str->btn_color_default) lv_obj_set_style_text_color(btn, lv_color_hex(str->btn_color_default),LV_PART_ITEMS);
     if (str->btn_color_checked) lv_obj_set_style_text_color(btn, lv_color_hex(str->btn_color_checked),LV_PART_ITEMS|LV_STATE_PRESSED);
     if (str->btn_font) lv_obj_set_style_text_font(btn,str->btn_font,LV_PART_ITEMS);

     lv_obj_add_flag(msgbox, LV_OBJ_FLAG_HIDDEN);
     lv_obj_update_layout(msgbox);
     return msgbox;
}

static void slider_event_cb(lv_event_t *e)
{
    lv_obj_t *target = lv_event_get_target(e);                                      /* 获取触发源 */
    lv_event_code_t code = lv_event_get_code(e);                                    /* 获取事件类型 */
    static uint8_t flag = 0;   //音量过高标志位
    if(code == LV_EVENT_VALUE_CHANGED)
    {
        lv_label_set_text_fmt(slider_label, "%d%%", lv_slider_get_value(target));   /* 获取当前值，更新音量百分比 */

        if((lv_slider_get_value(target) > 80) && flag == 0)                                        /* 音量大于80% */
        {
            lv_obj_clear_flag(msgbox, LV_OBJ_FLAG_HIDDEN);
            flag = 1;
        }
        else if(lv_slider_get_value(target) <= 80)
        {
            flag = 0;
        }
    }
}

static void msgbox_event_cb(lv_event_t *e)
{
    lv_obj_t *target = lv_event_get_current_target(e);

    if(lv_msgbox_get_active_btn(target) == 2)
    {
        lv_obj_add_flag(msgbox, LV_OBJ_FLAG_HIDDEN);
    }
}


void my_gui(void)
{
    lv_obj_t *act = lv_scr_act();

    my_str_slider_t my_str_slider = {0};
    my_str_slider.width = scr_act_width()/2;
    my_str_slider.height = 20;
    my_str_slider.position = LV_ALIGN_CENTER;
    my_str_slider.right_value = 50;
    lv_obj_t *slider = my_slider_init(act,act,&my_str_slider);
    lv_obj_add_event_cb(slider,slider_event_cb,LV_EVENT_VALUE_CHANGED,NULL);

    slider_label = my_label_text_create(act,slider,LV_ALIGN_OUT_RIGHT_MID, 20, 0,"50%",&lv_font_montserrat_20);
    my_label_text_create(act,slider,LV_ALIGN_OUT_LEFT_MID, -20, 0,LV_SYMBOL_VOLUME_MAX,&lv_font_montserrat_20);

    my_str_msgbox_t my_str_msgbox = {0};
    my_str_msgbox.title = LV_SYMBOL_WARNING " Notice";
    my_str_msgbox.txt = "Excessive volume may damage hearing.";
    my_str_msgbox.btn_txt = btns;
    my_str_msgbox.border_disable = 1;
    my_str_msgbox.btn_close = 0;
    my_str_msgbox.width = 300;
    my_str_msgbox.height = 170;
    my_str_msgbox.position = LV_ALIGN_CENTER;
    my_str_msgbox.shadow_width = 20;
    my_str_msgbox.shadow_color = 0xa9a9a9;
    my_str_msgbox.pad_top = 18;
    my_str_msgbox.pad_left = 20;
    my_str_msgbox.title_font = &lv_font_montserrat_20;
    my_str_msgbox.title_color = 0xff0000;
    my_str_msgbox.content_font = &lv_font_montserrat_20;
    my_str_msgbox.content_color = 0x6c6c6c;
    my_str_msgbox.content_pad_top = 15;
    my_str_msgbox.btn_opa_enable = 1;
    my_str_msgbox.btn_shadow_disable = 1;
    my_str_msgbox.btn_font = &lv_font_montserrat_20;
    my_str_msgbox.btn_color_default = 0x2271df;
    my_str_msgbox.btn_color_checked = 0xff0000;
    msgbox = my_msgbox_init(act,act,&my_str_msgbox);
    lv_obj_add_event_cb(msgbox, msgbox_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

}



