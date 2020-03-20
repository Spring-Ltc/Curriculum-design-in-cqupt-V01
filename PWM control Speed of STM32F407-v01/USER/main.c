#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "DHT.h"
#include "Key.h"
#include "LED.h"
#include "MyUart.h"
#include "pwm.h"

#include "string.h"
#include "stdio.h"

u16 step=50;	//PWM的步进值
u16 PWM_san=0;
u16 last_san=0;
u16 PWM_pai=0;
u16 last_pai=0;

int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);
	My_Usart1Init();
	LED_Init();
	Key_Init();
	
	Time3PWM_Init();
	/*
 	while(DHT_Init())	//DHT11初始化	
	{
		LED1=!LED1;
		delay_ms(250);
	}	
	*/
  while(1)
	{

		if(Style_pai==1)//排风扇加速
		{
			PWM_pai+=step;
			if(PWM_pai>=1000)
				PWM_pai-=step;
			Style_pai=0;
		}
		else if(Style_pai==2)
		{
			PWM_pai-=step;
			if(PWM_pai<=70)
				PWM_pai+=step;
			Style_pai=0;
		}
		
		
		if(Style_san==1)//散热器加速
		{
			PWM_san+=step;
			if(PWM_san>=1000)
				PWM_san-=step;
			Style_san=0;
		}
		else if(Style_san==2)
		{
			PWM_san-=step;
			if(PWM_san<=70)
				PWM_san+=step;
			Style_san=0;
		}
		
		//改变排风扇的PWM
		if(PWM_pai!=last_pai)
		{
			TIM_SetCompare1(TIM3,PWM_pai);
			last_pai=PWM_pai;
		}
		//改变散热器的PWM
		if(PWM_san!=last_san)
		{
			TIM_SetCompare2(TIM3,PWM_san);
			last_san=PWM_san;
		}
		
		
		LED1=!LED1;//break;	//LED1翻转
		delay_ms(250);
		LED0=!LED0;//break;	//LED0翻转
		delay_ms(250);
	}
}



