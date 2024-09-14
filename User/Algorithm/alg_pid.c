/*
 * @Project: Infantry Code
 *
 * @Author: GDDG08
 * @Date: 2021-12-31 17:37:14
 * @LastEditors: Hatrix 3113624526@qq.com
 * @LastEditTime: 2024-02-20 00:39:05
 */

#include "alg_pid.h"

void PID_Init(PID_ParamTypeDef *pparam, PID_ModeEnum mode, float kp, float ki, float kd, float kf_1, float kf_2, float sum_max, float output_max, float kd_fil_param, float kf1_fil_param, float kf2_fil_param)
{
    pparam->pid_mode = mode;
    pparam->kp = kp;
    pparam->ki = ki;
    pparam->kd = kd;
    pparam->kf_1 = kf_1;
    pparam->kf_2 = kf_2;
    pparam->sum_max = sum_max;
    pparam->output_max = output_max;
    Filter_LowPassInit(kd_fil_param, &pparam->d_fil_param);
    Filter_LowPassInit(kf1_fil_param, &pparam->kf1_fil_param);
    Filter_LowPassInit(kf2_fil_param, &pparam->kf2_fil_param);
}

void PID_Calc(PID_DataTypeDef *pid, PID_ParamTypeDef *pparam)
{
    if (pparam->pid_mode == PID_POSITION)
    {
        // Calculate the difference
        float dError, Error, ref_dError, ref_ddError;
        Error = pid->ref - pid->fdb;
        pid->err[2] = pid->err[1];
        pid->err[1] = pid->err[0];
        pid->err[0] = Error;
        pid->err_watch = Error;
        dError = Math_Differential(pid->err, 1);

        pid->err_fdf[2] = pid->err_fdf[1];
        pid->err_fdf[1] = pid->err_fdf[0];
        pid->err_fdf[0] = pid-> ref;

        ref_dError = Math_Differential(pid->err_fdf, 1);
        ref_ddError = Math_Differential(pid->err_fdf, 2);

        // Calculate the integral and integra anti-windup
        if (pparam->kp == 0)
        {
            pid->sum = pid->sum + Error;
        }
        else
        {
            pid->sum = pid->sum + Error + pid->err_lim / pparam->kp;
        }
        LimitMax(pid->sum, pparam->sum_max);

        // Calculation results kf1_filter
        pid->output_fdf = Filter_LowPass((pparam->kf_1 * ref_dError), &pparam->kf1_fil_param, &pid->kf1_fil) + Filter_LowPass((pparam->kf_2 * ref_ddError), &pparam->kf2_fil_param, &pid->kf2_fil);
        pid->output = pparam->kp * Error + pparam->ki * pid->sum + pparam->kd * Filter_LowPass(dError, &pparam->d_fil_param, &pid->d_fil);
        pid->output += pid->output_fdf;

        float temp_limit = pid->output;
        LimitMax(pid->output, pparam->output_max);
        pid->err_lim = pid->output - temp_limit;
    }

    else if (pparam->pid_mode == PID_DELTA)
    {
        // Calculate the difference
        float dError, ddError, Error, ref_dError, ref_ddError;
        Error = pid->ref - pid->fdb;
        pid->err[2] = pid->err[1];
        pid->err[1] = pid->err[0];
        pid->err[0] = Error;
        pid->err_watch = Error;
        dError = Math_Differential(pid->err, 1);
        ddError = Math_Differential(pid->err, 2);

        pid->err_fdf[2] = pid->err_fdf[1];
        pid->err_fdf[1] = pid->err_fdf[0];
        pid->err_fdf[0] = pid->ref;

        ref_dError = Math_Differential(pid->err_fdf, 1);
        ref_ddError = Math_Differential(pid->err_fdf, 2);

        // Calculate the integral and integral anti-windup
        if (pparam->kp == 0)
        {
            pid->sum = Error;
        }
        else
        {
            pid->sum = Error + pid->err_lim / pparam->kp;
        }
        LimitMax(pid->sum, pparam->sum_max);

        // Calculation results kf1_filter
        pid->output_fdf = Filter_LowPass((pparam->kf_1 * ref_dError), &pparam->kf1_fil_param, &pid->kf1_fil) + Filter_LowPass((pparam->kf_2 * ref_ddError), &pparam->kf2_fil_param, &pid->kf2_fil);
        pid->output = pparam->kp * dError + pparam->ki * pid->sum + pparam->kd * Filter_LowPass(ddError, &pparam->d_fil_param, &pid->d_fil);
        pid->output += pid->output_fdf;
    }

    // Output limiting
    float temp_limit = pid->output;
    LimitMax(pid->output, pparam->output_max);
    pid->err_lim = pid->output - temp_limit;
}

float PID_GetRef(PID_DataTypeDef *pid)
{
    return pid->ref;
}

void PID_SetRef(PID_DataTypeDef *pid, float ref)
{
    pid->ref = ref;
}

void PID_AddRef(PID_DataTypeDef *pid, float inc)
{
    pid->ref += inc;
}

float PID_GetFdb(PID_DataTypeDef *pid)
{
    return pid->fdb;
}

void PID_SetFdb(PID_DataTypeDef *pid, float fdb)
{
    pid->fdb = fdb;
}

float PID_GetOutput(PID_DataTypeDef *pid)
{
    return pid->output;
}

void PID_Clear(PID_DataTypeDef *pid)
{
    pid->ref = 0;
    pid->fdb = 0;
    pid->err[0] = 0;
    pid->err[1] = 0;
    pid->err[2] = 0;
    pid->err_fdf[0] = 0;
    pid->err_fdf[1] = 0;
    pid->err_fdf[2] = 0;
    pid->err_lim = 0;
    pid->sum = 0;
    pid->output_fdf = 0;
    pid->output = 0;
    pid->err_watch = 0;
}
