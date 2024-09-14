/*
 * @Project: Hatrix_Robot
 *
 * @Description: This file contains functions of buzzer
 * @Author: Hatrix
 * @Date: 2023-11-07 14:28:30
 * @LastEditors: Hatrix 3113624526@qq.com
 * @LastEditTime: 2024-02-20 10:38:36
 */

#ifndef PERIPH_BUZZER_H
#define PERIPH_BUZZER_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "util_pwm.h"

    typedef enum
    {
        BUZZER_OFF = 0,
        BUZZER_ON = 1,
        BUZZER_MUSIC = 2,
    } Buzzer_StateEnum;

    typedef struct
    {
        PWM_HandleTypeDef pwm;
        Buzzer_StateEnum state;
    } Buzzer_DataTypeDef;

    void Buzzer_Init(Buzzer_DataTypeDef *buzzer, TIM_HandleTypeDef *htim, uint32_t ch, uint32_t clk);
    void Buzzer_SetState(Buzzer_DataTypeDef *buzzer, Buzzer_StateEnum state);
    Buzzer_StateEnum Buzzer_GetState(Buzzer_DataTypeDef *buzzer);
    void Buzzer_Refresh(Buzzer_DataTypeDef *buzzer);

#ifdef __cplusplus
}
#endif

#endif
