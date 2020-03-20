#include "MyUart.h"
#include "sys.h"
#include "lcd.h"

u16 step=0;

char USART1_RX_BUF[USART1_RX_LEN]={0};		//接收数据缓存
char USART2_RX_BUF[USART2_RX_LEN]={0};
char USART3_RX_BUF[USART3_RX_LEN]={0};



u16 USART1_RX_STA=0;		//接收状态标志位
u16 USART2_RX_STA=0;
u16 USART3_RX_STA=0;
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目


//-------------串口初始化函数，注意中断的优先级和波特率哦-------------------------------

//USART6，和STM32F407VET6通信，控制电机
void My_Usart6Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;//GPIO初始化结构体
	USART_InitTypeDef USART_InitStruct;//串口相关变量结构体
	//NVIC_InitTypeDef NVIC_InitStruct;//中断相关变量结构体

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE);//串口时钟使能
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);//IO时钟使能

	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_USART6);//管脚复用映射
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_USART6);

	
	//GPIO初始化设置
	GPIO_InitStruct.GPIO_Mode =GPIO_Mode_AF;//复用模式
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStruct);

	//串口初始化设置
	USART_InitStruct.USART_BaudRate=19200;
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStruct.USART_Parity=USART_Parity_No;
	USART_InitStruct.USART_StopBits=USART_StopBits_1;
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;//字长
	USART_Init(USART6,&USART_InitStruct);

	USART_Cmd(USART6,ENABLE);//使能串口
	//USART_ITConfig(USART6,USART_IT_RXNE,ENABLE);//开串口中断【只开了接收中断】
/*
	//中断优先级相关初始化设置
	NVIC_InitStruct.NVIC_IRQChannel=USART6_IRQn;//通道选择
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0x01;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0x01;
	NVIC_Init(&NVIC_InitStruct);
	*/
}
//USART6初始化完毕



//UART5，和ESP8266通信，只只发送
void My_Uart5Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;//GPIO初始化结构体
	USART_InitTypeDef USART_InitStruct;//串口相关变量结构体
	//NVIC_InitTypeDef NVIC_InitStruct;//中断相关变量结构体

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);//串口时钟使能
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOD,ENABLE);//IO时钟使能

	GPIO_PinAFConfig(GPIOD,GPIO_PinSource2,GPIO_AF_UART5);//管脚复用映射
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource12,GPIO_AF_UART5);

	
	//GPIO初始化设置
	GPIO_InitStruct.GPIO_Mode =GPIO_Mode_AF;//复用模式
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_12;
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_2;
	GPIO_Init(GPIOD,&GPIO_InitStruct);
	

	//串口初始化设置
	USART_InitStruct.USART_BaudRate=74880;
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStruct.USART_Parity=USART_Parity_No;
	USART_InitStruct.USART_StopBits=USART_StopBits_1;
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;//字长
	USART_Init(UART5,&USART_InitStruct);

	USART_Cmd(UART5,ENABLE);//使能串口
	
	
	//USART_ITConfig(USART6,USART_IT_RXNE,ENABLE);//开串口中断【只开了接收中断】
/*
	//中断优先级相关初始化设置
	NVIC_InitStruct.NVIC_IRQChannel=USART6_IRQn;//通道选择
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0x01;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0x01;
	NVIC_Init(&NVIC_InitStruct);
	*/
}
//USART5初始化完毕


//USART3，和STM32F103C8T6通信
void My_Usart3Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;//GPIO初始化结构体
	USART_InitTypeDef USART_InitStruct;//串口相关变量结构体
	//NVIC_InitTypeDef NVIC_InitStruct;//中断相关变量结构体

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//串口时钟使能
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);//IO时钟使能

	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3);//管脚复用映射
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3);

	//GPIO初始化设置
	GPIO_InitStruct.GPIO_Mode =GPIO_Mode_AF;//复用模式
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_11|GPIO_Pin_10;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);

	//串口初始化设置
	USART_InitStruct.USART_BaudRate=115200;
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStruct.USART_Parity=USART_Parity_No;
	USART_InitStruct.USART_StopBits=USART_StopBits_1;
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;//字长
	USART_Init(USART3,&USART_InitStruct);

	USART_Cmd(USART3,ENABLE);//使能串口
	//USART_ITConfig(USART3,USART_IT_TXE,ENABLE);//开串口中断【只开了发送中断】
/*
	//中断优先级相关初始化设置
	NVIC_InitStruct.NVIC_IRQChannel=USART3_IRQn;//通道选择
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0x01;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0x01;
	NVIC_Init(&NVIC_InitStruct);
	*/
}
//USART3初始化完毕

//USART2，和STM32F407VET6通信
void My_Usart2Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;//GPIO初始化结构体
	USART_InitTypeDef USART_InitStruct;//串口相关变量结构体
	NVIC_InitTypeDef NVIC_InitStruct;//中断相关变量结构体

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//串口时钟使能
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//IO时钟使能

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2);//管脚复用映射
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2);

	//GPIO初始化设置
	GPIO_InitStruct.GPIO_Mode =GPIO_Mode_AF;//复用模式
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);

	//串口初始化设置
	USART_InitStruct.USART_BaudRate=9600;
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStruct.USART_Parity=USART_Parity_No;
	USART_InitStruct.USART_StopBits=USART_StopBits_1;
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;//字长
	USART_Init(USART2,&USART_InitStruct);

	USART_Cmd(USART2,ENABLE);//使能串口
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);//开串口中断【只开了发送中断】

	//中断优先级相关初始化设置
	NVIC_InitStruct.NVIC_IRQChannel=USART2_IRQn;//通道选择
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0x01;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0x01;
	NVIC_Init(&NVIC_InitStruct);
}
//USART2初始化完毕

//USART1，和ESP8266服务器通信
void My_Usart1Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;//GPIO初始化结构体
	USART_InitTypeDef USART_InitStruct;//串口相关变量结构体
	NVIC_InitTypeDef NVIC_InitStruct;//中断相关变量结构体

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//串口时钟使能
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//IO时钟使能

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);//管脚复用映射
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);

	//GPIO初始化设置
	GPIO_InitStruct.GPIO_Mode =GPIO_Mode_AF;//复用模式
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_10;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_25MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);

	//串口初始化设置
	USART_InitStruct.USART_BaudRate=74880;
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStruct.USART_Parity=USART_Parity_No;
	USART_InitStruct.USART_StopBits=USART_StopBits_1;
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;//字长
	USART_Init(USART1,&USART_InitStruct);

	USART_Cmd(USART1,ENABLE);//使能串口
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//开串口中断【只开了发送中断】

	//中断优先级相关初始化设置
	NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQn;//通道选择
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0x02;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0x02;
	NVIC_Init(&NVIC_InitStruct);
}
//USART1初始化完毕

//--------------------------所以串口初始化完毕---------------------------------


//---------------------------串口中断服务函数-----------------------------------
//串口1中断服务函数
//接收ESP8266指令并发送采集数据
void USART1_IRQHandler(void)
{
	u8 res;
	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)	//判断是不是接受中断
	{
		res=USART_ReceiveData(USART1);	//读取接收到的数据
		if((USART1_RX_STA&0x8000)==0)//判断是否接收完毕【最高位置1，表示接收完毕】,没有接收完毕才执行
		{
			if(USART1_RX_STA&0x4000)//判断上一次是否接收到了标志数据0x0d
			{
				if(res==0x0a)
					USART1_RX_STA|=0x8000;//正常接收一次数据完毕
				else
					USART1_RX_STA=0;//接收异常，清除数据
			}
			else
			{
				if(res==0x0d)
					USART1_RX_STA|=0x4000;
				else
				{
					USART1_RX_BUF[USART1_RX_STA&0x3fff]=(char)res;
					USART1_RX_STA++;
					if(USART1_RX_STA>=USART1_RX_LEN)
						USART1_RX_STA=0;//数据长度超出限制
				}
			}
		}			
	}						
}

/*
//串口2中断服务函数
//接收STM32F407采集的数据并发送步进电机控制指令
void USART2_IRQHandler(void)
{
	u8 res;
	if(USART_GetITStatus(USART2,USART_IT_RXNE)==SET)	//判断是不是接受中断
	{
		res=USART_ReceiveData(USART2);	//读取接收到的数据
		if((USART2_RX_STA&0x8000)==0)//判断是否接收完毕【最高位置1，表示接收完毕】,没有接收完毕才执行
		{
			if(USART2_RX_STA&0x4000)//判断上一次是否接收到了标志数据0x0d
			{
				if(res==0x0a)
					USART2_RX_STA|=0x8000;//正常接收一次数据完毕
				else
					USART2_RX_STA=0;//接收异常，清除数据
			}
			else
			{
				if(res==0x0d)
					USART2_RX_STA|=0x4000;
				else
				{
					USART2_RX_BUF[USART2_RX_STA&0x3fff]=res;
					USART2_RX_STA++;
					if(USART2_RX_STA>=USART2_RX_LEN)
						USART2_RX_STA=0;//数据长度超出限制
				}
			}
		}			
	}						
}
*/

//串口2中断服务函数
//暂时不需要接收数据
void USART2_IRQHandler(void)
{
	u8 res;
	if(USART_GetITStatus(USART2,USART_IT_RXNE)==SET)	//判断是不是接受中断
	{
		res=USART_ReceiveData(USART2);	//读取接收到的数据
		if((USART2_RX_STA&0x8000)==0)//判断是否接收完毕【最高位置1，表示接收完毕】,没有接收完毕才执行
		{
			if(USART2_RX_STA&0x4000)//判断上一次是否接收到了标志数据0x0d
			{
				if(res==0x0a)
					USART2_RX_STA|=0x8000;//正常接收一次数据完毕
				else
					USART2_RX_STA=0;//接收异常，清除数据
			}
			else
			{
				if(res==0x0d)
					USART2_RX_STA|=0x4000;
				else
				{
					USART2_RX_BUF[USART2_RX_STA&0x3fff]=res;
					USART2_RX_STA++;
					if(USART2_RX_STA>=USART2_RX_LEN)
						USART2_RX_STA=0;//数据长度超出限制
				}
			}
		}			
	}						
}

//---------------------------串口中断服务函数完毕-----------------------------------




//----------------------------串口数据发送函数---------------------------------------


void Uart1_SentDate(char date[],u8 len)
{
	u8 i=0;
	for(i=0;i<len;i++)
	{
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);//等待发送缓冲区清空
		USART_SendData(USART1,(u8)date[i]);
	}
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);
	USART_SendData(USART1,0x0d);//【发送一个字节】
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);
	USART_SendData(USART1,0x0a);//【发送一个字节】
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);
	
}



void Uart2_SentDate(char date[],u8 len)
{
	u8 i=0;
	for(i=0;i<len;i++)
	{
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);//等待发送缓冲区清空
		USART_SendData(USART2,(u8)date[i]);
	}
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);
	USART_SendData(USART2,0x0d);//【发送一个字节】
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);
	USART_SendData(USART2,0x0a);//【发送一个字节】
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);
}


void Uart5_SentDate(char date[],u8 len)
{
	u8 i=0;
	for(i=0;i<len;i++)
	{
		while(USART_GetFlagStatus(UART5,USART_FLAG_TC)==RESET);//等待发送缓冲区清空
		USART_SendData(UART5,(u8)date[i]);
	}
}



void Uart6_SentDate(char date[],u8 len)
{
	u8 i=0;
	for(i=0;i<len;i++)
	{
		while(USART_GetFlagStatus(USART6,USART_FLAG_TC)==RESET);//等待发送缓冲区清空
		USART_SendData(USART6,(u8)date[i]);
	}
	while(USART_GetFlagStatus(USART6,USART_FLAG_TC)!= SET);
	USART_SendData(USART6,0x0d);//【发送一个字节】
	while(USART_GetFlagStatus(USART6,USART_FLAG_TC)!= SET);
	USART_SendData(USART6,0x0a);//【发送一个字节】
	while(USART_GetFlagStatus(USART6,USART_FLAG_TC)!= SET);
}

//-------------------------------------分割线-------------------------------------------------------




