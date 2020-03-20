
//STM32F103最小系统板
//对  LED  和  蜂鸣器  的控制
//通过蓝牙串口 和STM32F407中转站  交互数据
//蓝牙组网，该组通信波特率位：19200
//需要使用一对蓝牙

#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
//#include "usart.h"
#include "MyUart.h"
#include "BUZZ.h"

//串口中断服务函数，直接使用 库函数的

int main(void)
{	

	delay_init();
	NVIC_Configuration();//中断优先级分组
	MyUart_Init(115200);	//串口初始化
	LED_Init();
	BUZZ_Init();

	
	while(1)
	{
			if(Style_BUZZ==0)
				BUZZ=1;//关闭蜂鸣器
			else if(Style_BUZZ==1)
				BUZZ=0;//蜂鸣器长鸣
			else if(Style_BUZZ==2)
			{
				BUZZ=0,delay_ms(300);
				BUZZ=1,delay_ms(300);
			}
			
			if(Style_LED==2)//保留
				;
			else if(Style_LED==0)	//切换
				LED_RGB=1,delay_ms(30),LED_RGB=0,Style_LED=2;
			else if(Style_LED==1)
				LED_RGB=1,delay_ms(500),LED_RGB=0,delay_ms(500);
			
	}
	
}










