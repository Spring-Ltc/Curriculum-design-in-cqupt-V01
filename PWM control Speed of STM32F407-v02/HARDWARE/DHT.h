
#ifndef __DHT_H__
#define __DHT_H__

#include "sys.h"
#include "delay.h"


//IO方向设置
#define DHT_IO_IN()  {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=0<<9*2;}	//PG9输入模式
#define DHT_IO_OUT() {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=1<<9*2;} 	//PG9输出模式 
////IO操作函数											   
#define	DHT_DQ_OUT PBout(9) //数据端口	PG9 
#define	DHT_DQ_IN  PBin(9)  //数据端口	PG9 

u8 DHT_Init(void);//初始化DHT11
u8 DHT_Read_Data(u8 *temp,u8 *humi);//读取温湿度
u8 DHT_Read_Byte(void);//读出一个字节
u8 DHT_Read_Bit(void);//读出一个位
u8 DHT_Check(void);//检测是否存在DHT11
void DHT_Rst(void);//复位DHT11    
#endif


