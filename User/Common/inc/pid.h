#ifndef __PID_H_
#define __PID_H_

#define _limit(amt, low, high) ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))

typedef struct
{

    // 初始化参数
    float P;     // 比例系数
    float I;     // 积分系数
    float D;     // 微分系数
    float ramp;  // 输出值的最大变化速度;0=不限制
    float limit; // 输出限幅

    // 内部变量
    float error_prev;
    float output_prev;
    float integral_prev;
    unsigned long timestamp_prev;

} PIDController_Obj;

float pid_calc(PIDController_Obj *pid, float error);
void pid_reset(PIDController_Obj *pid);

#endif
