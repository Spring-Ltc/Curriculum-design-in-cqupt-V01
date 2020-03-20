#include "MQsensor.h"


//MQ_Sensor�������������ѹģ��ֵ
//�ʲ���ADת����ȡ����Ũ��
//ѡȡADC12_IN8������ΪPB0
void MQ_Init(void)
{
	ADC_InitTypeDef ADC_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	ADC_CommonInitTypeDef ADC_CommonInitStruct;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);//ʹ��GPIOʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);//ʹ��ADC1ʱ��

	//�ȳ�ʼ��ADC1ͨ��6 ��IO��
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AN;//ģ������
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;	//PA5����
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;	//����������
	GPIO_Init(GPIOB,&GPIO_InitStruct);

	//����ADC��ͨ�ÿ��ƼĴ���CCR
	ADC_CommonInitStruct.ADC_DMAAccessMode=ADC_DMAAccessMode_Disabled;//������DMA����
	ADC_CommonInitStruct.ADC_Mode=ADC_Mode_Independent;//����ģʽ
	ADC_CommonInitStruct.ADC_Prescaler=ADC_Prescaler_Div4 ;//Ԥ��Ƶ4��Ƶ��ADCCLK=PCLK2/4=84/4=21Mhz,ADCʱ����ò�Ҫ����36Mhz 
	ADC_CommonInitStruct.ADC_TwoSamplingDelay=ADC_TwoSamplingDelay_5Cycles;//���������׶��ӳ�5��ʱ��
	ADC_CommonInit(&ADC_CommonInitStruct);
	
	//��ʼ��ADC1����
	ADC_InitStruct.ADC_Resolution=ADC_Resolution_12b;//	12λ
	ADC_InitStruct.ADC_ScanConvMode=DISABLE;//�ر�ɨ��ģʽ
	ADC_InitStruct.ADC_ContinuousConvMode=DISABLE;//�ر�����ת��
	ADC_InitStruct.ADC_ExternalTrigConvEdge=ADC_ExternalTrigConvEdge_None;//��ֹ������⣬ʹ���������
	ADC_InitStruct.ADC_DataAlign=ADC_DataAlign_Right;//�Ҷ���
	ADC_InitStruct.ADC_NbrOfConversion=1;//1��ת���ڹ��������� Ҳ����ֻת����������1 
	ADC_Init(ADC1,&ADC_InitStruct);
	
	ADC_Cmd(ADC1,ENABLE);//����ADת��
	
}


//��ȡһ��ADC��ֵ
//��ڲ�����ͨ������stm32f4xx_adc.h����308�д��ж���
//����ֵ������ת�����
u16 Get_Adc(u8 Channel)
{
	//������ѡADC����ͨ���Ķ�Ӧֵ,�������������ʱ�䡣
	ADC_RegularChannelConfig(ADC1,Channel,1,ADC_SampleTime_480Cycles);
	//��ADC1:ѡ����Χ�豸��ADC1��ADC2��ADC3����ѡ��
	//��Channel����Ҫ���õ�ADCͨ������0��18����ѡһ��ͨ����
	//��1���������������е�������0��16����ѡ��
	//��ADC_SampleTime_480Cycles��Ϊ��ѡͨ�����ò���ʱ�䣨����ʱ��Ϊ�������ڣ���
	
	ADC_SoftwareStartConv(ADC1);		//ʹ��ָ����ADC1�����ת����������
	
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
	//��ADC_FLAG_EOC��ָ��Ҫ���ı�־λ������ADC_FLAG_EOC��ʾת��������־��
	
	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
}


//��ȡͨ��ch��ת��ֵ��ȡtimes��,Ȼ��ƽ�� 
//ch:ͨ�����
//times:��ȡ����
//����ֵ:ͨ��ch��times��ת�����ƽ��ֵ
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

