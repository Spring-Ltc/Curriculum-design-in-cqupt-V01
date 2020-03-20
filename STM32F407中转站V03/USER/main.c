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
	My_Uart5Init();
	
	LED_Init();
	LCD_Init();
	LCD_ShowString(0,0,300,30,24,"ESP8266 Text");

  while(1)
	{
	
		LED1=!LED1;//break;	//LED1��ת
		delay_ms(200);
		
		//����1�ɹ����յ�һ������
		if(USART1_RX_STA&0x8000)
		{
			len=USART1_RX_STA&0x3FFF;//�õ����ݳ���
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
//END of main


//�Խ��յ��Ĵ���1���ݽ��д���
//@��ڲ�����date�洢���ܵ����ݵ���ʼ��ַ��lenΪ���ܵ����ݵĳ���
void SolveDate1(char date[],u8 len)
{

	
	//�����ͬ������LED��ָ�LED����OK��
	if(strncmp(date,"light",5)==0)
	{
		if(date[6]=='s')//�л�
		{
			USART_SendData(USART3,'A');
			Uart1_SentDate("switch",6);
		}
		else if(date[6]=='f')//��˸
		{
			USART_SendData(USART3,'B');
			Uart1_SentDate("flash",5);
		}
	}
	//��LED����OK��

	//�����ͬ�����Ʒ�������ָ�����������OK��
	else if(strncmp(date,"alarm",5)==0)
	{
		if(date[7]=='n')//����������
			USART_SendData(USART3,'b');
		else if(date[7]=='f')//�رշ�����
			USART_SendData(USART3,'a');
		else if(date[7]=='u')//����������
			USART_SendData(USART3,'c');
	}
	//������OK��
	
	
	
	//�����ͬ�����ƴ�����ָ���������OK����δ�Ӱ뿪��
	else if(strncmp(date,"current",7)==0)
	{
		//Uart1_SentDate("current",7);
		if(date[8]=='f')//������
		{
			Uart2_SentDate("o",1);
			Uart1_SentDate("o",1);
			//USART_SendData(USART2,'o');
	//USART_SendData(USART2,0x6f);//������һ���ֽڡ�
	//while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);
	//USART_SendData(USART2,0x0d);//������һ���ֽڡ�
	//while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);
	//USART_SendData(USART2,0x0a);//������һ���ֽڡ�
	//while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);
			//Uart1_SentDate("full",4);
		}
		else if(date[8]=='h')	//��һ��
		{
			Uart2_SentDate("h",1);
			Uart1_SentDate("h",1);
			//USART_SendData(USART2,'h');
	/*USART_SendData(USART2,0x68);//������һ���ֽڡ�
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);
	USART_SendData(USART2,0x0d);//������һ���ֽڡ�
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);
	USART_SendData(USART2,0x0a);//������һ���ֽڡ�
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);*/
		//	Uart1_SentDate("half",7);
		}
		else if(date[8]=='c')	//�ش���
		{
			Uart2_SentDate("c",1);
			Uart1_SentDate("c",1);
			//USART_SendData(USART2,'c');
	/*USART_SendData(USART2,0x63);//������һ���ֽڡ�
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);
	USART_SendData(USART2,0x0d);//������һ���ֽڡ�
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);
	USART_SendData(USART2,0x0a);//������һ���ֽڡ�
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);*/
			//Uart1_SentDate("close",5);
		}
	}
	//����
	
	
	//�����ͬ����ȡ��ʪ�ȵ�ָ��
	else if(strncmp(date,"climate",7)==0)
	{
		Uart2_SentDate("A",1);
		Uart1_SentDate("A",1);
		//USART_SendData(USART2,'A');
		
	/*USART_SendData(USART2,0x41);//������һ���ֽڡ�
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);
	USART_SendData(USART2,0x0d);//������һ���ֽڡ�
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);
	USART_SendData(USART2,0x0a);//������һ���ֽڡ�
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);*/
	//	Uart1_SentDate("get the date",12);
	}
	//����
	
	
	//�����ͬ�����Ƶ�����ȵ�ָ��
	else if(strncmp(date,"fan",3)==0)
	{
		Uart1_SentDate("fan",3);
		if(date[3]=='0')//ɢ����
		{
			Uart1_SentDate("0",1);
			
			if(date[5]=='o')//��
				Uart6_SentDate("A",1);
			else if(date[5]=='1')//����
				Uart6_SentDate("B",1);
			else if(date[5]=='2')//����
				Uart6_SentDate("C",1);
			else if(date[5]=='3')//����
				Uart6_SentDate("D",1),Uart1_SentDate("D0",2);
		}
		else if(date[3]=='1')	//�ŷ���
		{
			Uart1_SentDate("1",1);
			if(date[5]=='o')//��
				Uart6_SentDate("a",1);
			else if(date[5]=='1')//����
				Uart6_SentDate("b",1);
			else if(date[5]=='2')//����
				Uart6_SentDate("c",1),Uart1_SentDate("c2",2);
			else if(date[5]=='3')//����
				Uart6_SentDate("d",1);
		}
	}
	//����
}

//�Խ��յ��Ĵ���2���ݽ��д���
//@��ڲ�����date�洢���ܵ����ݵ���ʼ��ַ��lenΪ���ܵ����ݵĳ���
//���յ��������ǲɼ�����ʪ�ȵ�ֵ�����յ���ͨ��UART5����
void SolveDate2(char date[],u8 len)
{
	u8 i=0;
	USART_ClearFlag(UART5,USART_FLAG_TC); //���������1�ķ��ͱ�־λ��
	for(i=0;i<len;i++)
	{
		 USART_SendData(UART5,(u8)date[i]);//������һ���ֽڡ�
		 while(USART_GetFlagStatus(UART5,USART_FLAG_TC)!= SET);//���ȴ���ǰ�ֽڷ�����ϡ�
	}
	
	USART_SendData(UART5,0x0d);//������һ���ֽڡ�
	while(USART_GetFlagStatus(UART5,USART_FLAG_TC)!= SET);
	USART_SendData(UART5,0x0a);//������һ���ֽڡ�
	while(USART_GetFlagStatus(UART5,USART_FLAG_TC)!= SET);
	
}


