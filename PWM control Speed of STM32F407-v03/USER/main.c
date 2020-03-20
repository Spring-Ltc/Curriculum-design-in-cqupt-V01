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

u16 step=50;	//PWM的步进值
u16 PWM_san=0;
u16 last_san=0;
u16 PWM_pai=0;
u16 last_pai=0;

//挡位对应的PWM值（1000满）
u16 speed_off=2;
u16 speed1=300;
u16 speed2=650;
u16 speed3=950;

int main(void)
{ 
	u16 len=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);
	My_Usart1Init();
	LED_Init();
	Key_Init();
	
	Time3PWM_Init();

  while(1)
	{
		
		if(USART1_RX_STA&0x8000)
		{
			len=USART1_RX_STA&0x3FFF;//得到数据长度
			SolveDate1(USART1_RX_BUF,len);//对接受的数据进行处理
			USART1_RX_STA=0;//清标志位，准备下一次接收
		}
		
	/*	
		
		if(Style_pai==1)//排风扇关
			PWM_pai=speed_of,Style_pai=0;
		else if(Style_pai==2)	//一档
			PWM_pai=speed1,Style_pai=0;
		else if(Style_pai==1)//二档
			PWM_pai=speed2,Style_pai=0;
		else if(Style_pai==2)//三档
			PWM_pai=speed3,Style_pai=0;
		
		if(Style_san==1)//散热器关
			PWM_san=speed_of,Style_san=0;
		else if(Style_san==2)
			PWM_san=speed1,Style_san=0;
		else if(Style_san==3)
			PWM_san=speed2,Style_san=0;
		else if(Style_san==4)
			PWM_san=speed3,Style_san=0;
		
		//改变排风扇的PWM
		if(PWM_pai!=last_pai)
		{
			TIM_SetCompare1(TIM3,500),delay_ms(50);		//电压过低不能启动，给一个启动电压
			TIM_SetCompare1(TIM3,PWM_pai);
			last_pai=PWM_pai;
		}
		//改变散热器的PWM
		if(PWM_san!=last_san)
		{
			TIM_SetCompare2(TIM3,500),delay_ms(50);		//电压过低不能启动，给一个启动电压
			TIM_SetCompare2(TIM3,PWM_san);
			last_san=PWM_san;
		}
*/
		LED1=!LED1;//break;	//LED1翻转
		delay_ms(250);
		LED0=!LED0;//break;	//LED0翻转
		delay_ms(250);
	}
}


//对接收到的串口1数据进行处理
//@入口参数：date存储接受到数据的起始地址，len为接受的数据的长度
void SolveDate1(char date[],u8 len)
{

	if(strncmp(date,"A",1)==0)
	{
		TIM_SetCompare1(TIM3,999),delay_ms(100);		//电压过低不能启动，给一个启动电压
		TIM_SetCompare1(TIM3,speed_off);
	}
	else if(strncmp(date,"B",1)==0)
	{
		TIM_SetCompare1(TIM3,999),delay_ms(100);		//电压过低不能启动，给一个启动电压
		TIM_SetCompare1(TIM3,speed1);
	}
	else if(strncmp(date,"C",1)==0)
	{
		TIM_SetCompare1(TIM3,999),delay_ms(100);		//电压过低不能启动，给一个启动电压
		TIM_SetCompare1(TIM3,speed2);
	}
	else if(strncmp(date,"D",1)==0)
	{
		TIM_SetCompare1(TIM3,999),delay_ms(100);		//电压过低不能启动，给一个启动电压
		TIM_SetCompare1(TIM3,speed3);
	}
	
	else if(strncmp(date,"a",1)==0)
	{
		TIM_SetCompare2(TIM3,999),delay_ms(100);		//电压过低不能启动，给一个启动电压
		TIM_SetCompare2(TIM3,speed_off);
	}
	else if(strncmp(date,"b",1)==0)
	{
		TIM_SetCompare2(TIM3,999),delay_ms(100);		//电压过低不能启动，给一个启动电压
		TIM_SetCompare2(TIM3,speed1);
	}
	else if(strncmp(date,"c",1)==0)
	{
		TIM_SetCompare2(TIM3,999),delay_ms(100);		//电压过低不能启动，给一个启动电压
		TIM_SetCompare2(TIM3,speed2);
	}
	else if(strncmp(date,"d",1)==0)
	{
		TIM_SetCompare2(TIM3,999),delay_ms(100);		//电压过低不能启动，给一个启动电压
		TIM_SetCompare2(TIM3,speed3);
	}
	
	
}
