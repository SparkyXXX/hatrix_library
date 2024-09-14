/*
 * @Project: Hatrix_Robot
 *
 * @Author: Hatrix
 * @Date: 2023-11-07 14:28:30
 * @LastEditors: Hatrix 3113624526@qq.com
 * @LastEditTime: 2024-02-09 21:42:43
 */

#include "periph_servo.h"

/**
 * @brief      Initialize the steering gear
 * @param      servo: Pointer to steering gear object
 * @param      htim: Timer handle
 * @param      ch: PWM channel number
 * @retval     NULL
 */
void Servo_Init(Servo_DataTypeDef *servo, TIM_HandleTypeDef *htim, uint32_t ch, uint32_t clk, float angle)
{
    servo->state = SERVO_OFF;
    PWM_Init(&(servo->pwm), htim, ch, clk);
	PWM_SetFreq(&(servo->pwm), 50);
    PWM_Start(&(servo->pwm));
    servo->state = SERVO_ON;
    Servo_SetAngle(servo, angle);
}

/**
 * @brief      Start the steering gear
 * @param      servo: The pointer points to the actuator object
 * @retval     NULL
 */
void Servo_Start(Servo_DataTypeDef *servo)
{
    servo->state = SERVO_ON;
    PWM_Start(&(servo->pwm));
}

/**
 * @brief      Stop the servo
 * @param      servo: The pointer points to the actuator object
 * @retval     NULL
 */
void Servo_Stop(Servo_DataTypeDef *servo)
{
    servo->state = SERVO_OFF;
    PWM_Stop(&(servo->pwm));
}

/**
 * @brief      Set steering angle
 * @param      servo: The pointer points to the actuator object
 * @param      angle: Steering gear angle
 * @retval     NULL
 */
void Servo_SetAngle(Servo_DataTypeDef *servo, float angle)
{
    servo->angle = angle;
    PWM_SetDuty(&(servo->pwm), (angle / 1800 + 0.025f)); 
}

/**
 * @brief      Return to steering angle
 * @param      servo: The pointer points to the actuator object
 * @retval     Steering gear angle
 */
float Servo_GetAngle(Servo_DataTypeDef *servo)
{
    return servo->angle;
}

