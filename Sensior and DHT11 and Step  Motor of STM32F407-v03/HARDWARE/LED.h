#ifndef __LED_H__
#define __LED_H__

#include "sys.h"


//����LED
#define LED0_ON GPIO_ResetBits(GPIOA,GPIO_Pin_6)
#define LED1_ON GPIO_ResetBits(GPIOA,GPIO_Pin_7)

//�ر�LED
#define LED0_OFF GPIO_SetBits(GPIOA,GPIO_Pin_6)
#define LED1_OFF GPIO_SetBits(GPIOA,GPIO_Pin_7)

#define LED0 PAout(6)
#define LED1 PAout(7)



//��������
extern void LED_Init(void);






#endif

