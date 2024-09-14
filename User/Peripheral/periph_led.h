/*
 * @Project: Hatrix_Robot
 *
 * @Description: This file contains functions of LED
 * @Author: Hatrix
 * @Date: 2023-11-07 14:28:30
 * @LastEditors: Hatrix 3113624526@qq.com
 * @LastEditTime: 2024-02-20 10:45:51
 */

#ifndef PERIPH_LED_H
#define PERIPH_LED_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "util_gpio.h"

    typedef enum
    {
        LED_OFF      = 0,
        LED_ON       = 1,
        LED_FLASHING = 2,
    } LED_StateEnum;

    typedef struct
    {
        GPIO_HandleTypeDef gpio;
        LED_StateEnum state;
        uint8_t cnt;
    } LED_DataTypeDef;

    void LED_Init(LED_DataTypeDef *led, GPIO_HandleTypeDef *gpio);
    void LED_SetState(LED_DataTypeDef *led, LED_StateEnum state);
    LED_StateEnum LED_GetState(LED_DataTypeDef *led);
    void LED_Refresh(LED_DataTypeDef *led);

#ifdef __cplusplus
}
#endif

#endif