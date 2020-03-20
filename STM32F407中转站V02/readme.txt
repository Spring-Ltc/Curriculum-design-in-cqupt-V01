

--------------------------STM32F407ZGT6中转站--------------------------------

节点1：
	连接STM32F103C8T6最小系统,波特率115200
	USART3			PB10-TX;PB11-RX
	控制 LED照明 和 蜂鸣器报警
	指令关系：
		LED切换-----------------A
		LED闪烁-----------------B
		关闭蜂鸣器--------------b
		蜂鸣器长鸣--------------a
		周期性鸣叫--------------c
		
	其他：
		暂时只需要发送控制命令，不需要开接收中断
		
		
		
节点2：
	连接到STM32F407VET6最小系统，波特率9600
	USART2			PA2-TX;PA3-RX
	控制 DHT11温湿度采集 和 步进电机拉动窗帘
	//////////增加烟雾传感器，AD转换，采集模拟值
	指令关系：
		开窗帘--------------------o
		只开一半窗帘--------------h
		关窗帘--------------------c
		读取一次温湿度------------A





节点4：
	连接到STM32F407，波特率19200
	USART6		TX--PC6;	RX--PC7
	控制电机驱动散热器风扇和排风扇
	指令关系：
		散热器加速-----------------B
		散热器减速-----------------b
		排风扇加速-----------------A
		排风扇减速-----------------a

	



		
		
节点4：
	连接到ESP8266核心板,波特率74880
	USART1			PA9-TX;PA10-RX
	访问云服务器交互数据
	指令关系：
		LED切换-----------------"LED_Switch"-------------light_switch
		LED闪烁-----------------"LED_Flashing"-----------light_flash
		关闭蜂鸣器--------------"BUZZ_off"----------------buzz_off
		蜂鸣器长鸣--------------"BUZZ_on"-----------------buzz_on
		周期性鸣叫--------------"BUZZ_turn"---------------buzz_turn
		
		开窗帘--------------------"Window_open"
	88	只开一半窗帘--------------"Window_half"
		关窗帘--------------------"Window_close"
		读取一次温湿度------------"GetDate"
		
		散热器开-------------------“Speed_san_ON”
		散热器加速-----------------"Speed_san_UP"
		散热器减速-----------------"Speed_san_DOWN"
		散热器关--------------------“Speed_san_OFF”

		排风扇开---------------------“Speed_pai_ON”
		排风扇加速-----------------"Speed_pai_UP"
		排风扇减速-----------------"Speed_pai_DOWN"
		排风扇关---------------------“Speed_pai_OFF”
		
		
处理数据后，要及时清理数据接收缓存区	
		
		
		
---------------------------其他笔记	----------------------------



1.可以包含C语言中能包含的库函数：
如：	
	#include <stdio.h>
		fopen						fclose
		tmpnam						tmpfile
		remove						rename
		fprintf						printf
		sprintf						snprintf
		fscanf						scanf
		
		
	#include <string.h>		//字符串相关函数
		memcpy						strchr
		memmove						memchr
		strcpy						strcspn
		strncpy						strpbrk
		strcat						strstr
		strncat
		memcmp
		strcmp
		strncmp
		strcasecmp


2.把整形数据转化为字符串
	可以用sprintf()函数：		
		例如：  springf(address,%d,123)	//把整形数字123转化为字符串"123"存在地址 address中

3.比较两个字符串中的前 n 个字符
	strncmp函数为字符串比较函数，字符串大小的比较是以ASCII 码表上的顺序来决定，此顺序亦为字符的值。
	其函数声明为int strncmp ( const char * str1, const char * str2, size_t n );
	功能是把 str1 和 str2 进行比较，最多比较前 n 个字节，
	若str1与str2的前n个字符相同，则返回0；
	若s1大于s2，则返回大于0的值；
	若s1 小于s2，则返回小于0的值
		
		
		
		
		
USART4硬件连接:	
		TX-----PA0
		RX-----PA1
		
		
/////////////////////选择////////////////		
USART5硬件连接:	
		TX-----PC12
		RX-----PD2
		
			
		
		
USART6硬件连接:	
		TX-----PC6	/G14
		RX-----PC7	/G9
		
			
		
		
		
		
		
		
		
		
		