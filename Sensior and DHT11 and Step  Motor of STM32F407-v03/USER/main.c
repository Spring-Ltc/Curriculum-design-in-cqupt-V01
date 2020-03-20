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

void SolveDate1(char date[],u8 len);



u16 Text=265;
u16 Text_chang=180;
u16 Text_duan=85;
u8 temperature;  	    
u8 humidity; 


	u16 adcx;
	float temp;
	
	
//char add_tem[2]={0};
//char add_hum[2]={0};
char add_MQ[20]={0};	//把烟雾浓度值转换为字符存入该字符数组



//u8 Window_state=0;	//当前窗户的状态
//0:当前为关闭
//1：当前为开启
//2：当前为开启一半

int main(void)
{ 
	//u16 adcx;
	//float temp;
	u8 len=0;

	
	
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
		delay_ms(250);
	}	
	
  while(1)
	{
		LED1=!LED1;//break;	//LED1翻转
		delay_ms(500);

		//串口1成功接收到一次数据
		if(USART1_RX_STA&0x8000)
		{
			len=USART1_RX_STA&0x3FFF;//得到数据长度
			SolveDate1(USART1_RX_BUF,len);//对接受的数据进行处理
			USART1_RX_STA=0;//清标志位，准备下一次接收
		}
		
		
	}
}

//-----------------------------------------------------------------------------------------------------
//对接收到的串口1数据进行处理
//@入口参数：date存储接受到数据的起始地址，len为接受的数据的长度
void SolveDate1(char date[],u8 len)
{
	static u8 Window_state=0;
	
	if(strncmp(date,"A",1)==0)//采集数据
	{
		//memset(USART1_RX_BUF,' ',20);
		//printf(" state:%d\r\n",Window_state);
		DHT_Read_Data(&temperature,&humidity);		//读取温湿度值	
		adcx=Get_Adc_Average(ADC_Channel_8,15);		//读取烟雾浓度值的模拟电压值
		
		//printf(" state:%d\r\n",Window_state);
		temp=(float)adcx/4096;
	//	printf(" state:%d\r\n",Window_state);
		temp*=1000;	//只取整数部分，并乘10避免浓度过低出现小数点
		//printf(" state:%d\r\n",Window_state);
		sprintf(add_MQ,"%f\t\n",temp);	//计算烟雾浓度并转换为字符
	
	//	printf(" state:%d\r\n",Window_state);
		Uart1_SentBit(temperature);
		Uart1_SentBit(humidity);
		Uart1_SentDate(add_MQ,2);		//发送烟雾浓度
	//printf(" state:%d\r\n",Window_state);
		//还得加两个结束标志，不然对方接收不到数据，一般的串口软件默认加了，这个问题困扰了我很久
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
		USART_SendData(USART1,0x0d);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
		USART_SendData(USART1,0x0a);
		//printf(" state:%d\r\n",Window_state);
	}

	else if(strncmp(date,"o",1)==0)//开
	{
		//Uart1_SentDate(USART1_RX_BUF,10);
		//memset(USART1_RX_BUF,' ',20);
				if(Window_state==0)//原来是关闭状态才转动开窗
					open_Window(Text),Window_state=1;
				else if(Window_state==2)//原来是打开了一半的
					open_Window(Text_duan),Window_state=1;
	}
	
	else if(strncmp(date,"c",1)==0)//关
	{
		//Uart1_SentDate(USART1_RX_BUF,10);
		//memset(USART1_RX_BUF,' ',20);
			if(Window_state==1)//原来是开启状态才转动关窗
			{
				close_Window(Text),Window_state=0;
				//Uart1_SentDate("state=1",7);
			}
			else if(Window_state==2)//原来是打开了一半的
			{
				close_Window(Text_chang),Window_state=0;
				//Uart1_SentDate("state=2",7);
			}
			else
			{
				//Uart1_SentDate("state_error",11);
				//printf(" state:%d\r\n",Window_state);
			}
	}
	
	else if(strncmp(date,"h",1)==0)//半开
	{
		//Uart1_SentDate(USART1_RX_BUF,10);
		//memset(USART1_RX_BUF,' ',20);
				if(Window_state==0)//原来是关的
					open_Window(Text_chang),Window_state=2;
				else if(Window_state==1)//原来是开着的
					close_Window(Text_duan),Window_state=2;
	}
	
}	
	
	
	
	

/*
//串口1中断服务函数
void USART1_IRQHandler(void)
{
	u8 res;
	
	if(USART_GetFlagStatus(USART1,USART_FLAG_ORE)!=RESET)	//串口接收溢出中断
		USART_ClearFlag(USART1,USART_FLAG_ORE);
	
	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)	//判断是不是接受中断
	{
		res=USART_ReceiveData(USART1);	//读取接收到的数据
		//LED0=!LED0;
		
		USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);	//处理数据时，先关闭接收中断
		switch(res)
		{
			case 'A':
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
			
			
			
			
			case 'o':		//开启
			{
				if(Window_state==0)//原来是关闭状态才转动开窗
					open_Window(Text),Window_state=1;
				else if(Window_state==2)//原来是打开了一半的
					open_Window(Text_duan),Window_state=1;
				Style_Window=0;
			}
			case 'c':
			{
				if(Window_state==1)//原来是开启状态才转动关窗
					close_Window(Text),Window_state=0;
				else if(Window_state==2)//原来是打开了一半的
					close_Window(Text_chang),Window_state=0;
				Style_Window=0;
			}
			case 'h':
			{
				LED0=!LED0;
				//USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);
				if(Window_state==0)//原来是关的
					open_Window(Text_chang),Window_state=2;
				else if(Window_state==1)//原来是开着的
					close_Window(Text_duan),Window_state=2;
				Style_Window=0;
			}
		}
	}	

	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);	//允许下一次次接收
}
*/	

/*
		if(Style_Window==1)//开窗
		{
			if(Window_state==0)//原来是关闭状态才转动开窗
				open_Window(Text),Window_state=1;
			else if(Window_state==2)//原来是打开了一半的
				open_Window(Text_duan),Window_state=1;
			Style_Window=0;
		}
		else if(Style_Window==2)//关窗
		{
			if(Window_state==1)//原来是开启状态才转动关窗
				close_Window(Text),Window_state=0;
			else if(Window_state==2)//原来是打开了一半的
				close_Window(Text_chang),Window_state=0;
			Style_Window=0;
		}
		else if(Style_Window==3)	//只打开一半
		{
			//USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);
			if(Window_state==0)//原来是关的
				open_Window(Text_chang),Window_state=2;
			else if(Window_state==1)//原来是开着的
				close_Window(Text_duan),Window_state=2;
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
		*/
