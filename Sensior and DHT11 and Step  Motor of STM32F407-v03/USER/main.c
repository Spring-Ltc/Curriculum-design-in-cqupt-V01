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

void SolveDate1(char date[],u8 len);



u16 Text=265;
u16 Text_chang=180;
u16 Text_duan=85;
u8 temperature;  	    
u8 humidity; 


	u16 adcx;
	float temp;
	
	
//char add_tem[2]={0};
//char add_hum[2]={0};
char add_MQ[20]={0};	//������Ũ��ֵת��Ϊ�ַ�������ַ�����



//u8 Window_state=0;	//��ǰ������״̬
//0:��ǰΪ�ر�
//1����ǰΪ����
//2����ǰΪ����һ��

int main(void)
{ 
	//u16 adcx;
	//float temp;
	u8 len=0;

	
	
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
		delay_ms(250);
	}	
	
  while(1)
	{
		LED1=!LED1;//break;	//LED1��ת
		delay_ms(500);

		//����1�ɹ����յ�һ������
		if(USART1_RX_STA&0x8000)
		{
			len=USART1_RX_STA&0x3FFF;//�õ����ݳ���
			SolveDate1(USART1_RX_BUF,len);//�Խ��ܵ����ݽ��д���
			USART1_RX_STA=0;//���־λ��׼����һ�ν���
		}
		
		
	}
}

//-----------------------------------------------------------------------------------------------------
//�Խ��յ��Ĵ���1���ݽ��д���
//@��ڲ�����date�洢���ܵ����ݵ���ʼ��ַ��lenΪ���ܵ����ݵĳ���
void SolveDate1(char date[],u8 len)
{
	static u8 Window_state=0;
	
	if(strncmp(date,"A",1)==0)//�ɼ�����
	{
		//memset(USART1_RX_BUF,' ',20);
		//printf(" state:%d\r\n",Window_state);
		DHT_Read_Data(&temperature,&humidity);		//��ȡ��ʪ��ֵ	
		adcx=Get_Adc_Average(ADC_Channel_8,15);		//��ȡ����Ũ��ֵ��ģ���ѹֵ
		
		//printf(" state:%d\r\n",Window_state);
		temp=(float)adcx/4096;
	//	printf(" state:%d\r\n",Window_state);
		temp*=1000;	//ֻȡ�������֣�����10����Ũ�ȹ��ͳ���С����
		//printf(" state:%d\r\n",Window_state);
		sprintf(add_MQ,"%f\t\n",temp);	//��������Ũ�Ȳ�ת��Ϊ�ַ�
	
	//	printf(" state:%d\r\n",Window_state);
		Uart1_SentBit(temperature);
		Uart1_SentBit(humidity);
		Uart1_SentDate(add_MQ,2);		//��������Ũ��
	//printf(" state:%d\r\n",Window_state);
		//���ü�����������־����Ȼ�Է����ղ������ݣ�һ��Ĵ������Ĭ�ϼ��ˣ���������������Һܾ�
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
		USART_SendData(USART1,0x0d);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
		USART_SendData(USART1,0x0a);
		//printf(" state:%d\r\n",Window_state);
	}

	else if(strncmp(date,"o",1)==0)//��
	{
		//Uart1_SentDate(USART1_RX_BUF,10);
		//memset(USART1_RX_BUF,' ',20);
				if(Window_state==0)//ԭ���ǹر�״̬��ת������
					open_Window(Text),Window_state=1;
				else if(Window_state==2)//ԭ���Ǵ���һ���
					open_Window(Text_duan),Window_state=1;
	}
	
	else if(strncmp(date,"c",1)==0)//��
	{
		//Uart1_SentDate(USART1_RX_BUF,10);
		//memset(USART1_RX_BUF,' ',20);
			if(Window_state==1)//ԭ���ǿ���״̬��ת���ش�
			{
				close_Window(Text),Window_state=0;
				//Uart1_SentDate("state=1",7);
			}
			else if(Window_state==2)//ԭ���Ǵ���һ���
			{
				close_Window(Text_chang),Window_state=0;
				//Uart1_SentDate("state=2",7);
			}
			else
			{
				//Uart1_SentDate("state_error",11);
				//printf(" state:%d\r\n",Window_state);
			}
	}
	
	else if(strncmp(date,"h",1)==0)//�뿪
	{
		//Uart1_SentDate(USART1_RX_BUF,10);
		//memset(USART1_RX_BUF,' ',20);
				if(Window_state==0)//ԭ���ǹص�
					open_Window(Text_chang),Window_state=2;
				else if(Window_state==1)//ԭ���ǿ��ŵ�
					close_Window(Text_duan),Window_state=2;
	}
	
}	
	
	
	
	

/*
//����1�жϷ�����
void USART1_IRQHandler(void)
{
	u8 res;
	
	if(USART_GetFlagStatus(USART1,USART_FLAG_ORE)!=RESET)	//���ڽ�������ж�
		USART_ClearFlag(USART1,USART_FLAG_ORE);
	
	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)	//�ж��ǲ��ǽ����ж�
	{
		res=USART_ReceiveData(USART1);	//��ȡ���յ�������
		//LED0=!LED0;
		
		USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);	//��������ʱ���ȹرս����ж�
		switch(res)
		{
			case 'A':
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
			
			
			
			
			case 'o':		//����
			{
				if(Window_state==0)//ԭ���ǹر�״̬��ת������
					open_Window(Text),Window_state=1;
				else if(Window_state==2)//ԭ���Ǵ���һ���
					open_Window(Text_duan),Window_state=1;
				Style_Window=0;
			}
			case 'c':
			{
				if(Window_state==1)//ԭ���ǿ���״̬��ת���ش�
					close_Window(Text),Window_state=0;
				else if(Window_state==2)//ԭ���Ǵ���һ���
					close_Window(Text_chang),Window_state=0;
				Style_Window=0;
			}
			case 'h':
			{
				LED0=!LED0;
				//USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);
				if(Window_state==0)//ԭ���ǹص�
					open_Window(Text_chang),Window_state=2;
				else if(Window_state==1)//ԭ���ǿ��ŵ�
					close_Window(Text_duan),Window_state=2;
				Style_Window=0;
			}
		}
	}	

	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);	//������һ�δν���
}
*/	

/*
		if(Style_Window==1)//����
		{
			if(Window_state==0)//ԭ���ǹر�״̬��ת������
				open_Window(Text),Window_state=1;
			else if(Window_state==2)//ԭ���Ǵ���һ���
				open_Window(Text_duan),Window_state=1;
			Style_Window=0;
		}
		else if(Style_Window==2)//�ش�
		{
			if(Window_state==1)//ԭ���ǿ���״̬��ת���ش�
				close_Window(Text),Window_state=0;
			else if(Window_state==2)//ԭ���Ǵ���һ���
				close_Window(Text_chang),Window_state=0;
			Style_Window=0;
		}
		else if(Style_Window==3)	//ֻ��һ��
		{
			//USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);
			if(Window_state==0)//ԭ���ǹص�
				open_Window(Text_chang),Window_state=2;
			else if(Window_state==1)//ԭ���ǿ��ŵ�
				close_Window(Text_duan),Window_state=2;
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
		*/
