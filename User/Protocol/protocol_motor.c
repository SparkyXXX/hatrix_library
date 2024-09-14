/*
 * @Project: Hatrix_Robot
 *
 * @Author: Hatrix
 * @Date: 2023-11-07 14:28:30
 * @LastEditors: Hatrix 3113624526@qq.com
 * @LastEditTime: 2024-02-20 08:34:00
 */

#include "protocol_motor.h"

/**
 * @brief      Feeder motor encoder callback
 * @param      pmotor: Pointer to motor object
 * @retval     NULL
 */
static void m2006_decode(Motor_DataTypeDef *pmotor, uint8_t *rxdata)
{
    pmotor->encoder.last_angle = pmotor->encoder.angle;
    pmotor->encoder.angle = (float)((int16_t)((uint16_t)rxdata[0] << 8 | (uint16_t)rxdata[1]));
    pmotor->encoder.speed = (float)((int16_t)((uint16_t)rxdata[2] << 8 | (uint16_t)rxdata[3]));
    pmotor->encoder.current = (float)((int16_t)((uint16_t)rxdata[4] << 8 | (uint16_t)rxdata[5]));
    pmotor->encoder.temp = rxdata[6];

    pmotor->encoder.speed /= 36.0f;
    // Calculate the angle difference and the number of turns
    int diff = pmotor->encoder.angle - pmotor->encoder.last_angle;
    if (diff < -5500)
    {
        pmotor->encoder.round_count++;
    }
    else if (diff > 5500)
    {
        pmotor->encoder.round_count--;
    }
    // Calculate the shaft angle because the reduction ratio needs to be divided by 36
    pmotor->encoder.consequent_angle = (float)pmotor->encoder.round_count * 10.0f +
                                       (float)pmotor->encoder.angle / 8192.0f * 10.0f;

    pmotor->encoder.last_update_time = HAL_GetTick();
}

/**
 * @brief      Motor encoder decoding callback function
 * @param      canid: CAN Handle number
 * @param      stdid: CAN identifier
 * @param      rxdata: CAN rx data buff
 * @retval     NULL
 */
void Motor_CAN_Decode(CAN_HandleTypeDef *phcan, uint32_t stdid, uint8_t rxdata[], uint32_t len)
{
    if (phcan == &hcan1)
    {
        switch (stdid)
        {
        // case FORWARD_LEFT_CAN_ID:
        //     m2006_decode(&Motor_ForwardLeft, rxdata);
        //     break;
        // case FORWARD_RIGHT_CAN_ID:
        //     m2006_decode(&Motor_ForwardRight, rxdata);
        //     break;
        // case BACKWARD_RIGHT_CAN_ID:
        //     m2006_decode(&Motor_BackwardRight, rxdata);
        //     break;
        // case BACKWARD_LEFT_CAN_ID:
        //     m2006_decode(&Motor_BackwardLeft, rxdata);
        //     break;
        case FEEDER_CAN_ID:
            m2006_decode(&Motor_Test, rxdata);
            break;
        default:
            break;
        }
    }
}

void Motor_CAN_SendGroupOutput(Motor_GroupDataTypeDef *pgroup)
{
    if (pgroup == NULL)
    {
        return;
    }
	uint8_t txdata[8];
    txdata[0] = (uint8_t)((int16_t)Motor_GetOutput(pgroup->motor_handle[0]) >> 8);
    txdata[1] = (uint8_t)Motor_GetOutput(pgroup->motor_handle[0]);
    txdata[2] = (uint8_t)((int16_t)Motor_GetOutput(pgroup->motor_handle[1]) >> 8);
    txdata[3] = (uint8_t)Motor_GetOutput(pgroup->motor_handle[1]);
    txdata[4] = (uint8_t)((int16_t)Motor_GetOutput(pgroup->motor_handle[2]) >> 8);
    txdata[5] = (uint8_t)Motor_GetOutput(pgroup->motor_handle[2]);
    txdata[6] = (uint8_t)((int16_t)Motor_GetOutput(pgroup->motor_handle[3]) >> 8);
    txdata[7] = (uint8_t)Motor_GetOutput(pgroup->motor_handle[3]);
    CAN_Send(pgroup->can_handle, &(pgroup->can_header), txdata);
}
