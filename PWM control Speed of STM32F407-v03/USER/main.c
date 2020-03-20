#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"

#include "Key.h"
#include "LED.h"
#include "MyUart.h"
#include "pwm.h"

#include "string.h"
#include "stdio.h"


void SolveDate1(char date[],u8 len);

u16 step=50;	//PWM�Ĳ���ֵ
u16 PWM_san=0;
u16 last_san=0;
u16 PWM_pai=0;
u16 last_pai=0;

//��λ��Ӧ��PWMֵ��1000����
u16 speed_off=2;
u16 speed1=300;
u16 speed2=650;
u16 speed3=950;

int main(void)
{ 
	u16 len=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);
	My_Usart1Init();
	LED_Init();
	Key_Init();
	
	Time3PWM_Init();

  while(1)
	{
		
		if(USART1_RX_STA&0x8000)
		{
			len=USART1_RX_STA&0x3FFF;//�õ����ݳ���
			SolveDate1(USART1_RX_BUF,len);//�Խ��ܵ����ݽ��д���
			USART1_RX_STA=0;//���־λ��׼����һ�ν���
		}
		
	/*	
		
		if(Style_pai==1)//�ŷ��ȹ�
			PWM_pai=speed_of,Style_pai=0;
		else if(Style_pai==2)	//һ��
			PWM_pai=speed1,Style_pai=0;
		else if(Style_pai==1)//����
			PWM_pai=speed2,Style_pai=0;
		else if(Style_pai==2)//����
			PWM_pai=speed3,Style_pai=0;
		
		if(Style_san==1)//ɢ������
			PWM_san=speed_of,Style_san=0;
		else if(Style_san==2)
			PWM_san=speed1,Style_san=0;
		else if(Style_san==3)
			PWM_san=speed2,Style_san=0;
		else if(Style_san==4)
			PWM_san=speed3,Style_san=0;
		
		//�ı��ŷ��ȵ�PWM
		if(PWM_pai!=last_pai)
		{
			TIM_SetCompare1(TIM3,500),delay_ms(50);		//��ѹ���Ͳ�����������һ��������ѹ
			TIM_SetCompare1(TIM3,PWM_pai);
			last_pai=PWM_pai;
		}
		//�ı�ɢ������PWM
		if(PWM_san!=last_san)
		{
			TIM_SetCompare2(TIM3,500),delay_ms(50);		//��ѹ���Ͳ�����������һ��������ѹ
			TIM_SetCompare2(TIM3,PWM_san);
			last_san=PWM_san;
		}
*/
		LED1=!LED1;//break;	//LED1��ת
		delay_ms(250);
		LED0=!LED0;//break;	//LED0��ת
		delay_ms(250);
	}
}


//�Խ��յ��Ĵ���1���ݽ��д���
//@��ڲ�����date�洢���ܵ����ݵ���ʼ��ַ��lenΪ���ܵ����ݵĳ���
void SolveDate1(char date[],u8 len)
{

	if(strncmp(date,"A",1)==0)
	{
		TIM_SetCompare1(TIM3,999),delay_ms(100);		//��ѹ���Ͳ�����������һ��������ѹ
		TIM_SetCompare1(TIM3,speed_off);
	}
	else if(strncmp(date,"B",1)==0)
	{
		TIM_SetCompare1(TIM3,999),delay_ms(100);		//��ѹ���Ͳ�����������һ��������ѹ
		TIM_SetCompare1(TIM3,speed1);
	}
	else if(strncmp(date,"C",1)==0)
	{
		TIM_SetCompare1(TIM3,999),delay_ms(100);		//��ѹ���Ͳ�����������һ��������ѹ
		TIM_SetCompare1(TIM3,speed2);
	}
	else if(strncmp(date,"D",1)==0)
	{
		TIM_SetCompare1(TIM3,999),delay_ms(100);		//��ѹ���Ͳ�����������һ��������ѹ
		TIM_SetCompare1(TIM3,speed3);
	}
	
	else if(strncmp(date,"a",1)==0)
	{
		TIM_SetCompare2(TIM3,999),delay_ms(100);		//��ѹ���Ͳ�����������һ��������ѹ
		TIM_SetCompare2(TIM3,speed_off);
	}
	else if(strncmp(date,"b",1)==0)
	{
		TIM_SetCompare2(TIM3,999),delay_ms(100);		//��ѹ���Ͳ�����������һ��������ѹ
		TIM_SetCompare2(TIM3,speed1);
	}
	else if(strncmp(date,"c",1)==0)
	{
		TIM_SetCompare2(TIM3,999),delay_ms(100);		//��ѹ���Ͳ�����������һ��������ѹ
		TIM_SetCompare2(TIM3,speed2);
	}
	else if(strncmp(date,"d",1)==0)
	{
		TIM_SetCompare2(TIM3,999),delay_ms(100);		//��ѹ���Ͳ�����������һ��������ѹ
		TIM_SetCompare2(TIM3,speed3);
	}
	
	
}
