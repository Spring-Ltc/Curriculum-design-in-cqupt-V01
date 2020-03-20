#ifndef __MQSENSOR_H__
#define __MQSENSOR_H__

#include "sys.h"
#include "delay.h"


void MQ_Init(void);
u16 Get_Adc(u8 Channel); 				//获得某个通道值 
u16 Get_Adc_Average(u8 ch,u8 times);//得到某个通道给定次数采样的平均值 






#endif


