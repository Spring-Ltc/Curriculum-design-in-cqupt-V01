#include "Key.h"
#include "delay.h"

void Key_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOA,GPIOE时钟
 
	//按键初始化设置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4; //KEY0 KEY1 KEY2对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE2,3,4
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//WK_UP对应引脚PA0
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;//下拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA0
	
}


//按键键值读取函数
u8 key_scanf(void)
{
	u8 k=0;
	if(KEY0==0||KEY1==0||KEY2==0||WK_UP==1)
	{
		delay_ms(5);//按键消抖
		if(KEY0==0)
			k= 1;
		else if(KEY1==0)
			k= 2;
		else if(KEY2==0)
			k= 3;
		else if(WK_UP==1)
			k= 4;
		
		while((KEY0==0||KEY1==0||KEY2==0||WK_UP==1));//松手检测
	}
	return k;	//没有按键按下返回值为0	
}








