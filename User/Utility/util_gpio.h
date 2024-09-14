/*
 * @Project: Infantry Code
 *
 * @Author: GDDG08
 * @Date: 2021-12-31 17:37:14
 * @LastEditors: Hatrix 3113624526@qq.com
 * @LastEditTime: 2024-02-20 10:51:58
 */

#ifndef UTIL_GPIO_H
#define UTIL_GPIO_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "gpio.h"

    typedef struct
    {
        GPIO_PinState state;
        GPIO_TypeDef *handle;
        uint16_t pin;
        uint32_t tick;
        uint32_t last_tick;
    } GPIO_HandleTypeDef;

    void GPIO_Reset(GPIO_HandleTypeDef *gpio);
    void GPIO_Set(GPIO_HandleTypeDef *gpio);
    GPIO_PinState GPIO_ReadPin(GPIO_HandleTypeDef *gpio);
    uint32_t GPIO_GetTriggerTick(GPIO_HandleTypeDef *gpio);

#ifdef __cplusplus
}
#endif

#endif
