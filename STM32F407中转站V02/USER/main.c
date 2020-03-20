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
	LED_Init();
	LCD_Init();
	LCD_ShowString(0,0,300,30,24,"ESP8266 Text");

  while(1)
	{
		
		LED1=!LED1;//break;	//LED1翻转
		delay_ms(500);
		
		//串口1成功接收到一次数据
		if(USART1_RX_STA&0x8000)
		{
			len=USART1_RX_STA&0x3FFF;//得到数据长度
			//sprintf(str,USART1_RX_BUF);
			//USART1_RX_BUF=(char)USART1_RX_BUF;
			
			LCD_ShowString(0,50,300,30,24,"OK");	//【成功收到，未判断】
			
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

//对接收到的串口1数据进行处理
//@入口参数：date存储接受到数据的起始地址，len为接受的数据的长度
void SolveDate1(char date[],u8 len)
{
	//如果相同，控制LED的指令【LED测试OK】
	if(strncmp(date,"light",5)==0)
	{
		//LCD_ShowString(0,80,300,30,24,"LED");	//【成功收到，判断LED】
		//Uart1_SentDate("LED",3);
		if(date[6]=='s')//切换
		{
			//LCD_ShowString(0,110,300,30,24,"SEND");	//【成功收到，判断LED，并发送指令】
			USART_SendData(USART3,'A');
			//Uart1_SentDate("switch",6);
		}
		else if(date[6]=='f')//闪烁
			USART_SendData(USART3,'B'),Uart1_SentDate("Flashing",8);
	}
	
	//如果相同，控制蜂鸣器的指令【蜂鸣器测试OK】
	else if(strncmp(date,"buzz",4)==0)
	{
		//Uart1_SentDate("BUZZ",3);
		if(date[6]=='n')//长鸣蜂鸣器
			USART_SendData(USART3,'b'),Uart1_SentDate("on",4);
		else if(date[6]=='f')//关闭蜂鸣器
			USART_SendData(USART3,'a'),Uart1_SentDate("off",4);
		else if(date[6]=='u')//周期性鸣叫
			USART_SendData(USART3,'c'),Uart1_SentDate("turn",4);
	}
	//如果相同，控制窗帘的指令【窗户测试OK，但未加半开】
	else if(strncmp(date,"Window",6)==0)
	{
		Uart1_SentDate("Window",6);
		if(date[7]=='o')//开窗户
			USART_SendData(USART2,'o'),Uart1_SentDate("open",4);
		else if(date[7]=='h')	//开一半
			USART_SendData(USART2,'h'),Uart1_SentDate("half",4);
		else if(date[7]=='c')	//关窗户
			USART_SendData(USART2,'c'),Uart1_SentDate("close",5);
	}
	//如果相同，读取温湿度的指令
	else if(strncmp(date,"Get",3)==0)
	{
		USART_SendData(USART2,'A');
		//Uart1_SentDate("get the date",12);
	}
	//如果相同，控制电机风扇的指令
	else if(strncmp(date,"Speed",5)==0)
	{
		if(date[6]=='s')//散热器
		{
			if(date[10]=='U')//加速
				USART_SendData(USART6,'B'),Uart1_SentDate("san_up",6);
			else if(date[10]=='D')//减速
				USART_SendData(USART6,'b'),Uart1_SentDate("san_down",8);
		}
		else if(date[6]=='p')	//排风扇
		{
			if(date[10]=='U')//加速
				USART_SendData(USART6,'A'),Uart1_SentDate("pai_up",6);
			else if(date[10]=='D')//减速
				USART_SendData(USART6,'a'),Uart1_SentDate("pai_down",8);
		}
	}
}

//对接收到的串口2数据进行处理
//@入口参数：date存储接受到数据的起始地址，len为接受的数据的长度
//接收到的数据是采集的温湿度的值，接收到后通过USART1发送
void SolveDate2(char date[],u8 len)
{
	u8 i=0;
	USART_ClearFlag(USART1,USART_FLAG_TC); //【清除串口1的发送标志位】
	for(i=0;i<len;i++)
	{
		 USART_SendData(USART1,(u8)date[i]);//【发送一个字节】
		 while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);//【等待当前字节发送完毕】
	}
	
	USART_SendData(USART1,0x0d);//【发送一个字节】
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);
	USART_SendData(USART1,0x0a);//【发送一个字节】
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);
	
}


