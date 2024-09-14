/*
 * @Project: Infantry Code
 *
 * @Author: GDDG08
 * @Date: 2021-12-31 17:37:14
 * @LastEditors: Hatrix 3113624526@qq.com
 * @LastEditTime: 2024-02-20 11:58:57
 */

#ifndef CALLBACK_H
#define CALLBACK_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "protocol_motor.h"
#include "util_gpio.h"

    void GPIO_Callback(uint16_t GPIO_Pin);
    void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *phcan);
    void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *phcan);

#ifdef __cplusplus
}
#endif

#endif
