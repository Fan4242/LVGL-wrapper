#ifndef _MY_GUI_H
#define _MY_GUI_H

#include "lvgl.h"



//基础部件配置样式结构体
typedef struct my_str_obj
{
    lv_align_t position;             //与父对象的位置关系
    lv_coord_t x_ofs;                //相对于父对象的x轴偏移
    lv_coord_t y_ofs;                //相对于父对象的y轴偏移
    lv_coord_t width;                //宽度
    lv_coord_t height;               //高度
    uint32_t bg_color;               //主体部分的颜色
    lv_opa_t bg_opa;                 //主体部分的透明度
    lv_coord_t radius;               //主体部分的圆角
    bool border_disable;             //是否去除主体边框
    bool scrollbar_disable;          //是否去除主体滑动条

}my_str_obj_t;


//滑块部件配置样式结构体
typedef struct str_slider
{
    lv_align_t position;             //与父对象的位置关系
    lv_coord_t x_ofs;                //相对于父对象的x轴偏移
    lv_coord_t y_ofs;                //相对于父对象的y轴偏移
    lv_coord_t width;                //滑块的宽度
    lv_coord_t height;               //滑块的高度
    uint32_t main_color;            //滑块主体部分的颜色
    uint32_t indicator_color;       //滑块显示器部分颜色
    bool konb_disable;               //是否关闭手柄
    lv_anim_enable_t anim_enable;    //是否开启动画
    lv_slider_mode_t slider_mode;    //滑块的类型
    int32_t left_value;             //滑块的起始左值（在滑块模式为双头时有效）
    int32_t right_value;            //滑块的起始右值
    int32_t min_value;              //滑块的范围最小值
    int32_t max_value;              //滑块的范围最大值
}my_str_slider_t;

//圆弧部件的两种使用模式（一种是作为圆弧旋钮，另一种是指示状态）
typedef enum{
    MY_ARC_KNOB,
    MY_ARC_MONITOR
} m_arc_mode;

//圆弧部件样式配置结构体
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

//线条部件样式配置结构体
typedef struct my_str_line_t
{
    const lv_point_t *line_points;   //线条的点集
    uint16_t point_num;             //线条的点的个数
    lv_coord_t line_width;           //线条的宽度
    uint32_t line_color;           //线条的颜色
    bool invert_enable;             //是否反转y轴坐标
    bool rounded_enable;             //是否添加圆角
    lv_align_t position;             //与参考对象的位置关系
    lv_coord_t x_ofs;                //相对于参考对象的x轴偏移
    lv_coord_t y_ofs;                //相对于参考对象的y轴偏移

}my_str_line_t;

 //图片部件样式配置结构体
typedef struct my_str_img_t
{
    lv_align_t position;             //与父对象的位置关系
    lv_coord_t x_ofs;                //相对于父对象的x轴偏移
    lv_coord_t y_ofs;                //相对于父对象的y轴偏移
    uint16_t zoom;                  //图片的缩放比例
    uint32_t bg_color;              //图片的颜色变化
    lv_opa_t opa;                    //图片的透明度
    int16_t angle;                  //图片的旋转角度（范围限定为正的360度和负的360度）
    lv_coord_t pivot_x;             //图片的x轴中心点
    lv_coord_t pivot_y;             //图片的y轴中心点
}my_str_img_t;

//按钮矩阵部件样式配置结构体
typedef struct my_str_btnm_t
{
    lv_align_t position;             //与父对象的位置关系
    lv_coord_t x_ofs;                //相对于父对象的x轴偏移
    lv_coord_t y_ofs;                //相对于父对象的y轴偏移
    lv_coord_t width;                //按钮矩阵的宽度
    lv_coord_t height;               //按钮矩阵的高度
    lv_font_t *text_font;             //按钮矩阵中按钮的字体大小
    bool bg_opa_to_zero;             //主体部分的透明度
    bool item_opa_to_zero;           //按键部分的透明度
    bool border_disable;             //是否去除主体边框
    bool shadow_disable;              //是否去除按键部分的阴影
}my_str_btnm_t;

//按钮矩阵按钮样式配置结构体
typedef struct my_str_btnm_btn_t
{
    uint8_t width;             //按键的相对宽度

}my_str_btnm_btn_t;

//文本区域部件配置样式结构体
typedef struct my_ta_obj
{
    lv_align_t position;             //与父对象的位置关系
    lv_coord_t x_ofs;                //相对于父对象的x轴偏移
    lv_coord_t y_ofs;                //相对于父对象的y轴偏移
    lv_coord_t width;                //宽度
    lv_coord_t height;               //高度
    lv_font_t *text_font;            //输入的字符字体
    bool password_mode;             //是否开启密码模式
    uint16_t password_show_time;    //密码模式下字符显示时长（ms）
    bool one_line;                  //是否一行显示
    const char *placeholder_text;   //文字占位符
    const char *accepted_chars;     //允许输入的字符限制
    uint32_t max_length;            //允许输入的字符串最大长度

}my_str_ta_t;


void my_gui(void);
lv_obj_t *my_obj_init(lv_obj_t *my_dad,const lv_obj_t *my_position_dad,my_str_obj_t *str);
lv_obj_t *my_slider_init(lv_obj_t *my_dad,const lv_obj_t *my_position_dad,my_str_slider_t *str);
void my_arc_init(lv_obj_t *my_main,const lv_obj_t *my_dad,str_arc *str);
lv_obj_t *label_text_create(const lv_obj_t *my_dad,const lv_obj_t *position_dad,lv_align_t position,lv_coord_t x_ofs,lv_coord_t y_ofs,const char* label_text,lv_font_t *font);
lv_obj_t *my_line_init(const lv_obj_t *my_dad,const lv_obj_t *my_option_dad,my_str_line_t *str);
lv_obj_t *my_img_init(const lv_obj_t *my_dad,const lv_obj_t *my_option_dad,my_str_img_t *str,const lv_img_dsc_t* img_source);
lv_obj_t *my_btnm_init(const lv_obj_t *my_dad,const lv_obj_t *my_option_dad,my_str_btnm_t *str,const char* btn_arr);
void my_btnm_btn_set_style(const lv_obj_t *my_btnm,uint16_t continue_set_value,const my_str_btnm_btn_t *str);
lv_obj_t *my_ta_init(lv_obj_t *my_dad,const lv_obj_t *my_position_dad,my_str_ta_t *str);

#endif // _MY_GUI_H
