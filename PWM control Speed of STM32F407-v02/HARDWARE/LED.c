#include "LED.h"





//������ʼ������
void LED_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStruct;		//����LED��IO�ڵĽṹ�����
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);		//ʹ��ʱ��
	
	
	//F9��F10������LED��IO�ڣ���ʼ������
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_6|GPIO_Pin_7);	//Ĭ������Ϊ�ߵ�ƽ���ر�LED��
}


