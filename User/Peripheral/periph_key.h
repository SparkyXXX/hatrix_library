/*
 * @Project: Hatrix_Robot
 *
 * @Description: Key trigger function
 * @Author: Hatrix
 * @Date: 2023-11-07 14:28:30
 * @LastEditors: Hatrix 3113624526@qq.com
 * @LastEditTime: 2024-02-20 10:45:14
 */

#ifndef PERIPH_KEY_H
#define PERIPH_KEY_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "util_gpio.h"

    void Key_EventHandler(GPIO_HandleTypeDef *gpio);

#ifdef __cplusplus
}
#endif

#endif