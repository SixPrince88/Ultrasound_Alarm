#ifndef LOWPASS_FILTER_H
#define LOWPASS_FILTER_H
#include <stdint.h>

// 参考了SimpleFoc
// 低通滤波器

typedef struct
{
    // float Tf; // 时间常数,单位毫秒,参数越大,滤波效果越强,相位(响应)越延迟
    float alpha;
    float y_prev;
} LowPassFilter_Obj;

// 中值滤波器计算
uint16_t Find_Median(uint16_t arr[], int size);

// 低通滤波器计算
float lpf_calc(LowPassFilter_Obj *lpf, float x);

// 低通滤波器复位
void lpf_reset(LowPassFilter_Obj *lpf, float x);

#endif
