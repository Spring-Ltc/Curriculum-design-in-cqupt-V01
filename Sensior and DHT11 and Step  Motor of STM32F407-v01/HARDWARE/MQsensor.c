#include "MQsensor.h"


//MQ_Sensor烟雾传感器输出电压模拟值
//故采用AD转换获取烟雾浓度
//选取ADC12_IN8，引脚为PB0
void MQ_Init(void)
{
	ADC_InitTypeDef ADC_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	ADC_CommonInitTypeDef ADC_CommonInitStruct;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);//使能GPIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);//使能ADC1时钟

	//先初始化ADC1通道6 的IO口
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AN;//模拟输入
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;	//PA5引脚
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;	//不带上下拉
	GPIO_Init(GPIOB,&GPIO_InitStruct);

	//设置ADC的通用控制寄存器CCR
	ADC_CommonInitStruct.ADC_DMAAccessMode=ADC_DMAAccessMode_Disabled;//不开启DMA传输
	ADC_CommonInitStruct.ADC_Mode=ADC_Mode_Independent;//独立模式
	ADC_CommonInitStruct.ADC_Prescaler=ADC_Prescaler_Div4 ;//预分频4分频。ADCCLK=PCLK2/4=84/4=21Mhz,ADC时钟最好不要超过36Mhz 
	ADC_CommonInitStruct.ADC_TwoSamplingDelay=ADC_TwoSamplingDelay_5Cycles;//两个采样阶段延迟5个时钟
	ADC_CommonInit(&ADC_CommonInitStruct);
	
	//初始化ADC1参数
	ADC_InitStruct.ADC_Resolution=ADC_Resolution_12b;//	12位
	ADC_InitStruct.ADC_ScanConvMode=DISABLE;//关闭扫描模式
	ADC_InitStruct.ADC_ContinuousConvMode=DISABLE;//关闭连续转换
	ADC_InitStruct.ADC_ExternalTrigConvEdge=ADC_ExternalTrigConvEdge_None;//禁止触发检测，使用软件触发
	ADC_InitStruct.ADC_DataAlign=ADC_DataAlign_Right;//右对齐
	ADC_InitStruct.ADC_NbrOfConversion=1;//1个转换在规则序列中 也就是只转换规则序列1 
	ADC_Init(ADC1,&ADC_InitStruct);
	
	ADC_Cmd(ADC1,ENABLE);//开启AD转换
	
}


//获取一次ADC的值
//入口参数：通道，在stm32f4xx_adc.h里面308行处有定义
//返回值：本次转换结果
u16 Get_Adc(u8 Channel)
{
	//配置所选ADC常规通道的对应值,排序器及其采样时间。
	ADC_RegularChannelConfig(ADC1,Channel,1,ADC_SampleTime_480Cycles);
	//【ADC1:选择外围设备，ADC1、ADC2、ADC3里面选】
	//【Channel：需要配置的ADC通道，从0到18里面选一个通道】
	//【1：常规组排序器中的排名，0到16里面选】
	//【ADC_SampleTime_480Cycles：为所选通道设置采样时间（采样时间为几个周期）】
	
	ADC_SoftwareStartConv(ADC1);		//使能指定的ADC1的软件转换启动功能
	
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
	//【ADC_FLAG_EOC：指定要检查的标志位，这里ADC_FLAG_EOC表示转换结束标志】
	
	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
}


//获取通道ch的转换值，取times次,然后平均 
//ch:通道编号
//times:获取次数
//返回值:通道ch的times次转换结果平均值
u16 Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		delay_ms(5);
	}
	return temp_val/times;
} 

//END

