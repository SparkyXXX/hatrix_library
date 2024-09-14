/*
 * @Project: Hatrix_Robot
 *
 * @Description: This file contains functions of buzzer
 * @Author: Hatrix
 * @Date: 2023-11-07 14:28:30
 * @LastEditors: Hatrix 3113624526@qq.com
 * @LastEditTime: 2024-02-20 11:58:36
 */

#include "periph_buzzer.h"

/**
 * @brief         Init buzzer
 * @param         [Buzzer_DataTypeDef*] buzzer
 * @param         [TIM_HandleTypeDef*] htim
 * @param         [uint32_t] ch
 * @return        NULL
 */
void Buzzer_Init(Buzzer_DataTypeDef *buzzer, TIM_HandleTypeDef *htim, uint32_t ch, uint32_t clk)
{
    buzzer->state = BUZZER_OFF;
    PWM_Init(&(buzzer->pwm), htim, ch, clk);
    PWM_SetDuty(&(buzzer->pwm), 0.0f);
    PWM_SetFreq(&(buzzer->pwm), 2000);
    PWM_Start(&(buzzer->pwm));
}

/**
 * @brief         Set buzzer state
 * @param         [Buzzer_DataTypeDef*] buzzer
 * @param         [Buzzer_StateEnum] state
 * @return        NULL
 */
void Buzzer_SetState(Buzzer_DataTypeDef *buzzer, Buzzer_StateEnum state)
{
    buzzer->state = state;
}

/**
 * @brief         Get buzzer state
 * @param         [Buzzer_DataTypeDef*] buzzer
 * @return        [Buzzer_StateEnum]
 */
Buzzer_StateEnum Buzzer_GetState(Buzzer_DataTypeDef *buzzer)
{
    return buzzer->state;
}

/**
 * @brief         Refresh buzzer
 * @param         [Buzzer_DataTypeDef*] buzzer
 * @return        NULL
 */
void Buzzer_Refresh(Buzzer_DataTypeDef *buzzer)
{
    if (buzzer->state == BUZZER_OFF)
        PWM_SetDuty(&(buzzer->pwm), 0.0f);
    if (buzzer->state == BUZZER_ON)
    {
        int delay_cnt = 4000 * 500;
        PWM_SetDuty(&(buzzer->pwm), 0.01f);
        while (delay_cnt--)
        {
            ;
        }
        delay_cnt = 4000 * 500;
        PWM_SetDuty(&(buzzer->pwm), 0.0f);
        while (delay_cnt--)
        {
            ;
        }
        delay_cnt = 4000 * 500;
    }
    // todo: MUSIC
}
