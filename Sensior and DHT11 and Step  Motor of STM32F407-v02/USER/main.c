#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "DHT.h"
#include "Key.h"
#include "LED.h"
#include "MyUart.h"
#include "Motor.h"
#include "MQsensor.h"

#include "string.h"
#include "stdio.h"

u16 Text=265;
u16 Text_chang=180;
u16 Text_duan=85;
u8 temperature;  	    
u8 humidity; 

//char add_tem[2]={0};
//char add_hum[2]={0};
char add_MQ[5]={0};	//������Ũ��ֵת��Ϊ�ַ�������ַ�����

u8 Window_state=0;	//��ǰ������״̬
//0:��ǰΪ�ر�
//1����ǰΪ����
//2����ǰΪ����һ��

int main(void)
{ 
	u16 adcx;
	float temp;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);
	My_Usart1Init();
	LED_Init();
	Key_Init();
	Motor_Init();
	MQ_Init();
	
 	while(DHT_Init())	//DHT11��ʼ��	
	{
		LED1=!LED1;
		delay_ms(500);
	}	
	
  while(1)
	{
			if(Style_Window==1)//����
			{
				
				if(Window_state==0)//ԭ���ǹر�״̬��ת������
					open_Window(Text),Window_state=1,Uart1_SentDate("0",1);
				else if(Window_state==2)//ԭ���Ǵ���һ���
					open_Window(Text_duan),Window_state=1,Uart1_SentDate("2",1);
				Style_Window=0;
			}
			else if(Style_Window==2)//�ش�
			{
				USART_SendData(USART1,Window_state);
				if(Window_state==1)//ԭ���ǿ���״̬��ת���ش�
					close_Window(Text),Window_state=0,Uart1_SentDate("1",1);
				else if(Window_state==2)//ԭ���Ǵ���һ���
					close_Window(Text_chang),Window_state=0,Uart1_SentDate("2",1);
				Style_Window=0;
			}
			else if(Style_Window==3)	//ֻ��һ��
			{
				USART_SendData(USART1,Window_state);
				LED1=!LED1;
				if(Window_state==0)//ԭ���ǹص�
					open_Window(Text_chang),Window_state=2,Uart1_SentDate("0",1);
				else if(Window_state==1)//ԭ���ǿ��ŵ�
					close_Window(Text_duan),Window_state=2,Uart1_SentDate("1",1);
				Style_Window=0;
			}

			if(Style_DHT==1)//���յ�����ʱ�Ųɼ����ݲ�����
			{
				
					DHT_Read_Data(&temperature,&humidity);		//��ȡ��ʪ��ֵ	
					adcx=Get_Adc_Average(ADC_Channel_8,15);		//��ȡ����Ũ��ֵ��ģ���ѹֵ
					
					temp=(float)adcx/4096;
					temp*=1000;	//ֻȡ�������֣�����10����Ũ�ȹ��ͳ���С����
					sprintf(add_MQ,"%f\t\n",temp);	//��������Ũ�Ȳ�ת��Ϊ�ַ�
				
					Uart1_SentBit(temperature);
					Uart1_SentBit(humidity);
					Uart1_SentDate(add_MQ,2);		//��������Ũ��
				
					//���ü�����������־����Ȼ�Է����ղ������ݣ�һ��Ĵ������Ĭ�ϼ��ˣ���������������Һܾ�
					while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
					USART_SendData(USART1,0x0d);
					while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
					USART_SendData(USART1,0x0a);
				
					Style_DHT=0;
			}
			
			
		//	LED1=!LED1;//break;	//LED1��ת
			//delay_ms(200);
	}
}



