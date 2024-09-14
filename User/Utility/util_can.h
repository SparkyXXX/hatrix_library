/*
 * @Project: Infantry Code
 *
 * @Author: GDDG08
 * @Date: 2021-12-31 17:37:14
 * @LastEditors: Hatrix 3113624526@qq.com
 * @LastEditTime: 2024-02-19 21:46:47
 */

#ifndef UTIL_CAN_H
#define UTIL_CAN_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "can.h"

#define Const_CAN_RX_BUFF_LEN  16

void CAN_InitTxHeader(CAN_TxHeaderTypeDef *pheader, uint32_t stdid);
void CAN_InitFilterAndStart(CAN_HandleTypeDef* phcan);
void CAN_Send(CAN_HandleTypeDef* phcan, CAN_TxHeaderTypeDef* pheader, uint8_t txdata[]);
void CAN_ErrorHandler(uint32_t ret);

#endif

#ifdef __cplusplus
}
#endif
