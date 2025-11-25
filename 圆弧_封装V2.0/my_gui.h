#ifndef _MY_GUI_H
#define _MY_GUI_H

#include "lvgl.h"

typedef struct str_slider
{
    lv_align_t position;             //与父对象的位置关系
    lv_coord_t x_ofs;                //相对于父对象的x轴偏移
    lv_coord_t y_ofs;                //相对于父对象的y轴偏移
    lv_coord_t width;                //滑块的宽度
    lv_coord_t height;               //滑块的高度
    lv_anim_enable_t anim_enable;    //是否开启动画
    lv_slider_mode_t slider_mode;    //滑块的类型
    int32_t left_value;             //滑块的起始左值（在滑块模式为双头时有效）
    int32_t right_value;            //滑块的起始右值
    int32_t min_value;              //滑块的范围最小值
    int32_t max_value;              //滑块的范围最大值
}str_slider;

//圆弧部件的两种使用模式（一种是作为圆弧旋钮，另一种是指示状态）
typedef enum{
    MY_ARC_KNOB,
    MY_ARC_MONITOR
} m_arc_mode;

typedef struct str_arc
{
    lv_align_t position;             //与父对象的位置关系
    lv_coord_t x_ofs;                //相对于父对象的x轴偏移
    lv_coord_t y_ofs;                //相对于父对象的y轴偏移
    lv_coord_t width;                //圆弧的宽度
    lv_coord_t height;               //圆弧的高度
    lv_coord_t arc_width;            //背景弧以及前景弧的宽度
    lv_arc_mode_t arc_mode;          //圆弧的类型
    int32_t start_value;            //圆弧的起始值
    int32_t min_value;              //圆弧的范围最小值
    int32_t max_value;              //圆弧的范围最大值
    int16_t bg_start_v;             //圆弧背景的起始角度值
    int16_t bf_end_v;               //圆弧背景的终止角度值
    uint16_t rotation;              //圆弧旋转角度
    m_arc_mode my_arc_mode;
}str_arc;


void my_gui(void);
void my_slider_init(lv_obj_t *sld_main,const lv_obj_t *sld_dad,str_slider *str);
void my_arc_init(lv_obj_t *my_main,const lv_obj_t *my_dad,str_arc *str);
void *label_text_create(const lv_obj_t *sld_dad,const lv_obj_t *position_dad,lv_align_t position,lv_coord_t x_ofs,lv_coord_t y_ofs,const char* label_text);

#endif // _MY_GUI_H
