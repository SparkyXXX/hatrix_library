/*
 * @Project: Infantry Code
 *
 * @Author: GDDG08
 * @Date: 2021-12-31 17:37:14
 * @LastEditors: Hatrix 3113624526@qq.com
 * @LastEditTime: 2024-02-20 10:21:50
 */

#ifndef APP_MOTOR_TEST_H
#define APP_MOTOR_TEST_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "alg_pid.h"
#include "protocol_motor.h"
#include "periph_motor_can.h"

    typedef struct
    {
        Motor_GroupDataTypeDef *motor_group;
        Motor_DataTypeDef *motor;
        PID_ParamTypeDef speed_param, angle_param;
        PID_DataTypeDef speed, angle;
    } Motor_ControlTypeDef;

    extern Motor_ControlTypeDef Motor_ControlTest;

    void MotorTest_Init(Motor_ControlTypeDef *pmotor_control, Motor_GroupDataTypeDef *pmotor_group, Motor_DataTypeDef *pmotor);
    void MotorTest_Control(Motor_ControlTypeDef *pmotor_control);

#endif

#ifdef __cplusplus
}
#endif
