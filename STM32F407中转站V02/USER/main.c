#include "stm32f4xx.h"
//#include "usart.h"
#include "delay.h"
#include "lcd.h"
#include "MyUart.h"
#include "LED.h"
#include "string.h"

void SolveDate1(char date[],u8 len);
void SolveDate2(char date[],u8 len);





u8 LED_Style=1;

int main(void)
{ 
	//u8 key=0;
	u8 len=0;//�ݴ����ݳ���
	//char str[200];
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);
	//uart_init(115200);
	My_Usart6Init();
	My_Usart3Init();
	My_Usart2Init();
	My_Usart1Init();
	LED_Init();
	LCD_Init();
	LCD_ShowString(0,0,300,30,24,"ESP8266 Text");

  while(1)
	{
		
		LED1=!LED1;//break;	//LED1��ת
		delay_ms(500);
		
		//����1�ɹ����յ�һ������
		if(USART1_RX_STA&0x8000)
		{
			len=USART1_RX_STA&0x3FFF;//�õ����ݳ���
			//sprintf(str,USART1_RX_BUF);
			//USART1_RX_BUF=(char)USART1_RX_BUF;
			
			LCD_ShowString(0,50,300,30,24,"OK");	//���ɹ��յ���δ�жϡ�
			
			SolveDate1(USART1_RX_BUF,len);//�Խ��ܵ����ݽ��д���
			USART1_RX_STA=0;//���־λ��׼����һ�ν���
		}
		
		//����2�ɹ����յ�һ������
		if(USART2_RX_STA&0x8000)
		{
			len=USART2_RX_STA&0x3FFF;//�õ����ݳ���
			
			SolveDate2(USART2_RX_BUF,len);//�Խ��ܵ����ݽ��д���
			USART2_RX_STA=0;//���־λ��׼����һ�ν���
		}
		
	
	}
}

//�Խ��յ��Ĵ���1���ݽ��д���
//@��ڲ�����date�洢���ܵ����ݵ���ʼ��ַ��lenΪ���ܵ����ݵĳ���
void SolveDate1(char date[],u8 len)
{
	//�����ͬ������LED��ָ�LED����OK��
	if(strncmp(date,"light",5)==0)
	{
		//LCD_ShowString(0,80,300,30,24,"LED");	//���ɹ��յ����ж�LED��
		//Uart1_SentDate("LED",3);
		if(date[6]=='s')//�л�
		{
			//LCD_ShowString(0,110,300,30,24,"SEND");	//���ɹ��յ����ж�LED��������ָ�
			USART_SendData(USART3,'A');
			//Uart1_SentDate("switch",6);
		}
		else if(date[6]=='f')//��˸
			USART_SendData(USART3,'B'),Uart1_SentDate("Flashing",8);
	}
	
	//�����ͬ�����Ʒ�������ָ�����������OK��
	else if(strncmp(date,"buzz",4)==0)
	{
		//Uart1_SentDate("BUZZ",3);
		if(date[6]=='n')//����������
			USART_SendData(USART3,'b'),Uart1_SentDate("on",4);
		else if(date[6]=='f')//�رշ�����
			USART_SendData(USART3,'a'),Uart1_SentDate("off",4);
		else if(date[6]=='u')//����������
			USART_SendData(USART3,'c'),Uart1_SentDate("turn",4);
	}
	//�����ͬ�����ƴ�����ָ���������OK����δ�Ӱ뿪��
	else if(strncmp(date,"Window",6)==0)
	{
		Uart1_SentDate("Window",6);
		if(date[7]=='o')//������
			USART_SendData(USART2,'o'),Uart1_SentDate("open",4);
		else if(date[7]=='h')	//��һ��
			USART_SendData(USART2,'h'),Uart1_SentDate("half",4);
		else if(date[7]=='c')	//�ش���
			USART_SendData(USART2,'c'),Uart1_SentDate("close",5);
	}
	//�����ͬ����ȡ��ʪ�ȵ�ָ��
	else if(strncmp(date,"Get",3)==0)
	{
		USART_SendData(USART2,'A');
		//Uart1_SentDate("get the date",12);
	}
	//�����ͬ�����Ƶ�����ȵ�ָ��
	else if(strncmp(date,"Speed",5)==0)
	{
		if(date[6]=='s')//ɢ����
		{
			if(date[10]=='U')//����
				USART_SendData(USART6,'B'),Uart1_SentDate("san_up",6);
			else if(date[10]=='D')//����
				USART_SendData(USART6,'b'),Uart1_SentDate("san_down",8);
		}
		else if(date[6]=='p')	//�ŷ���
		{
			if(date[10]=='U')//����
				USART_SendData(USART6,'A'),Uart1_SentDate("pai_up",6);
			else if(date[10]=='D')//����
				USART_SendData(USART6,'a'),Uart1_SentDate("pai_down",8);
		}
	}
}

//�Խ��յ��Ĵ���2���ݽ��д���
//@��ڲ�����date�洢���ܵ����ݵ���ʼ��ַ��lenΪ���ܵ����ݵĳ���
//���յ��������ǲɼ�����ʪ�ȵ�ֵ�����յ���ͨ��USART1����
void SolveDate2(char date[],u8 len)
{
	u8 i=0;
	USART_ClearFlag(USART1,USART_FLAG_TC); //���������1�ķ��ͱ�־λ��
	for(i=0;i<len;i++)
	{
		 USART_SendData(USART1,(u8)date[i]);//������һ���ֽڡ�
		 while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);//���ȴ���ǰ�ֽڷ�����ϡ�
	}
	
	USART_SendData(USART1,0x0d);//������һ���ֽڡ�
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);
	USART_SendData(USART1,0x0a);//������һ���ֽڡ�
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);
	
}


