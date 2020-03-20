#include "stm32f4xx.h"
//#include "usart.h"
#include "delay.h"
#include "lcd.h"
#include "MyUart.h"
//ALIENTEK 探索者STM32F407开发板 实验0
//STM32F4工程模板-库函数版本
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK
//点亮LED

u8 LED_Style=1;

int main(void)
{ 
	u8 key=0;
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);
	//uart_init(115200);
	My_Usart3Init();
	My_Usart1Init();
	IO_Init();
	

  while(1)
	{
		/*
		LED1=!LED1;//break;	//LED1翻转
		delay_ms(500);
		LED0=!LED0;//break;	//LED0翻转
		delay_ms(500);
		*/
		key=key_scanf();
		if(key!=0)
		{
			switch(key)
			{
				case 1:
				{
					USART_SendData(USART3,'a');
					USART_SendData(USART1,'a');
					break;
				}
				case 2:
				{
					USART_SendData(USART3,'b');
					USART_SendData(USART1,'b');
					break;
				}
				case 3:
				{
					USART_SendData(USART3,'c');
					USART_SendData(USART1,'c');
					break;
				}
				case 4:
				{
					LED_Style++;
					if(LED_Style==3)
						LED_Style=1;
					
					if(LED_Style==1)
						USART_SendData(USART3,'A'),USART_SendData(USART1,'A');
					else
						USART_SendData(USART3,'B'),USART_SendData(USART1,'B');
					break;
				}
 			}
		}	
	}
}



