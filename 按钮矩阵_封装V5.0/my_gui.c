#include "my_gui.h"


/* 获取当前活动屏幕的宽高 */
#define scr_act_width() lv_obj_get_width(lv_scr_act())
#define scr_act_height() lv_obj_get_height(lv_scr_act())

lv_obj_t *label1;
lv_obj_t *label_input;
lv_obj_t *img1;
lv_obj_t *obj1;

LV_IMG_DECLARE(img_user);

/* 按钮矩阵数组 */
static const char *num_map[] = { "1", "2", "3", "\n",
                                 "4", "5", "6", "\n",
                                 "7", "8", "9", "\n",
                                 "#", "0", "%", "" };

static lv_point_t line_point_arr[] = {{0,0},{0,200}};

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
lv_obj_t *label_text_create(const lv_obj_t *my_dad,const lv_obj_t *position_dad,lv_align_t position,lv_coord_t x_ofs,lv_coord_t y_ofs,const char* label_text,lv_font_t *font)
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
 * \param my_option_dad:创建依附的父对象
 * \param str:位置相对偏移的参考对象
 * \return 创建出来的线条对象
 *
 */
 lv_obj_t *my_line_init(const lv_obj_t *my_dad,const lv_obj_t *my_option_dad,my_str_line_t *str)
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
     lv_obj_align_to(line,my_option_dad , str->position, str->x_ofs, str->y_ofs);
     return line;
 }


 /** \brief 图片部件的初始化函数,传入图片部件样式结构体、依附的父对象、位置相对偏移的参考对象、图片源即可完成线条初始化
 *
 * \param my_dad:创建依附的父对象
 * \param my_option_dad:位置相对偏移的参考对象
 * \param str:图片部件样式结构体
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
     if (str->bg_color) lv_obj_set_style_img_recolor(img, lv_color_hex(str->bg_color), LV_PART_MAIN);
     if (str->opa)  lv_obj_set_style_img_recolor_opa(img, str->opa, LV_PART_MAIN);
     if ( str->angle!=0 && (str->angle<=360 && str->angle>=-360))
     {
         lv_img_set_angle(img,str->angle*10);
     }

     lv_obj_align_to(img,my_option_dad , str->position, str->x_ofs, str->y_ofs);
     lv_obj_update_layout(img);
     return img;
 }

  /** \brief 按钮矩阵部件的初始化函数,传入按钮矩阵样式结构体、依附的父对象、位置相对偏移的参考对象、按钮数组即可完成线条初始化
 *
 * \param my_dad:创建依附的父对象
 * \param my_option_dad:位置相对偏移的参考对象
 * \param str:按钮矩阵部件样式结构体
 * \param btn_arr:按钮数组
 * \return 创建出来的按钮矩阵对象
 *
 */
 lv_obj_t *my_btnm_init(const lv_obj_t *my_dad,const lv_obj_t *my_option_dad,my_str_btnm_t *str,const char* btn_arr)
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
     lv_obj_align_to(btnm,my_option_dad , str->position, str->x_ofs, str->y_ofs);
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



 static void event_cb(lv_event_t *e)
{
    uint8_t id;

    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (code == LV_EVENT_PRESSED)
    {
        id = lv_btnmatrix_get_selected_btn(target);
        lv_label_set_text(label_input,lv_btnmatrix_get_btn_text(target,id));
        lv_obj_align_to(label_input,obj1,LV_ALIGN_CENTER,0,0);
    }
}



void my_gui(void)
{
    lv_obj_t *act = lv_scr_act();

    my_str_btnm_t my_str_btnm = {0};
    my_str_btnm.width = scr_act_width()*2/5;
    my_str_btnm.height = scr_act_width()*2/5;
    my_str_btnm.position = LV_ALIGN_RIGHT_MID;
    my_str_btnm.x_ofs = -scr_act_width()/16;
    my_str_btnm.text_font = &lv_font_montserrat_30;
    my_str_btnm.bg_opa_to_zero = 1;
    my_str_btnm.item_opa_to_zero = 1;
    my_str_btnm.border_disable = 1;
    my_str_btnm.shadow_disable = 1;
    lv_obj_t *btnm = my_btnm_init(act,act,&my_str_btnm,num_map);
    lv_obj_add_event_cb(btnm,event_cb,LV_EVENT_PRESSED,NULL);

    my_str_btnm_btn_t my_btn_all = {0};
    my_btnm_btn_set_style(btnm,12,&my_btn_all);

    my_str_img_t my_str_img = {0};
    my_str_img.position = LV_ALIGN_CENTER;
    my_str_img.zoom = 256;
    my_str_img.bg_color = 0xf2f2f2;
    my_str_img.opa = 100;
    my_str_img.x_ofs = -scr_act_width()/4;
    my_str_img.y_ofs = -scr_act_height()/7;
    img1 = my_img_init(act,act,&my_str_img,&img_user);

    label1 = label_text_create(act,img1,LV_ALIGN_OUT_BOTTOM_MID,0,10,"USER",&lv_font_montserrat_30);

    my_str_obj_t my_str_obj = {0};
    my_str_obj.width = scr_act_width()/4;
    my_str_obj.height = scr_act_height()/12;
    my_str_obj.position = LV_ALIGN_OUT_BOTTOM_MID;
    my_str_obj.x_ofs = 0;
    my_str_obj.y_ofs = scr_act_height()/20;
    my_str_obj.bg_color = 0xcccccc;
    my_str_obj.bg_opa = 150;
    my_str_obj.radius = 20;
    my_str_obj.scrollbar_disable = 1;
    my_str_obj.border_disable = 1;
    obj1 = my_obj_init(act,label1,&my_str_obj);

    label_input = label_text_create(act,obj1,LV_ALIGN_CENTER,0,0,"",&lv_font_montserrat_30);

    my_str_line_t my_str_line = {0};
    my_str_line.line_points = line_point_arr;
    my_str_line.point_num = 2;
    my_str_line.position = LV_ALIGN_CENTER;
    my_str_line.line_color = 0xcdcdcd;
    lv_obj_t *line = my_line_init(act,act,&my_str_line);
}



