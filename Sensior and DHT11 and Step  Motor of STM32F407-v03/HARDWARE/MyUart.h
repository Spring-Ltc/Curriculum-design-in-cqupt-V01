#ifndef __MYUART_H__
#define __MYUART_H__

#include "sys.h"

#define USART1_RX_LEN   200			//���ݽ�����󳤶�


void My_Usart3Init(void);
void My_Usart1Init(void);
void Uart3_SentBit(u8 date);
void Uart1_SentBit(u8 date);
void Uart1_SentDate(char date[],u8 len);
extern u8 Style_Window;
extern u8 Style_DHT;
extern u8 Style_MQ;

extern u16 USART1_RX_STA;		//����״̬��־λ
extern char USART1_RX_BUF[USART1_RX_LEN];		//�������ݻ���





#endif


