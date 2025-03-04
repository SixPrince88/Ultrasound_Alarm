#include "pid.h"

// pid计算
float pid_calc(PIDController_Obj *pid, float error)
{
    // uint32_t timestamp_now = htim2.Instance->CNT;

    // float Ts;
    // // 时间溢出处理
    // if (timestamp_now > pid->timestamp_prev) {
    //     Ts = (timestamp_now - pid->timestamp_prev) * 1e-3f;
    // } else {
    //     Ts = (0xFFFFFFFF - pid->timestamp_prev + timestamp_now) * 1e-3f;
    // }
    float Ts = 1;

    // 比例环
    float proportional = pid->P * error;

    // 积分环
    float integral = pid->integral_prev + pid->I * Ts * 0.5f * (error + pid->error_prev);
    if (pid->limit > 0)
    {
        integral = _limit(integral, -pid->limit, pid->limit);
    }

    // 微分环
    float derivative = pid->D * (error - pid->error_prev) / Ts;

    // 计算输出
    float output = proportional + integral + derivative;
    if (pid->limit > 0)
    {
        output = _limit(output, -pid->limit, pid->limit);
    }

    // 如果需要限制输出速率
    if (pid->ramp > 0)
    {
        // 通过斜坡输出限制加速度
        float output_rate = (output - pid->output_prev) / Ts;
        if (output_rate > pid->ramp)
            output = pid->output_prev + pid->ramp * Ts;
        else if (output_rate < -pid->ramp)
            output = pid->output_prev - pid->ramp * Ts;
    }

    // 保持变量用于下一次计算
    pid->integral_prev = integral;
    pid->output_prev = output;
    pid->error_prev = error;
    // pid->timestamp_prev = timestamp_now;
    return output;
}

void pid_reset(PIDController_Obj *pid)
{
    pid->integral_prev = 0.0f;
    pid->output_prev = 0.0f;
    pid->error_prev = 0.0f;
}
