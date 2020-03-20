#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "DHT.h"
#include "Key.h"
#include "LED.h"
#include "MyUart.h"
#include "Motor.h"
#include "MQsensor.h"

#include "string.h"
#include "stdio.h"

u16 Text=265;
u16 Text_chang=180;
u16 Text_duan=85;
u8 temperature;  	    
u8 humidity; 

//char add_tem[2]={0};
//char add_hum[2]={0};
char add_MQ[5]={0};	//把烟雾浓度值转换为字符存入该字符数组

u8 Window_state=0;	//当前窗户的状态
//0:当前为关闭
//1：当前为开启
//2：当前为开启一半

int main(void)
{ 
	u16 adcx;
	float temp;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);
	My_Usart1Init();
	LED_Init();
	Key_Init();
	Motor_Init();
	MQ_Init();
	
 	while(DHT_Init())	//DHT11初始化	
	{
		LED1=!LED1;
		delay_ms(500);
	}	
	
  while(1)
	{
			if(Style_Window==1)//开窗
			{
				
				if(Window_state==0)//原来是关闭状态才转动开窗
					open_Window(Text),Window_state=1,Uart1_SentDate("0",1);
				else if(Window_state==2)//原来是打开了一半的
					open_Window(Text_duan),Window_state=1,Uart1_SentDate("2",1);
				Style_Window=0;
			}
			else if(Style_Window==2)//关窗
			{
				USART_SendData(USART1,Window_state);
				if(Window_state==1)//原来是开启状态才转动关窗
					close_Window(Text),Window_state=0,Uart1_SentDate("1",1);
				else if(Window_state==2)//原来是打开了一半的
					close_Window(Text_chang),Window_state=0,Uart1_SentDate("2",1);
				Style_Window=0;
			}
			else if(Style_Window==3)	//只打开一半
			{
				USART_SendData(USART1,Window_state);
				LED1=!LED1;
				if(Window_state==0)//原来是关的
					open_Window(Text_chang),Window_state=2,Uart1_SentDate("0",1);
				else if(Window_state==1)//原来是开着的
					close_Window(Text_duan),Window_state=2,Uart1_SentDate("1",1);
				Style_Window=0;
			}

			if(Style_DHT==1)//接收到命令时才采集数据并发送
			{
				
					DHT_Read_Data(&temperature,&humidity);		//读取温湿度值	
					adcx=Get_Adc_Average(ADC_Channel_8,15);		//读取烟雾浓度值的模拟电压值
					
					temp=(float)adcx/4096;
					temp*=1000;	//只取整数部分，并乘10避免浓度过低出现小数点
					sprintf(add_MQ,"%f\t\n",temp);	//计算烟雾浓度并转换为字符
				
					Uart1_SentBit(temperature);
					Uart1_SentBit(humidity);
					Uart1_SentDate(add_MQ,2);		//发送烟雾浓度
				
					//还得加两个结束标志，不然对方接收不到数据，一般的串口软件默认加了，这个问题困扰了我很久
					while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
					USART_SendData(USART1,0x0d);
					while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
					USART_SendData(USART1,0x0a);
				
					Style_DHT=0;
			}
			
			
		//	LED1=!LED1;//break;	//LED1翻转
			//delay_ms(200);
	}
}



