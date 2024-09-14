/*
 * @Project: Hatrix_Robot
 *
 * @Author: Hatrix
 * @Date: 2023-11-07 14:28:30
 * @LastEditors: Hatrix 3113624526@qq.com
 * @LastEditTime: 2024-02-19 22:10:44
 */

#ifndef PROTOCOL_MOTOR_H
#define PROTOCOL_MOTOR_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "task_ctrl.h"
#include "periph_motor_can.h"

    void Motor_CAN_Decode(CAN_HandleTypeDef *phcan, uint32_t stdid, uint8_t rxdata[], uint32_t len);
    void Motor_CAN_SendGroupOutput(Motor_GroupDataTypeDef *pgroup);

#ifdef __cplusplus
}
#endif

#endif