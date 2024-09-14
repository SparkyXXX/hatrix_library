/*
 * @Project: Infantry Code
 *
 * @Author: GDDG08
 * @Date: 2021-12-31 17:37:14
 * @LastEditors: Hatrix 3113624526@qq.com
 * @LastEditTime: 2024-02-20 12:00:24
 */

#include "callback_ctrl.h"

/**
 * @brief          Key event handler
 * @param          [GPIO_HandleTypeDef*] gpio
 * @retval         NULL
 */
#define FALSE_TRIGGER_TIME 80
#define LONG_PRESS_TIME 200
uint32_t trigger_time = 0;
void Key_EventHandler(GPIO_HandleTypeDef *gpio)
{
    if (GPIO_ReadPin(gpio) == GPIO_PIN_RESET)
        gpio->last_tick = gpio->tick;
    if (GPIO_ReadPin(gpio) == GPIO_PIN_SET)
        trigger_time = gpio->tick - gpio->last_tick;

    if (trigger_time <= FALSE_TRIGGER_TIME)
        LED_B.state = LED_FLASHING;
    else if ((trigger_time >= FALSE_TRIGGER_TIME) && (trigger_time <= LONG_PRESS_TIME))
        LED_B.state = LED_ON;
    else if (trigger_time >= LONG_PRESS_TIME)
        LED_B.state = LED_OFF;
}

void GPIO_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == KEY_Pin)
    {
        Key_EventHandler(&GPIO_KEY);
    }
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *phcan)
{
    CAN_RxHeaderTypeDef CAN_RxHeader;
    uint8_t CAN_RxData[8];
    uint32_t ret;
    if (HAL_CAN_GetRxMessage(phcan, CAN_RX_FIFO0, &CAN_RxHeader, CAN_RxData) != HAL_OK)
    {
        CAN_ErrorHandler(ret);
    }
    Motor_CAN_Decode(phcan, (&CAN_RxHeader)->StdId, CAN_RxData, (&CAN_RxHeader)->DLC);
}

void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *phcan)
{
    CAN_RxHeaderTypeDef CAN_RxHeader;
    uint8_t CAN_RxData[8];
    uint32_t ret;
    if (HAL_CAN_GetRxMessage(phcan, CAN_RX_FIFO1, &CAN_RxHeader, CAN_RxData) != HAL_OK)
    {
        CAN_ErrorHandler(ret);
    }
    Motor_CAN_Decode(phcan, (&CAN_RxHeader)->StdId, CAN_RxData, (&CAN_RxHeader)->DLC);
}
