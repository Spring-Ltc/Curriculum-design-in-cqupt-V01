#include "LED.h"





//按键初始化函数
void LED_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStruct;		//定义LED的IO口的结构体变量
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);		//使能时钟
	
	
	//F9和F10（两个LED的IO口）初始化设置
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_6|GPIO_Pin_7);	//默认设置为高电平，关闭LED亮
}


