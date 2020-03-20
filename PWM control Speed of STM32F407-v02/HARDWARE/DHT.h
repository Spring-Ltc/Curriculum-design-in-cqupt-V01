
#ifndef __DHT_H__
#define __DHT_H__

#include "sys.h"
#include "delay.h"


//IO��������
#define DHT_IO_IN()  {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=0<<9*2;}	//PG9����ģʽ
#define DHT_IO_OUT() {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=1<<9*2;} 	//PG9���ģʽ 
////IO��������											   
#define	DHT_DQ_OUT PBout(9) //���ݶ˿�	PG9 
#define	DHT_DQ_IN  PBin(9)  //���ݶ˿�	PG9 

u8 DHT_Init(void);//��ʼ��DHT11
u8 DHT_Read_Data(u8 *temp,u8 *humi);//��ȡ��ʪ��
u8 DHT_Read_Byte(void);//����һ���ֽ�
u8 DHT_Read_Bit(void);//����һ��λ
u8 DHT_Check(void);//����Ƿ����DHT11
void DHT_Rst(void);//��λDHT11    
#endif


