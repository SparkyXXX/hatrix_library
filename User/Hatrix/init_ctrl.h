/*
 * @Project: Infantry Code
 *
 * @Author: GDDG08
 * @Date: 2021-12-31 17:37:14
 * @LastEditors: Hatrix 3113624526@qq.com
 * @LastEditTime: 2024-02-20 11:52:10
 */

#ifndef INIT_CTRL_H
#define INIT_CTRL_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "app_ins.h"
#include "app_motor_test.h"

#include "periph_led.h"
#include "periph_buzzer.h"
#include "periph_servo.h"
#include "periph_motor_can.h"
#include "periph_bmi088.h"

#define CPU_CLK 168 //(MHz)
#define FEEDER_CAN_ID 0x204
// #define FORWARD_LEFT_CAN_ID 0x201
// #define FORWARD_RIGHT_CAN_ID 0x202
// #define BACKWARD_RIGHT_CAN_ID 0x203
// #define BACKWARD_LEFT_CAN_ID 0x204

    extern LED_DataTypeDef LED_R;
    extern LED_DataTypeDef LED_G;
    extern LED_DataTypeDef LED_B;
    extern GPIO_HandleTypeDef GPIO_KEY;
    extern Buzzer_DataTypeDef Buzzer_Data;
    extern Servo_DataTypeDef Servo_Data;
    extern BMI088_DataTypeDef BMI088_Data;
    extern Motor_GroupDataTypeDef *Motor_groupHandle[1];
    extern Motor_GroupDataTypeDef Motor_TestMotors;
    extern Motor_DataTypeDef Motor_Test;

    // extern Motor_GroupDataTypeDef *Motor_groupHandle[1];
    // extern Motor_GroupDataTypeDef Motor_ChassisMotors;
    // extern Motor_DataTypeDef Motor_ForwardLeft;
    // extern Motor_DataTypeDef Motor_ForwardRight;
    // extern Motor_DataTypeDef Motor_BackwardRight;
    // extern Motor_DataTypeDef Motor_BackwardLeft;


    void InitAll(void);

#ifdef __cplusplus
}
#endif

#endif