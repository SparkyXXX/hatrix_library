/*
 * @Project: Infantry Code
 *
 * @Author: GDDG08
 * @Date: 2021-12-31 17:37:14
 * @LastEditors: Hatrix 3113624526@qq.com
 * @LastEditTime: 2024-02-20 11:53:09
 */

#include "init_ctrl.h"

LED_DataTypeDef LED_R;
LED_DataTypeDef LED_G;
LED_DataTypeDef LED_B;
GPIO_HandleTypeDef GPIO_LED_B = {GPIO_PIN_RESET, GPIOH, GPIO_PIN_10};
GPIO_HandleTypeDef GPIO_LED_G = {GPIO_PIN_RESET, GPIOH, GPIO_PIN_11};
GPIO_HandleTypeDef GPIO_LED_R = {GPIO_PIN_RESET, GPIOH, GPIO_PIN_12};
GPIO_HandleTypeDef GPIO_KEY = {GPIO_PIN_SET, GPIOA, GPIO_PIN_0};
Buzzer_DataTypeDef Buzzer_Data;
Servo_DataTypeDef Servo_Data;
BMI088_DataTypeDef BMI088_Data;
SPI_HandleTypeDef *BMI088_SPI_HANDLER = &hspi1;
GPIO_HandleTypeDef CS_ACCEL = {GPIO_PIN_RESET, GPIOA, GPIO_PIN_4};
GPIO_HandleTypeDef CS_GYRO = {GPIO_PIN_RESET, GPIOB, GPIO_PIN_0};
Motor_GroupDataTypeDef *Motor_groupHandle[1];
Motor_GroupDataTypeDef Motor_TestMotors;
Motor_DataTypeDef Motor_Test;

// Motor_GroupDataTypeDef *Motor_groupHandle[1];
// Motor_GroupDataTypeDef Motor_ChassisMotors;
// Motor_DataTypeDef Motor_ForwardLeft;
// Motor_DataTypeDef Motor_ForwardRight;
// Motor_DataTypeDef Motor_BackwardRight;
// Motor_DataTypeDef Motor_BackwardLeft;

static void init_all_leds()
{
    LED_Init(&LED_R, &GPIO_LED_R);
    LED_Init(&LED_G, &GPIO_LED_G);
    LED_Init(&LED_B, &GPIO_LED_B);
}

static void init_all_motors()
{
    // Motor_groupHandle[0] = &Motor_ChassisMotors;
    // Motor_InitGroup(&Motor_ChassisMotors, 4, &hcan1, 0x200);
    // Motor_Init(&Motor_ForwardLeft, FORWARD_LEFT_CAN_ID);
    // Motor_Init(&Motor_ForwardRight, FORWARD_RIGHT_CAN_ID);
    // Motor_Init(&Motor_BackwardRight, BACKWARD_RIGHT_CAN_ID);
    // Motor_Init(&Motor_BackwardLeft, BACKWARD_LEFT_CAN_ID);
    // Motor_ChassisMotors.motor_handle[FORWARD_LEFT_CAN_ID - 0x201] = &Motor_ForwardLeft;
    // Motor_ChassisMotors.motor_handle[FORWARD_RIGHT_CAN_ID - 0x201] = &Motor_ForwardRight;
    // Motor_ChassisMotors.motor_handle[BACKWARD_RIGHT_CAN_ID - 0x201] = &Motor_BackwardRight;
    // Motor_ChassisMotors.motor_handle[BACKWARD_LEFT_CAN_ID - 0x201] = &Motor_BackwardLeft;

    Motor_groupHandle[0] = &Motor_TestMotors;
    Motor_InitGroup(&Motor_TestMotors, 1, &hcan1, 0x200);
    Motor_Init(&Motor_Test, FEEDER_CAN_ID);
    Motor_TestMotors.motor_handle[FEEDER_CAN_ID - 0x201] = &Motor_Test;
}

void InitAll(void)
{
    // DWT_Init(CPU_CLK);
    // while (BMI088_Init(&BMI088_Data, BMI088_SPI_HANDLER, &CS_ACCEL, &CS_GYRO)){;}
    // INS_Init();
    init_all_leds();
    Buzzer_Init(&Buzzer_Data, &htim4, TIM_CHANNEL_3, CPU_CLK * 1000000);
    Servo_Init(&Servo_Data, &htim1, TIM_CHANNEL_1, CPU_CLK * 1000000, 0.0f);
    init_all_motors();
    CAN_InitFilterAndStart(&hcan1);
    MotorTest_Init(&Motor_ControlTest, &Motor_TestMotors, &Motor_Test);
}
