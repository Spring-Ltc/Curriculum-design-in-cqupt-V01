#ifndef __MQSENSOR_H__
#define __MQSENSOR_H__

#include "sys.h"
#include "delay.h"


void MQ_Init(void);
u16 Get_Adc(u8 Channel); 				//���ĳ��ͨ��ֵ 
u16 Get_Adc_Average(u8 ch,u8 times);//�õ�ĳ��ͨ����������������ƽ��ֵ 






#endif


