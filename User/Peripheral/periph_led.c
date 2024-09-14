/*
 * @Project: Hatrix_Robot
 *
 * @Description: This file contains functions of LED
 * @Author: Hatrix
 * @Date: 2023-11-07 14:28:30
 * @LastEditors: Hatrix 3113624526@qq.com
 * @LastEditTime: 2024-02-20 11:58:24
 */

#include "periph_led.h"

/**
 * @brief         Init LED
 * @param         [LED_DataTypeDef*] led
 * @param         [GPIO_HandleTypeDef*] gpio
 * @return        NULL
 */
void LED_Init(LED_DataTypeDef *led, GPIO_HandleTypeDef *gpio)
{
    led->gpio = *gpio;
    led->state = LED_OFF;
}

/**
 * @brief         Set LED state
 * @param         [LED_DataTypeDef*] led
 * @param         [LED_StateEnum] state
 * @return        NULL
 */
void LED_SetState(LED_DataTypeDef *led, LED_StateEnum state)
{
    led->state = state;
}

/**
 * @brief         Get LED state
 * @param         [LED_DataTypeDef*] led
 * @return        [LED_StateEnum]
 */
LED_StateEnum LED_GetState(LED_DataTypeDef *led)
{
    return led->state;
}

/**
 * @brief         Refresh LED
 * @param         NULL
 * @return        NULL
 */
void LED_Refresh(LED_DataTypeDef *led)
{
    if (led->state == LED_ON)
        GPIO_Set(&(led->gpio));
    else if (led->state == LED_OFF)
        GPIO_Reset(&(led->gpio));
    else if (led->state == LED_FLASHING)
    {
        led->cnt++;
        if (led->cnt >= 200)
        {
            led->cnt = 0;
            HAL_GPIO_TogglePin(led->gpio.handle, led->gpio.pin);
        }
    }
}
