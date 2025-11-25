#include "my_gui.h"
#include "lvgl.h"

/* 获取当前活动屏幕的宽高 */
#define scr_act_width() lv_obj_get_width(lv_scr_act())
#define scr_act_height() lv_obj_get_height(lv_scr_act())

lv_obj_t *label1;

typedef struct slider
{
    lv_align_t position;            //与父对象的位置关系
    lv_coord_t x_ofs;               //相对于父对象的x轴偏移
    lv_coord_t y_ofs;               //相对于父对象的y轴便宜
    lv_coord_t width;              //滑块的宽度
    lv_coord_t height;              //滑块的高度
    lv_anim_enable_t anim_enable;   //是否开启动画
    lv_slider_mode_t slider_mode;   //滑块的类型
    int32_t left_value;            //滑块的起始左值（在滑块模式为双头时有效）
    int32_t right_value;           //滑块的起始右值
    int32_t min_value;             //滑块的范围最小值
    int32_t max_value;             //滑块的范围最大值
}str_slider;

static void event_cb(lv_event_t *e)
{
    lv_obj_t *target = lv_event_get_target(e);
    lv_label_set_text_fmt( label1, "%d%%", lv_slider_get_value(target) ) ;
}


/** \brief 滑块部件的初始化函数,传入滑块本身、依附的父对象、想要的滑块类型即可完成滑块形式初始化
 *
 * \param 滑块部件自身
 * \param 滑块部件对齐时参考的父对象
 * \param 滑块部件样式结构体
 * \return 无
 *
 */
 void slider_init(lv_obj_t *sld_main,const lv_obj_t *sld_dad,str_slider *str)
 {
     if (str == NULL) {
         return;     // 保护性编程，防止空指针
     }
     lv_slider_set_mode(sld_main,str->slider_mode);
     if (str->width) lv_obj_set_width(sld_main, str->width);
     if (str->height) lv_obj_set_height(sld_main, str->height);
     lv_obj_align_to(sld_main,sld_dad , str->position, str->x_ofs, str->y_ofs);
     if (str->min_value || str->max_value) lv_slider_set_range(sld_main, str->min_value,str->max_value);
     if (str->right_value) lv_slider_set_value(sld_main,str->right_value,str->anim_enable);
     if (str->left_value)  lv_slider_set_left_value(sld_main, str->left_value, str->anim_enable);
     lv_obj_update_layout(sld_main);
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
void *label_text_create(const lv_obj_t *sld_dad,const lv_obj_t *position_dad,lv_align_t position,lv_coord_t x_ofs,lv_coord_t y_ofs,const char* label_text)
{
    lv_obj_t *label = lv_label_create(sld_dad);
    lv_label_set_text( label, label_text);
    lv_obj_align_to(label,position_dad ,position, x_ofs, y_ofs);
    return label;
}

void my_gui(void)
{
    str_slider my_str = {0};
    lv_obj_t *act = lv_scr_act();
    lv_obj_t *slider = lv_slider_create(act);
    my_str.width = scr_act_width()*3/5;
    my_str.x_ofs = 0;
    my_str.y_ofs = 0;
    my_str.position = LV_ALIGN_CENTER;
    slider_init(slider,act,&my_str);
    lv_obj_add_event_cb(slider,event_cb,LV_EVENT_VALUE_CHANGED,NULL);

    label1 = label_text_create(act,slider,LV_ALIGN_OUT_RIGHT_MID,15,0,"80%");
    lv_obj_t *label2 = label_text_create(act,slider,LV_ALIGN_OUT_LEFT_MID,-15,0,LV_SYMBOL_VOLUME_MAX);
}



