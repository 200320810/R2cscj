#include "main.h"
#include "gpio.h"
#include "cscj.h"
#include "tim.h"
int high_time_0,IC_flag_0,IC_buf[4];
int high_time_1;
int IC_flag_1;
float cm[2];
int load=0;
int load1=0;

void delay_us(int i)
{
	int j;
	for(j=i;j>0;j--);
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==htim9.Instance)
	{
		load++;
	}
	if(htim->Instance==htim3.Instance)
	{
		load1++;
	}
}
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==htim9.Instance)
	{
		if(IC_flag_0==0)
		{
			IC_buf[0]=HAL_TIM_ReadCapturedValue(&htim9,TIM_CHANNEL_2);
			__HAL_TIM_SET_CAPTUREPOLARITY(&htim9,TIM_CHANNEL_2,TIM_INPUTCHANNELPOLARITY_FALLING);
			IC_flag_0=1;
			load=0;
		}
		else
		{
			IC_buf[1]=HAL_TIM_ReadCapturedValue(&htim9,TIM_CHANNEL_2);
			if(load==0)
			{
				high_time_0=IC_buf[1]-IC_buf[0];
			}
			else
			{
				//high_time=IC_buf[1]-IC_buf[0]+__HAL_TIM_GET_AUTORELOAD(&htim4);
				high_time_0=IC_buf[1]-IC_buf[0]+load*1000;
			}
			IC_flag_0=0;
			__HAL_TIM_SET_CAPTUREPOLARITY(&htim9,TIM_CHANNEL_2,TIM_INPUTCHANNELPOLARITY_RISING);
		}
		cm[0]=high_time_0*0.017;
	}
	if(htim->Instance==htim3.Instance)
	{
		if(IC_flag_1==0)
		{
			IC_buf[2]=HAL_TIM_ReadCapturedValue(&htim3,TIM_CHANNEL_3);
			__HAL_TIM_SET_CAPTUREPOLARITY(&htim3,TIM_CHANNEL_3,TIM_INPUTCHANNELPOLARITY_FALLING);
			IC_flag_1=1;
			load1=0;
		}
		else
		{
			IC_buf[3]=HAL_TIM_ReadCapturedValue(&htim3,TIM_CHANNEL_3);
			if(load1==0)
			{
				high_time_1=IC_buf[3]-IC_buf[2];
			}
			else
			{
				//high_time=IC_buf[1]-IC_buf[0]+__HAL_TIM_GET_AUTORELOAD(&htim4);
				high_time_1=IC_buf[3]-IC_buf[2]+load1*1000;
			}
			IC_flag_1=0;
			__HAL_TIM_SET_CAPTUREPOLARITY(&htim3,TIM_CHANNEL_3,TIM_INPUTCHANNELPOLARITY_RISING);
		}
		cm[1]=high_time_1*0.017;
	}
}
