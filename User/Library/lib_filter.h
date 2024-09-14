/*
 * @Project: Infantry Code
 *
 * @Author: GDDG08
 * @Date: 2021-12-31 17:37:14
 * @LastEditors: Hatrix
 * @LastEditTime: 2024-01-05 17:46:17
 */

#ifndef ALG_FILTER_H
#define ALG_FILTER_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f4xx_hal.h"
#include "lib_math.h"

#define MAX_LENGTH 30

    typedef struct
    {
        float cut_off_frq;
        float filt_para;
        float last_tick;
        float calc_frq;
    } Filter_LowPassParamTypeDef;

    typedef struct
    {
        float filted_val;
        float filted_last_val;
    } Filter_LowPassTypeDef;

    typedef struct
    {
        uint8_t length;
        float val[MAX_LENGTH];
        float sum;
    } Filter_WindowTypeDef;

    typedef struct
    {
        double ybuf[4];
        double xbuf[4];
        float filted_val;
    } Filter_Bessel_TypeDef;

    void Filter_LowPassInit(float param, Filter_LowPassParamTypeDef *pparam);
    float Filter_LowPass(float val, Filter_LowPassParamTypeDef *fparam, Filter_LowPassTypeDef *filt);
    void Filter_AverInit(Filter_WindowTypeDef *filt, uint8_t length);
    float Filter_Aver(float val, Filter_WindowTypeDef *filt);
    float Filter_Bessel(float val, Filter_Bessel_TypeDef *filt);

#ifdef __cplusplus
}
#endif

#endif
