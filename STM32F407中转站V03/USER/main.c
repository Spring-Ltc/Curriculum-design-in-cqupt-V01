#include "stm32f4xx.h"
//#include "usart.h"
#include "delay.h"
#include "lcd.h"
#include "MyUart.h"
#include "LED.h"
#include "string.h"

void SolveDate1(char date[],u8 len);
void SolveDate2(char date[],u8 len);





u8 LED_Style=1;

int main(void)
{ 
	//u8 key=0;
	u8 len=0;//暂存数据长度
	//char str[200];
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);
	//uart_init(115200);
	My_Usart6Init();
	My_Usart3Init();
	My_Usart2Init();
	My_Usart1Init();
	My_Uart5Init();
	
	LED_Init();
	LCD_Init();
	LCD_ShowString(0,0,300,30,24,"ESP8266 Text");

  while(1)
	{
	
		LED1=!LED1;//break;	//LED1翻转
		delay_ms(200);
		
		//串口1成功接收到一次数据
		if(USART1_RX_STA&0x8000)
		{
			len=USART1_RX_STA&0x3FFF;//得到数据长度
			SolveDate1(USART1_RX_BUF,len);//对接受的数据进行处理
			USART1_RX_STA=0;//清标志位，准备下一次接收
		}
		
		//串口2成功接收到一次数据
		if(USART2_RX_STA&0x8000)
		{
			len=USART2_RX_STA&0x3FFF;//得到数据长度
			SolveDate2(USART2_RX_BUF,len);//对接受的数据进行处理
			USART2_RX_STA=0;//清标志位，准备下一次接收
		}
	}
}
//END of main


//对接收到的串口1数据进行处理
//@入口参数：date存储接受到数据的起始地址，len为接受的数据的长度
void SolveDate1(char date[],u8 len)
{

	
	//如果相同，控制LED的指令【LED测试OK】
	if(strncmp(date,"light",5)==0)
	{
		if(date[6]=='s')//切换
		{
			USART_SendData(USART3,'A');
			Uart1_SentDate("switch",6);
		}
		else if(date[6]=='f')//闪烁
		{
			USART_SendData(USART3,'B');
			Uart1_SentDate("flash",5);
		}
	}
	//【LED测试OK】

	//如果相同，控制蜂鸣器的指令【蜂鸣器测试OK】
	else if(strncmp(date,"alarm",5)==0)
	{
		if(date[7]=='n')//长鸣蜂鸣器
			USART_SendData(USART3,'b');
		else if(date[7]=='f')//关闭蜂鸣器
			USART_SendData(USART3,'a');
		else if(date[7]=='u')//周期性鸣叫
			USART_SendData(USART3,'c');
	}
	//【测试OK】
	
	
	
	//如果相同，控制窗帘的指令【窗户测试OK，但未加半开】
	else if(strncmp(date,"current",7)==0)
	{
		//Uart1_SentDate("current",7);
		if(date[8]=='f')//开窗户
		{
			Uart2_SentDate("o",1);
			Uart1_SentDate("o",1);
			//USART_SendData(USART2,'o');
	//USART_SendData(USART2,0x6f);//【发送一个字节】
	//while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);
	//USART_SendData(USART2,0x0d);//【发送一个字节】
	//while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);
	//USART_SendData(USART2,0x0a);//【发送一个字节】
	//while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);
			//Uart1_SentDate("full",4);
		}
		else if(date[8]=='h')	//开一半
		{
			Uart2_SentDate("h",1);
			Uart1_SentDate("h",1);
			//USART_SendData(USART2,'h');
	/*USART_SendData(USART2,0x68);//【发送一个字节】
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);
	USART_SendData(USART2,0x0d);//【发送一个字节】
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);
	USART_SendData(USART2,0x0a);//【发送一个字节】
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);*/
		//	Uart1_SentDate("half",7);
		}
		else if(date[8]=='c')	//关窗户
		{
			Uart2_SentDate("c",1);
			Uart1_SentDate("c",1);
			//USART_SendData(USART2,'c');
	/*USART_SendData(USART2,0x63);//【发送一个字节】
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);
	USART_SendData(USART2,0x0d);//【发送一个字节】
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);
	USART_SendData(USART2,0x0a);//【发送一个字节】
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);*/
			//Uart1_SentDate("close",5);
		}
	}
	//【】
	
	
	//如果相同，读取温湿度的指令
	else if(strncmp(date,"climate",7)==0)
	{
		Uart2_SentDate("A",1);
		Uart1_SentDate("A",1);
		//USART_SendData(USART2,'A');
		
	/*USART_SendData(USART2,0x41);//【发送一个字节】
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);
	USART_SendData(USART2,0x0d);//【发送一个字节】
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);
	USART_SendData(USART2,0x0a);//【发送一个字节】
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);*/
	//	Uart1_SentDate("get the date",12);
	}
	//【】
	
	
	//如果相同，控制电机风扇的指令
	else if(strncmp(date,"fan",3)==0)
	{
		Uart1_SentDate("fan",3);
		if(date[3]=='0')//散热器
		{
			Uart1_SentDate("0",1);
			
			if(date[5]=='o')//关
				Uart6_SentDate("A",1);
			else if(date[5]=='1')//减速
				Uart6_SentDate("B",1);
			else if(date[5]=='2')//减速
				Uart6_SentDate("C",1);
			else if(date[5]=='3')//减速
				Uart6_SentDate("D",1),Uart1_SentDate("D0",2);
		}
		else if(date[3]=='1')	//排风扇
		{
			Uart1_SentDate("1",1);
			if(date[5]=='o')//关
				Uart6_SentDate("a",1);
			else if(date[5]=='1')//减速
				Uart6_SentDate("b",1);
			else if(date[5]=='2')//减速
				Uart6_SentDate("c",1),Uart1_SentDate("c2",2);
			else if(date[5]=='3')//减速
				Uart6_SentDate("d",1);
		}
	}
	//【】
}

//对接收到的串口2数据进行处理
//@入口参数：date存储接受到数据的起始地址，len为接受的数据的长度
//接收到的数据是采集的温湿度的值，接收到后通过UART5发送
void SolveDate2(char date[],u8 len)
{
	u8 i=0;
	USART_ClearFlag(UART5,USART_FLAG_TC); //【清除串口1的发送标志位】
	for(i=0;i<len;i++)
	{
		 USART_SendData(UART5,(u8)date[i]);//【发送一个字节】
		 while(USART_GetFlagStatus(UART5,USART_FLAG_TC)!= SET);//【等待当前字节发送完毕】
	}
	
	USART_SendData(UART5,0x0d);//【发送一个字节】
	while(USART_GetFlagStatus(UART5,USART_FLAG_TC)!= SET);
	USART_SendData(UART5,0x0a);//【发送一个字节】
	while(USART_GetFlagStatus(UART5,USART_FLAG_TC)!= SET);
	
}


