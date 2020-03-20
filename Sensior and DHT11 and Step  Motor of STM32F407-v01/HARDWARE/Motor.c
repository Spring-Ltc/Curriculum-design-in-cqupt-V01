#include "Motor.h"
#include "delay.h"
#include "LED.h"

#define STEP 2100

//步进电机初始化
void Motor_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStruct;		//定义LED的IO口的结构体变量
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);		//使能时钟

	//F9和F10（两个LED的IO口）初始化设置
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_DOWN;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_ResetBits(GPIOA,GPIO_Pin_6|GPIO_Pin_7);	//默认设置为高电平，关闭LED亮
}


//开窗户
void open_Window(u16 time)
{
	u16 i=0;
		for(i=0;i<time*10;i++)
		{
			OUT1=1,OUT2=0,OUT3=0,OUT4=0;
			LED0=!LED0,delay_us(STEP);
			OUT1=0,OUT2=1,OUT3=0,OUT4=0;
			LED0=!LED0,delay_us(STEP);
			OUT1=0,OUT2=0,OUT3=1,OUT4=0;
			LED0=!LED0,delay_us(STEP);
			OUT1=0,OUT2=0,OUT3=0,OUT4=1;
			LED0=!LED0,delay_us(STEP);
		}
}
//关窗户
void close_Window(u16 time)
{
	u16 i=0;
		for(i=0;i<time*10;i++)
		{
			OUT1=0,OUT2=0,OUT3=0,OUT4=1;
			LED0=!LED0,delay_us(STEP);

			OUT1=0,OUT2=0,OUT3=1,OUT4=0;
			LED0=!LED0,delay_us(STEP);
			
			OUT1=0,OUT2=1,OUT3=0,OUT4=0;
			LED0=!LED0,delay_us(STEP);
			
			OUT1=1,OUT2=0,OUT3=0,OUT4=0;
			LED0=!LED0,delay_us(STEP);
		}
}
