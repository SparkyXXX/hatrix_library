/*
 * @Project: Infantry Code
 *
 * @Author: GDDG08
 * @Date: 2021-12-31 17:37:14
 * @LastEditors: Hatrix 3113624526@qq.com
 * @LastEditTime: 2024-02-19 21:58:00
 */

#ifndef PERIPH_MOTOR_CAN_H
#define PERIPH_MOTOR_CAN_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "util_can.h"

#define MOTOR_OFFLINE_TIME 1000

    typedef enum
    {
        MOTOR_CONNECTED = 0,
        MOTOR_LOST = 1
    } Motor_StateEnum;

    typedef struct
    {
        float angle;
        float speed;
        float current;
        int8_t temp;

        int16_t last_angle;
        int32_t round_count;
        float limited_angle;
        float consequent_angle;

        uint32_t last_update_time;
    } Encoder_DataTypeDef;

    typedef struct
    {
        Motor_StateEnum state;
        Encoder_DataTypeDef encoder;
        uint32_t stdid;
        float output;
    } Motor_DataTypeDef;

    typedef struct
    {
        uint8_t motor_num;
        Motor_DataTypeDef *motor_handle[4];
        CAN_HandleTypeDef *can_handle;
        CAN_TxHeaderTypeDef can_header;
    } Motor_GroupDataTypeDef;

    void Motor_Init(Motor_DataTypeDef *pmotor, uint32_t stdid);
    void Motor_InitGroup(Motor_GroupDataTypeDef *pgroup, uint8_t motor_num, CAN_HandleTypeDef *phcan, uint16_t stdid);
    void Motor_SetOutput(Motor_DataTypeDef *pmotor, float output);
    float Motor_GetOutput(Motor_DataTypeDef *pmotor);
    uint8_t Motor_IsLost(Motor_DataTypeDef *pmotor);

#endif

#ifdef __cplusplus
}
#endif
