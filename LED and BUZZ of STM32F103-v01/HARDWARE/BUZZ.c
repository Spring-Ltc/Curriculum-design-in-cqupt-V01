#include "BUZZ.h"


void BUZZ_Init(void)
{
 
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB,PE端口时钟
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;		//13位板载LED		 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOB, &GPIO_InitStructure);					
	 GPIO_SetBits(GPIOB,GPIO_Pin_14);						
	 //GPIO_ResetBits(GPIOB,GPIO_Pin_14);		 //PB14 输出低【关闭】
}
 

