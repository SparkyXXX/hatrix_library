/*
 * @Project: Infantry Code
 *
 * @Author: GDDG08
 * @Date: 2021-12-31 17:37:14
 * @LastEditors: Hatrix 3113624526@qq.com
 * @LastEditTime: 2024-02-20 08:58:56
 */

#include "util_can.h"

/**
 * @brief        : Initialize can transmitter
 * @param         [CAN_TxHeaderTypeDef] *pheader
 * @param         [uint32_t] stdid
 * @param         [uint32_t] extid
 * @param         [uint32_t] dlc
 * @return        [type]
 */
void CAN_InitTxHeader(CAN_TxHeaderTypeDef *pheader, uint32_t stdid)
{
    pheader->StdId = stdid;
    pheader->RTR = CAN_RTR_DATA;
    pheader->IDE = CAN_ID_STD;
    pheader->DLC = 8;
    pheader->TransmitGlobalTime = DISABLE;
}

/**
 * @brief        : Initialize can filter and enable CAN Bus Transceiver
 * @param         [CAN_HandleTypeDef*] phcan
 * @return        [type]
 */
void CAN_InitFilterAndStart(CAN_HandleTypeDef *phcan)
{
    CAN_FilterTypeDef sFilterConfig;
    sFilterConfig.FilterActivation = ENABLE;
    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
    sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
    sFilterConfig.FilterIdHigh = 0x0000;
    sFilterConfig.FilterIdLow = 0x0000;
    sFilterConfig.FilterMaskIdHigh = 0x0000;
    sFilterConfig.FilterMaskIdLow = 0x0000;
    if (phcan == &hcan1)
    {
        sFilterConfig.FilterBank = 0;
    }
    else
    {
        sFilterConfig.FilterBank = 14;
    }
    if (phcan == &hcan1)
    {
        sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
    }
    else
    {
        sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO1;
    }

    uint32_t ret;
    if (HAL_CAN_ConfigFilter(phcan, &sFilterConfig) != HAL_OK)
    {
        CAN_ErrorHandler(ret);
    }
    if (HAL_CAN_Start(phcan) != HAL_OK)
    {
        CAN_ErrorHandler(ret);
    }

    if (phcan == &hcan1)
    {
        ret = HAL_CAN_ActivateNotification(phcan, CAN_IT_RX_FIFO0_MSG_PENDING);
    }
    else
    {
        ret = HAL_CAN_ActivateNotification(phcan, CAN_IT_RX_FIFO1_MSG_PENDING);
    }
    if (ret != HAL_OK)
    {
        CAN_ErrorHandler(ret);
    }
}

/**
 * @brief        : Sending information to can bus
 * @param         [CAN_HandleTypeDef*] phcan
 * @param         [CAN_TxHeaderTypeDef*] pheader
 * @param         [uint8_t] txdata
 * @return        [type]
 */
void CAN_Send(CAN_HandleTypeDef *phcan, CAN_TxHeaderTypeDef *pheader, uint8_t txdata[])
{
    uint32_t mailbox;
    uint32_t ret;
    pheader->StdId = 0x200;
    pheader->IDE = CAN_ID_STD;
    pheader->RTR = CAN_RTR_DATA;
    pheader->DLC = 0x08;
    if (HAL_CAN_AddTxMessage(phcan, pheader, txdata, &mailbox) != HAL_OK)
    {
        CAN_ErrorHandler(ret);
    }
}

/**
 * @brief        : CAN Error handle handling
 * @param         [uint32_t] ret
 * @return        [type]
 */
void CAN_ErrorHandler(uint32_t ret)
{
    while (1)
    {
        ;
    }
}
