/*
 * @Project: Infantry Code
 *
 * @Author: GDDG08
 * @Date: 2021-12-31 17:37:14
 * @LastEditors: Hatrix 3113624526@qq.com
 * @LastEditTime: 2024-02-12 17:25:57
 */

#include "app_ins.h"

INS_DataTypeDef INS_Data;
// correct according to the installation position
const float correction_mat[9] = {1, 0, 0,
                                 0, 1, 0,
                                 0, 0, 1};

INS_DataTypeDef *INS_GetControlPtr()
{
    return &INS_Data;
}

/**
 * @brief reserved.It is used to correct IMU installation error and scale factor error,
 *        i.e. the installation deviation of gyroscope axis and PTZ axis
 * @param param
 * @param gyro
 * @param accel
 */
static void param_correction(INS_ParamTypeDef *param, float gyro[3], float accel[3])
{
    static float lastYawOffset, lastPitchOffset, lastRollOffset;
    static float c_11, c_12, c_13, c_21, c_22, c_23, c_31, c_32, c_33;
    float cosPitch, cosYaw, cosRoll, sinPitch, sinYaw, sinRoll;

    if (fabsf(param->yaw - lastYawOffset) > 0.001f ||
        fabsf(param->pitch - lastPitchOffset) > 0.001f ||
        fabsf(param->roll - lastRollOffset) > 0.001f || !param->init_flag)
    {
        cosYaw = arm_cos_f32(param->yaw / 57.295779513f);
        cosPitch = arm_cos_f32(param->pitch / 57.295779513f);
        cosRoll = arm_cos_f32(param->roll / 57.295779513f);
        sinYaw = arm_sin_f32(param->yaw / 57.295779513f);
        sinPitch = arm_sin_f32(param->pitch / 57.295779513f);
        sinRoll = arm_sin_f32(param->roll / 57.295779513f);

        // 1.yaw(alpha) 2.pitch(beta) 3.roll(gamma)
        c_11 = cosYaw * cosRoll + sinYaw * sinPitch * sinRoll;
        c_12 = cosPitch * sinYaw;
        c_13 = cosYaw * sinRoll - cosRoll * sinYaw * sinPitch;
        c_21 = cosYaw * sinPitch * sinRoll - cosRoll * sinYaw;
        c_22 = cosYaw * cosPitch;
        c_23 = -sinYaw * sinRoll - cosYaw * cosRoll * sinPitch;
        c_31 = -cosPitch * sinRoll;
        c_32 = sinPitch;
        c_33 = cosPitch * cosRoll;
        param->init_flag = 1;
    }

    float gyro_temp[3];
    for (uint8_t i = 0; i < 3; i++)
    {
        gyro_temp[i] = gyro[i] * param->scale[i];
    }
    gyro[PITCH] = c_11 * gyro_temp[PITCH] + c_12 * gyro_temp[Y_AXIS] + c_13 * gyro_temp[Z_AXIS];
    gyro[ROLL] = c_21 * gyro_temp[PITCH] + c_22 * gyro_temp[Y_AXIS] + c_23 * gyro_temp[Z_AXIS];
    gyro[YAW] = c_31 * gyro_temp[PITCH] + c_32 * gyro_temp[Y_AXIS] + c_33 * gyro_temp[Z_AXIS];

    float accel_temp[3];
    for (uint8_t i = 0; i < 3; i++)
    {
        accel_temp[i] = accel[i];
    }
    accel[X_AXIS] = c_11 * accel_temp[X_AXIS] + c_12 * accel_temp[Y_AXIS] + c_13 * accel_temp[Z_AXIS];
    accel[Y_AXIS] = c_21 * accel_temp[X_AXIS] + c_22 * accel_temp[Y_AXIS] + c_23 * accel_temp[Z_AXIS];
    accel[Z_AXIS] = c_31 * accel_temp[X_AXIS] + c_32 * accel_temp[Y_AXIS] + c_33 * accel_temp[Z_AXIS];

    lastYawOffset = param->yaw;
    lastPitchOffset = param->pitch;
    lastRollOffset = param->roll;
}

void INS_Init()
{
    INS_DataTypeDef *ins = INS_GetControlPtr();
    ins->ins_param.scale[X_AXIS] = 1;
    ins->ins_param.scale[Y_AXIS] = 1;
    ins->ins_param.scale[Z_AXIS] = 1;
    ins->ins_param.yaw = 0;
    ins->ins_param.pitch = 0;
    ins->ins_param.roll = 0;
    ins->ins_param.init_flag = 0;
    QEKF_Init(&ins->q, 10, 0.01f, 10000000, 1, 0.0085f);
}

void INS_Upadte(BMI088_DataTypeDef *bmi088)
{
    INS_DataTypeDef *ins = INS_GetControlPtr();
    while (1)
    {
        static uint32_t count = 0;
        ins->update_dt = DWT_GetDeltaT(&ins->last_update_tick);
        if (((count % 1) == 0))
        {
            BMI088_Decode(bmi088);
            ins->accel[X_AXIS] = bmi088->accel.x;
            ins->accel[Y_AXIS] = bmi088->accel.y;
            ins->accel[Z_AXIS] = bmi088->accel.z;
            ins->gyro[PITCH] = bmi088->gyro.pitch;
            ins->gyro[ROLL] = bmi088->gyro.row;
            ins->gyro[YAW] = bmi088->gyro.yaw;
            param_correction(&ins->ins_param, ins->gyro, ins->accel);
            QEKF_Update(&ins->q, ins->gyro[PITCH], ins->gyro[ROLL], ins->gyro[YAW],
                                 ins->accel[X_AXIS], ins->accel[Y_AXIS], ins->accel[Z_AXIS], ins->update_dt);

            ins->pitch = ins->q.pitch * correction_mat[0] + ins->q.roll * correction_mat[1] + ins->q.yaw * correction_mat[2];
            ins->roll = ins->q.pitch * correction_mat[3] + ins->q.roll * correction_mat[4] + ins->q.yaw * correction_mat[5];
            ins->yaw = ins->q.pitch * correction_mat[6] + ins->q.roll * correction_mat[7] + ins->q.yaw * correction_mat[8];
            ins->yaw_consequent = ins->q.yaw_consequent;
        }
        count++;
        DWT_Delayms(1);
    }
}
