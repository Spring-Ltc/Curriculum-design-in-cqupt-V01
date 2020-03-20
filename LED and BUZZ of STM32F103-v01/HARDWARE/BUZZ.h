#ifndef __BUZZ_H__
#define __BUZZ_H__

#include "sys.h"


void BUZZ_Init(void);

#define BUZZ PBout(14)
#define BUZZ_ON 		GPIO_SetBits(GPIOB,GPIO_Pin_14)
#define BUZZ_OFF 		GPIO_ResetBits(GPIOB,GPIO_Pin_14)



#endif



