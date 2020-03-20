#include "MyUart.h"
#include "sys.h"
#include "lcd.h"

u16 step=0;

char USART1_RX_BUF[USART1_RX_LEN]={0};		//�������ݻ���
char USART2_RX_BUF[USART2_RX_LEN]={0};
char USART3_RX_BUF[USART3_RX_LEN]={0};



u16 USART1_RX_STA=0;		//����״̬��־λ
u16 USART2_RX_STA=0;
u16 USART3_RX_STA=0;
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ


//-------------���ڳ�ʼ��������ע���жϵ����ȼ��Ͳ�����Ŷ-------------------------------

//USART6����STM32F407VET6ͨ�ţ����Ƶ��
void My_Usart6Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;//GPIO��ʼ���ṹ��
	USART_InitTypeDef USART_InitStruct;//������ر����ṹ��
	//NVIC_InitTypeDef NVIC_InitStruct;//�ж���ر����ṹ��

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE);//����ʱ��ʹ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);//IOʱ��ʹ��

	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_USART6);//�ܽŸ���ӳ��
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_USART6);

	
	//GPIO��ʼ������
	GPIO_InitStruct.GPIO_Mode =GPIO_Mode_AF;//����ģʽ
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStruct);

	//���ڳ�ʼ������
	USART_InitStruct.USART_BaudRate=19200;
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStruct.USART_Parity=USART_Parity_No;
	USART_InitStruct.USART_StopBits=USART_StopBits_1;
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;//�ֳ�
	USART_Init(USART6,&USART_InitStruct);

	USART_Cmd(USART6,ENABLE);//ʹ�ܴ���
	//USART_ITConfig(USART6,USART_IT_RXNE,ENABLE);//�������жϡ�ֻ���˽����жϡ�
/*
	//�ж����ȼ���س�ʼ������
	NVIC_InitStruct.NVIC_IRQChannel=USART6_IRQn;//ͨ��ѡ��
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0x01;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0x01;
	NVIC_Init(&NVIC_InitStruct);
	*/
}
//USART6��ʼ�����



//UART5����ESP8266ͨ�ţ�ֻֻ����
void My_Uart5Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;//GPIO��ʼ���ṹ��
	USART_InitTypeDef USART_InitStruct;//������ر����ṹ��
	//NVIC_InitTypeDef NVIC_InitStruct;//�ж���ر����ṹ��

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);//����ʱ��ʹ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOD,ENABLE);//IOʱ��ʹ��

	GPIO_PinAFConfig(GPIOD,GPIO_PinSource2,GPIO_AF_UART5);//�ܽŸ���ӳ��
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource12,GPIO_AF_UART5);

	
	//GPIO��ʼ������
	GPIO_InitStruct.GPIO_Mode =GPIO_Mode_AF;//����ģʽ
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_12;
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_2;
	GPIO_Init(GPIOD,&GPIO_InitStruct);
	

	//���ڳ�ʼ������
	USART_InitStruct.USART_BaudRate=74880;
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStruct.USART_Parity=USART_Parity_No;
	USART_InitStruct.USART_StopBits=USART_StopBits_1;
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;//�ֳ�
	USART_Init(UART5,&USART_InitStruct);

	USART_Cmd(UART5,ENABLE);//ʹ�ܴ���
	
	
	//USART_ITConfig(USART6,USART_IT_RXNE,ENABLE);//�������жϡ�ֻ���˽����жϡ�
/*
	//�ж����ȼ���س�ʼ������
	NVIC_InitStruct.NVIC_IRQChannel=USART6_IRQn;//ͨ��ѡ��
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0x01;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0x01;
	NVIC_Init(&NVIC_InitStruct);
	*/
}
//USART5��ʼ�����


//USART3����STM32F103C8T6ͨ��
void My_Usart3Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;//GPIO��ʼ���ṹ��
	USART_InitTypeDef USART_InitStruct;//������ر����ṹ��
	//NVIC_InitTypeDef NVIC_InitStruct;//�ж���ر����ṹ��

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//����ʱ��ʹ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);//IOʱ��ʹ��

	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3);//�ܽŸ���ӳ��
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3);

	//GPIO��ʼ������
	GPIO_InitStruct.GPIO_Mode =GPIO_Mode_AF;//����ģʽ
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_11|GPIO_Pin_10;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);

	//���ڳ�ʼ������
	USART_InitStruct.USART_BaudRate=115200;
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStruct.USART_Parity=USART_Parity_No;
	USART_InitStruct.USART_StopBits=USART_StopBits_1;
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;//�ֳ�
	USART_Init(USART3,&USART_InitStruct);

	USART_Cmd(USART3,ENABLE);//ʹ�ܴ���
	//USART_ITConfig(USART3,USART_IT_TXE,ENABLE);//�������жϡ�ֻ���˷����жϡ�
/*
	//�ж����ȼ���س�ʼ������
	NVIC_InitStruct.NVIC_IRQChannel=USART3_IRQn;//ͨ��ѡ��
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0x01;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0x01;
	NVIC_Init(&NVIC_InitStruct);
	*/
}
//USART3��ʼ�����

//USART2����STM32F407VET6ͨ��
void My_Usart2Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;//GPIO��ʼ���ṹ��
	USART_InitTypeDef USART_InitStruct;//������ر����ṹ��
	NVIC_InitTypeDef NVIC_InitStruct;//�ж���ر����ṹ��

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//����ʱ��ʹ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//IOʱ��ʹ��

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2);//�ܽŸ���ӳ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2);

	//GPIO��ʼ������
	GPIO_InitStruct.GPIO_Mode =GPIO_Mode_AF;//����ģʽ
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);

	//���ڳ�ʼ������
	USART_InitStruct.USART_BaudRate=9600;
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStruct.USART_Parity=USART_Parity_No;
	USART_InitStruct.USART_StopBits=USART_StopBits_1;
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;//�ֳ�
	USART_Init(USART2,&USART_InitStruct);

	USART_Cmd(USART2,ENABLE);//ʹ�ܴ���
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);//�������жϡ�ֻ���˷����жϡ�

	//�ж����ȼ���س�ʼ������
	NVIC_InitStruct.NVIC_IRQChannel=USART2_IRQn;//ͨ��ѡ��
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0x01;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0x01;
	NVIC_Init(&NVIC_InitStruct);
}
//USART2��ʼ�����

//USART1����ESP8266������ͨ��
void My_Usart1Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;//GPIO��ʼ���ṹ��
	USART_InitTypeDef USART_InitStruct;//������ر����ṹ��
	NVIC_InitTypeDef NVIC_InitStruct;//�ж���ر����ṹ��

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//����ʱ��ʹ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//IOʱ��ʹ��

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);//�ܽŸ���ӳ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);

	//GPIO��ʼ������
	GPIO_InitStruct.GPIO_Mode =GPIO_Mode_AF;//����ģʽ
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_10;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_25MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);

	//���ڳ�ʼ������
	USART_InitStruct.USART_BaudRate=74880;
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStruct.USART_Parity=USART_Parity_No;
	USART_InitStruct.USART_StopBits=USART_StopBits_1;
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;//�ֳ�
	USART_Init(USART1,&USART_InitStruct);

	USART_Cmd(USART1,ENABLE);//ʹ�ܴ���
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//�������жϡ�ֻ���˷����жϡ�

	//�ж����ȼ���س�ʼ������
	NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQn;//ͨ��ѡ��
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0x02;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0x02;
	NVIC_Init(&NVIC_InitStruct);
}
//USART1��ʼ�����

//--------------------------���Դ��ڳ�ʼ�����---------------------------------


//---------------------------�����жϷ�����-----------------------------------
//����1�жϷ�����
//����ESP8266ָ����Ͳɼ�����
void USART1_IRQHandler(void)
{
	u8 res;
	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)	//�ж��ǲ��ǽ����ж�
	{
		res=USART_ReceiveData(USART1);	//��ȡ���յ�������
		if((USART1_RX_STA&0x8000)==0)//�ж��Ƿ������ϡ����λ��1����ʾ������ϡ�,û�н�����ϲ�ִ��
		{
			if(USART1_RX_STA&0x4000)//�ж���һ���Ƿ���յ��˱�־����0x0d
			{
				if(res==0x0a)
					USART1_RX_STA|=0x8000;//��������һ���������
				else
					USART1_RX_STA=0;//�����쳣���������
			}
			else
			{
				if(res==0x0d)
					USART1_RX_STA|=0x4000;
				else
				{
					USART1_RX_BUF[USART1_RX_STA&0x3fff]=(char)res;
					USART1_RX_STA++;
					if(USART1_RX_STA>=USART1_RX_LEN)
						USART1_RX_STA=0;//���ݳ��ȳ�������
				}
			}
		}			
	}						
}

/*
//����2�жϷ�����
//����STM32F407�ɼ������ݲ����Ͳ����������ָ��
void USART2_IRQHandler(void)
{
	u8 res;
	if(USART_GetITStatus(USART2,USART_IT_RXNE)==SET)	//�ж��ǲ��ǽ����ж�
	{
		res=USART_ReceiveData(USART2);	//��ȡ���յ�������
		if((USART2_RX_STA&0x8000)==0)//�ж��Ƿ������ϡ����λ��1����ʾ������ϡ�,û�н�����ϲ�ִ��
		{
			if(USART2_RX_STA&0x4000)//�ж���һ���Ƿ���յ��˱�־����0x0d
			{
				if(res==0x0a)
					USART2_RX_STA|=0x8000;//��������һ���������
				else
					USART2_RX_STA=0;//�����쳣���������
			}
			else
			{
				if(res==0x0d)
					USART2_RX_STA|=0x4000;
				else
				{
					USART2_RX_BUF[USART2_RX_STA&0x3fff]=res;
					USART2_RX_STA++;
					if(USART2_RX_STA>=USART2_RX_LEN)
						USART2_RX_STA=0;//���ݳ��ȳ�������
				}
			}
		}			
	}						
}
*/

//����2�жϷ�����
//��ʱ����Ҫ��������
void USART2_IRQHandler(void)
{
	u8 res;
	if(USART_GetITStatus(USART2,USART_IT_RXNE)==SET)	//�ж��ǲ��ǽ����ж�
	{
		res=USART_ReceiveData(USART2);	//��ȡ���յ�������
		if((USART2_RX_STA&0x8000)==0)//�ж��Ƿ������ϡ����λ��1����ʾ������ϡ�,û�н�����ϲ�ִ��
		{
			if(USART2_RX_STA&0x4000)//�ж���һ���Ƿ���յ��˱�־����0x0d
			{
				if(res==0x0a)
					USART2_RX_STA|=0x8000;//��������һ���������
				else
					USART2_RX_STA=0;//�����쳣���������
			}
			else
			{
				if(res==0x0d)
					USART2_RX_STA|=0x4000;
				else
				{
					USART2_RX_BUF[USART2_RX_STA&0x3fff]=res;
					USART2_RX_STA++;
					if(USART2_RX_STA>=USART2_RX_LEN)
						USART2_RX_STA=0;//���ݳ��ȳ�������
				}
			}
		}			
	}						
}

//---------------------------�����жϷ��������-----------------------------------




//----------------------------�������ݷ��ͺ���---------------------------------------


void Uart1_SentDate(char date[],u8 len)
{
	u8 i=0;
	for(i=0;i<len;i++)
	{
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);//�ȴ����ͻ��������
		USART_SendData(USART1,(u8)date[i]);
	}
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);
	USART_SendData(USART1,0x0d);//������һ���ֽڡ�
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);
	USART_SendData(USART1,0x0a);//������һ���ֽڡ�
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);
	
}



void Uart2_SentDate(char date[],u8 len)
{
	u8 i=0;
	for(i=0;i<len;i++)
	{
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//�ȴ����ͻ��������
		USART_SendData(USART2,(u8)date[i]);
	}
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);
	USART_SendData(USART2,0x0d);//������һ���ֽڡ�
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);
	USART_SendData(USART2,0x0a);//������һ���ֽڡ�
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);
}


void Uart5_SentDate(char date[],u8 len)
{
	u8 i=0;
	for(i=0;i<len;i++)
	{
		while(USART_GetFlagStatus(UART5,USART_FLAG_TC)==RESET);//�ȴ����ͻ��������
		USART_SendData(UART5,(u8)date[i]);
	}
}



void Uart6_SentDate(char date[],u8 len)
{
	u8 i=0;
	for(i=0;i<len;i++)
	{
		while(USART_GetFlagStatus(USART6,USART_FLAG_TC)==RESET);//�ȴ����ͻ��������
		USART_SendData(USART6,(u8)date[i]);
	}
	while(USART_GetFlagStatus(USART6,USART_FLAG_TC)!= SET);
	USART_SendData(USART6,0x0d);//������һ���ֽڡ�
	while(USART_GetFlagStatus(USART6,USART_FLAG_TC)!= SET);
	USART_SendData(USART6,0x0a);//������һ���ֽڡ�
	while(USART_GetFlagStatus(USART6,USART_FLAG_TC)!= SET);
}

//-------------------------------------�ָ���-------------------------------------------------------




