

/*------------------------------���˵��--------------------------------------------------

���ڷ�������ʱ��ֻ�ܰ�����ת��Ϊ�ַ����ٷ��ͣ���
���ڷ��Ͳ���Ҫ�ж�



*///--------------------------------------------------------------------------------


#include "MyUart.h"
#include "LED.h"


char USART1_RX_BUF[USART1_RX_LEN]={0};		//�������ݻ���
u16 USART1_RX_STA=0;		//����״̬��־λ


u8 Style_Window=0;
u8 Style_DHT=0;
u8 Style_MQ=0;




/*//����3��ʼ��
void My_Usart3Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;//GPIO��ʼ���ṹ��
	USART_InitTypeDef USART_InitStruct;//������ر����ṹ��
	NVIC_InitTypeDef NVIC_InitStruct;//�ж���ر����ṹ��

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//����ʱ��ʹ��
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);//IOʱ��ʹ��

		GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3);//�ܽŸ���ӳ��
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3);

	//GPIO��ʼ������
	GPIO_InitStruct.GPIO_Mode =GPIO_Mode_AF;//����ģʽ
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_11|GPIO_Pin_10;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_25MHz;
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

	//�ж����ȼ���س�ʼ������
	NVIC_InitStruct.NVIC_IRQChannel=USART3_IRQn;//ͨ��ѡ��
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0x01;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0x01;
	NVIC_Init(&NVIC_InitStruct);

}

void Uart3_SentBit(u8 date)
{
	while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET);//�ȴ����ͻ��������
	
	USART_SendData(USART3,date);
}
*/
// END of Flag


//��Ҫ���Ͳɼ�����ʪ�ȵ�ֵ
//��Ҫ���նԲ�������Ŀ�������
//����1��ʼ��
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
	USART_InitStruct.USART_BaudRate=9600;
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;		//�����պͷ��Ͷ�ҡ������
	USART_InitStruct.USART_Parity=USART_Parity_No;
	USART_InitStruct.USART_StopBits=USART_StopBits_1;
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;//�ֳ�
	USART_Init(USART1,&USART_InitStruct);

	USART_Cmd(USART1,ENABLE);//ʹ�ܴ���
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//�����ڽ����жϣ��������������ģ�����Ҫ�����жϡ�
	
	//�ж����ȼ���س�ʼ������
	NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQn;//ͨ��ѡ��
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0x02;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0x02;
	NVIC_Init(&NVIC_InitStruct);
}
//END of Flag




//----------------------------------------------�ָ���---------------------------------------------------

//������OK��
//���ڷ��ͺ���
//��ת��Ϊ�ַ����ٷ��͡�����ȡģ�������㡿
void Uart1_SentBit(u8 date)
{
	u8 send[2];
	send[0]=date/10;
	send[1]=date%10;
	
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);//�ȴ����ͻ��������
	USART_SendData(USART1,'0'+send[0]);
	
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);//�ȴ����ͻ��������
	USART_SendData(USART1,'0'+send[1]);
}


//�����ַ�������
void Uart1_SentDate(char date[],u8 len)
{
	u8 i=0;
	for(i=0;i<len;i++)
	{
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);//�ȴ����ͻ��������
		USART_SendData(USART1,(u8)date[i]);
	}
}





//------------------------------------------------------�ָ���--------------------------------------------------------


//---------------------------�����жϷ�����-----------------------------------
//����1�жϷ�����

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







































