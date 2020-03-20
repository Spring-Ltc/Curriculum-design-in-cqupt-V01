#include "pwm.h"


void Time3PWM_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	//GPIO结构体
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; //定时器结构体
	TIM_OCInitTypeDef TIM_OCInitStruct;		//通道结构体
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//使能定时器3的时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE );//使能GPIO的时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;          
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOC,&GPIO_InitStructure);              
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM3);//GPIO管脚复用
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM3);//GPIO管脚复用
	
	//定时器初始化相关设置		//【PWM频率为	84M/((83+1)*(999+1))	=	1kHz	】
	TIM_TimeBaseStructure.TIM_Prescaler=83;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=999;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);//初始化定时器
	
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;	//PWM模式（模式1或模式2）
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;		//输出使能
	TIM_OCInitStruct.TIM_Pulse=10;		//比较值，写CCRx,决定初始占空比
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_Low;		//比较输出极性
	
	TIM_OC1Init(TIM3,&TIM_OCInitStruct);	//PWM输出通道初始化
	TIM_OC2Init(TIM3,&TIM_OCInitStruct);	//PWM输出通道初始化
	
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR1上的预装载寄存器 
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR1上的预装载寄存器 

  TIM_ARRPreloadConfig(TIM3,ENABLE);//ARPE使能 
	TIM_Cmd(TIM3, ENABLE);  //使能定时器TIM3
}



