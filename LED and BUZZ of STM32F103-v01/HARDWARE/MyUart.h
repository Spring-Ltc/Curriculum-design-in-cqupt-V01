#ifndef __MYUART_H__
#define __MYUART_H__

#include "sys.h"

#define USART_REC_LEN  			200  	//�����������ֽ��� 200


extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬���	


void MyUart_Init(u32 bound);
 

extern u8 Style_LED;
extern u8 Style_BUZZ;

#endif



