/*
 * @Project: Infantry Code
 *
 * @Author: GDDG08
 * @Date: 2021-12-31 17:37:14
 * @LastEditors: Hatrix 3113624526@qq.com
 * @LastEditTime: 2024-02-20 10:27:39
 */

#include "app_motor_test.h"

Motor_ControlTypeDef Motor_ControlTest;

/**
 * @brief      shooter control initialization
 * @param      NULL
 * @retval     NULL
 */
void MotorTest_Init(Motor_ControlTypeDef *pmotor_control, Motor_GroupDataTypeDef *pmotor_group, Motor_DataTypeDef *pmotor)
{
    pmotor_control->motor_group = pmotor_group;
    pmotor_control->motor = pmotor;
    PID_Init(&pmotor_control->speed_param, PID_POSITION, 500.0f, 0.01f, 0.0f, 0.0f, 0.0f, 10000.0f, 20000.0f, 1.0f, 1.0f, 1.0f);
    PID_Init(&pmotor_control->angle_param, PID_POSITION, 8.35f, 0.0f, 0.11f, 0.0f, 0.0f, 10000.0f, 20000.0f, 1.0f, 1.0f, 1.0f);
    //                                     mode          p     i     d     kf1   kf2   sum_max  output_max d_fil  kf1_fil  kf2_fil
}

/**
 * @brief      Shooter feeder control
 * @param      NULL
 * @retval     NULL
 */
int pid_num = 0;
void MotorTest_Control(Motor_ControlTypeDef *pmotor_control)
{
    switch (pid_num)
    {
    case 1:
        PID_SetRef(&pmotor_control->speed, 10);
        PID_SetFdb(&pmotor_control->speed, pmotor_control->motor->encoder.speed);
        PID_Calc(&pmotor_control->speed, &pmotor_control->speed_param);
        break;
    case 2:
        PID_SetRef(&pmotor_control->angle, 45.0f);
        PID_SetFdb(&pmotor_control->angle, pmotor_control->motor->encoder.consequent_angle);
        PID_Calc(&pmotor_control->angle, &pmotor_control->angle_param);
        PID_SetRef(&pmotor_control->speed, PID_GetOutput(&pmotor_control->angle));
        PID_SetFdb(&pmotor_control->speed, pmotor_control->motor->encoder.speed);
        PID_Calc(&pmotor_control->speed, &pmotor_control->speed_param);
        break;
    default:
        PID_SetRef(&pmotor_control->speed, 0);
        PID_SetFdb(&pmotor_control->speed, pmotor_control->motor->encoder.speed);
        PID_Calc(&pmotor_control->speed, &pmotor_control->speed_param);
        break;
    }
    Motor_SetOutput(pmotor_control->motor, PID_GetOutput(&pmotor_control->speed));
    Motor_CAN_SendGroupOutput(pmotor_control->motor_group);
}
