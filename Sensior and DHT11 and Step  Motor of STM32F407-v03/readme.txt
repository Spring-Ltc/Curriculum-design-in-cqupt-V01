实验器材:
	STM32F407VET6最小系统板（LQFP100封装）
	
板载硬件连接：
		LED2(D2)------PA6
		LED3(D3)------PA7
		
		K_UP------PA0		已经下拉
		K0------PE4		已经上拉
		K1------PE3		已经上拉
		
		
		
		
-------------------温湿度、步进电机、烟雾浓度 节点--------------------------------------------------------------------------

程序功能：
	DHT11温湿度采集，通过串口USART1发送
		单总线数据传输：PB9
		
		
	步进电机控制窗帘升降
		A、B、C、D四相输出对应 PA2.3.4.5
		
		
	MQ_Sensor采集烟雾浓度
		12位AD转换器：	ADC12_IN8------PB0
		
		
		
		
		
		
		
		
		
		
		
		
		
		