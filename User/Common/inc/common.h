#ifndef __COMMON_H__
#define __COMMON_H__

// 存放一些通用的宏定义
#define Limit(value, min, max) (((value) < (min)) ? (min) : (((value) > (max)) ? (max) : (value)))
#define ABS(x) (((x) > 0) ? (x) : -(x))

#define pi 3.14159265359

#endif
