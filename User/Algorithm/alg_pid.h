/*
 * @Project: Infantry Code
 *
 * @Author: GDDG08
 * @Date: 2021-12-31 17:37:14
 * @LastEditors: Hatrix
 * @LastEditTime: 2024-01-14 21:05:37
 */

#ifndef ALG_PID_H
#define ALG_PID_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "lib_math.h"
#include "lib_filter.h"

    typedef enum
    {
        PID_POSITION = 0u,
        PID_DELTA = 1u
    } PID_ModeEnum;

    typedef struct
    {
        float ref;
        float fdb;
        float err[3];
        float err_fdf[3]; // Feedforard
        float err_lim;    // Integral anti-windup
        float sum;
        float output_fdf; // Feedforard output
        float output;
        float err_watch;

        Filter_LowPassTypeDef d_fil;
        Filter_LowPassTypeDef kf1_fil;
        Filter_LowPassTypeDef kf2_fil;

    } PID_DataTypeDef;

    typedef struct
    {
        PID_ModeEnum pid_mode;
        float kp;
        float ki;
        float kd;
        float kf_1;                                 // Feedforward param
        float kf_2;
        float sum_max;
        float output_max;
        Filter_LowPassParamTypeDef d_fil_param;     // Kd filter param
        Filter_LowPassParamTypeDef kf1_fil_param;   // Feedforawrd filter param
        Filter_LowPassParamTypeDef kf2_fil_param;

    } PID_ParamTypeDef;

    void PID_Init(PID_ParamTypeDef *pparam, PID_ModeEnum mode, float kp, float ki, float kd, float kf_1, float kf_2, float sum_max, float output_max, float kd_fil_param, float kf1_fil_param, float kf2_fil_param);
    void PID_Calc(PID_DataTypeDef *pid, PID_ParamTypeDef *para);
    float PID_GetRef(PID_DataTypeDef *pid);
    void PID_SetRef(PID_DataTypeDef *pid, float ref);
    void PID_AddRef(PID_DataTypeDef *pid, float inc);
    float PID_GetFdb(PID_DataTypeDef *pid);
    void PID_SetFdb(PID_DataTypeDef *pid, float fdb);
    float PID_GetOutput(PID_DataTypeDef *pid);
    void PID_Clear(PID_DataTypeDef *pid);

#ifdef __cplusplus
}
#endif

#endif
