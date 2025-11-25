#include "my_gui.h"


/* 获取当前活动屏幕的宽高 */
#define scr_act_width() lv_obj_get_width(lv_scr_act())
#define scr_act_height() lv_obj_get_height(lv_scr_act())

lv_obj_t *label1;
lv_obj_t *label2;
lv_obj_t *arc2;

static void event_cb(lv_event_t *e)
{
    lv_obj_t *target = lv_event_get_target(e);
    int16_t arc_value = lv_arc_get_value(target);
    lv_label_set_text_fmt( label1, "%d%%", arc_value ) ;
    lv_label_set_text_fmt( label2, "%d%%", arc_value ) ;
    lv_arc_set_value(arc2,arc_value);
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

 /** \brief 圆弧部件的初始化函数,传入滑块本身、依附的父对象、想要的滑块类型即可完成滑块形式初始化
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
  * \return 所创建的标签对象
  *
  */
void *label_text_create(const lv_obj_t *my_dad,const lv_obj_t *position_dad,lv_align_t position,lv_coord_t x_ofs,lv_coord_t y_ofs,const char* label_text)
{
    lv_obj_t *label = lv_label_create(my_dad);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_align_to(label,position_dad ,position, x_ofs, y_ofs);
    lv_label_set_text( label, label_text);
    return label;
}

void my_gui(void)
{
    lv_obj_t *act = lv_scr_act();

    str_arc my_arc1 = {0};
    lv_obj_t *arc1 = lv_arc_create(act);
    my_arc1.width = scr_act_height()*3/8;
    my_arc1.height = scr_act_height()*3/8;
    my_arc1.arc_width = 20;
    my_arc1.x_ofs = scr_act_width()/4;
    my_arc1.position = LV_ALIGN_LEFT_MID;
    my_arc_init(arc1,act,&my_arc1);
    label1 = label_text_create(act,arc1,LV_ALIGN_CENTER,0,0,"0%");
    lv_obj_add_event_cb(arc1,event_cb,LV_EVENT_VALUE_CHANGED,NULL);

    str_arc my_arc2 = {0};
    arc2 = lv_arc_create(act);
    my_arc2.width = scr_act_height()*3/8;
    my_arc2.height = scr_act_height()*3/8;
    my_arc2.arc_width = 20;
    my_arc2.rotation = 270;
    my_arc2.x_ofs = -scr_act_width()/4;
    my_arc2.position = LV_ALIGN_RIGHT_MID;
    my_arc2.bg_start_v = 0;
    my_arc2.bf_end_v = 360;
    my_arc2.my_arc_mode = MY_ARC_MONITOR;
    my_arc_init(arc2,act,&my_arc2);
    label2 = label_text_create(act,arc2,LV_ALIGN_CENTER,0,0,"0%");


}



