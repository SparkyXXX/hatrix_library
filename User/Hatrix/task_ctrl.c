/*
 * @Project: Infantry Code
 *
 * @Author: GDDG08
 * @Date: 2021-12-31 17:37:14
 * @LastEditors: Hatrix
 * @LastEditTime: 2024-02-20 11:50:59
 */

#include "task_ctrl.h"

float servo_angle = 0.0f;
void RunAll(void)
{
    LED_Refresh(&LED_B);
    Buzzer_Refresh(&Buzzer_Data);
    // Servo_SetAngle(&Servo_Data, servo_angle);
    // MotorTest_Control(&Motor_ControlTest);
    // INS_Upadte(&BMI088_Data);
    HAL_Delay(1);
}
