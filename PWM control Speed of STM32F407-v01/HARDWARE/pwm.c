#include "pwm.h"


void Time3PWM_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	//GPIO�ṹ��
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; //��ʱ���ṹ��
	TIM_OCInitTypeDef TIM_OCInitStruct;		//ͨ���ṹ��
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//ʹ�ܶ�ʱ��3��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE );//ʹ��GPIO��ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;          
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOC,&GPIO_InitStructure);              
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM3);//GPIO�ܽŸ���
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM3);//GPIO�ܽŸ���
	
	//��ʱ����ʼ���������		//��PWMƵ��Ϊ	84M/((83+1)*(999+1))	=	1kHz	��
	TIM_TimeBaseStructure.TIM_Prescaler=83;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=999;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);//��ʼ����ʱ��
	
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;	//PWMģʽ��ģʽ1��ģʽ2��
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;		//���ʹ��
	TIM_OCInitStruct.TIM_Pulse=10;		//�Ƚ�ֵ��дCCRx,������ʼռ�ձ�
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_Low;		//�Ƚ��������
	
	TIM_OC1Init(TIM3,&TIM_OCInitStruct);	//PWM���ͨ����ʼ��
	TIM_OC2Init(TIM3,&TIM_OCInitStruct);	//PWM���ͨ����ʼ��
	
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR1�ϵ�Ԥװ�ؼĴ��� 
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR1�ϵ�Ԥװ�ؼĴ��� 

  TIM_ARRPreloadConfig(TIM3,ENABLE);//ARPEʹ�� 
	TIM_Cmd(TIM3, ENABLE);  //ʹ�ܶ�ʱ��TIM3
}



