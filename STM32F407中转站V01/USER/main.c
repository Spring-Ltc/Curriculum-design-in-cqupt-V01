#include "stm32f4xx.h"
//#include "usart.h"
#include "delay.h"
#include "lcd.h"
#include "MyUart.h"
//ALIENTEK ̽����STM32F407������ ʵ��0
//STM32F4����ģ��-�⺯���汾
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK
//����LED

u8 LED_Style=1;

int main(void)
{ 
	u8 key=0;
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);
	//uart_init(115200);
	My_Usart3Init();
	My_Usart1Init();
	IO_Init();
	

  while(1)
	{
		/*
		LED1=!LED1;//break;	//LED1��ת
		delay_ms(500);
		LED0=!LED0;//break;	//LED0��ת
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



