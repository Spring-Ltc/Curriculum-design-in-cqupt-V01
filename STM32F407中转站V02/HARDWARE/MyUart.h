#ifndef __MYUART_H__
#define __MYUART_H__

#include "sys.h"


#define USART1_RX_LEN   200			//数据接收最大长度
#define USART2_RX_LEN   200
#define USART3_RX_LEN   200

extern char USART1_RX_BUF[USART1_RX_LEN];		//接收数据缓存
extern char USART2_RX_BUF[USART2_RX_LEN];
extern char USART3_RX_BUF[USART3_RX_LEN];

extern u16 USART1_RX_STA;		//接收状态标志位
extern u16 USART2_RX_STA;
extern u16 USART3_RX_STA;


void My_Usart6Init(void);
void My_Usart3Init(void);
void My_Usart2Init(void);
void My_Usart1Init(void);
void Uart1_SentDate(char date[],u8 len);
void Uart2_SentDate(char date[],u8 len);




#endif


