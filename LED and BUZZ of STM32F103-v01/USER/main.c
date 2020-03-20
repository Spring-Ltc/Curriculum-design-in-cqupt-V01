
//STM32F103��Сϵͳ��
//��  LED  ��  ������  �Ŀ���
//ͨ���������� ��STM32F407��תվ  ��������
//��������������ͨ�Ų�����λ��19200
//��Ҫʹ��һ������

#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
//#include "usart.h"
#include "MyUart.h"
#include "BUZZ.h"

//�����жϷ�������ֱ��ʹ�� �⺯����

int main(void)
{	

	delay_init();
	NVIC_Configuration();//�ж����ȼ�����
	MyUart_Init(115200);	//���ڳ�ʼ��
	LED_Init();
	BUZZ_Init();

	
	while(1)
	{
			if(Style_BUZZ==0)
				BUZZ=1;//�رշ�����
			else if(Style_BUZZ==1)
				BUZZ=0;//����������
			else if(Style_BUZZ==2)
			{
				BUZZ=0,delay_ms(300);
				BUZZ=1,delay_ms(300);
			}
			
			if(Style_LED==2)//����
				;
			else if(Style_LED==0)	//�л�
				LED_RGB=1,delay_ms(30),LED_RGB=0,Style_LED=2;
			else if(Style_LED==1)
				LED_RGB=1,delay_ms(500),LED_RGB=0,delay_ms(500);
			
	}
	
}










