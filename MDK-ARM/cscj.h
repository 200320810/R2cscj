#ifndef CSCJ_H
#define CSCJ_H
#include "tim.h"
void delay_us(int i);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);
#endif
