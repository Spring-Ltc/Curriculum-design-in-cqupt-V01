#ifndef __MOTOR_H__
#define __MOTOR_H__


#include "sys.h"

#define OUT1 PAout(2)
#define OUT2 PAout(3)
#define OUT3 PAout(4)
#define OUT4 PAout(5)


void Motor_Init(void);
void open_Window(u16 time);
void close_Window(u16 time);



#endif


