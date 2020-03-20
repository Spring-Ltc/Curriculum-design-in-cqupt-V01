//���õ����߷�ʽ��ȡ����
//����Ҫͬʱ����Ϊ�����������������������衾�����������Ѿ���ӡ�
//STM32������Ҫ����Ϊ��©���  OD
//�����ʱ��Ҫ�Ƚ������ø�


#include "DHT.h"

u16 wendu=40;
u16 shidu=50;

   
//��λDHT
void DHT_Rst(void)	   
{                 
	DHT_IO_OUT(); 	//SET OUTPUT
  DHT_DQ_OUT=0; 	//����DQ
  delay_ms(20);    	//��������18ms
  DHT_DQ_OUT=1; 	//DQ=1 
	delay_us(30);     	//��������20~40us
}
//�ȴ�DHT�Ļ�Ӧ
//����1:δ��⵽DHT�Ĵ���
//����0:����
u8 DHT_Check(void) 	   
{   
	u8 retry=0;
	DHT_IO_IN();//SET INPUT	 
    while (DHT_DQ_IN&&retry<100)//DHT������40~80us
	{
		retry++;
		delay_us(1);
	};	 
	if(retry>=100)return 1;
	else retry=0;
    while (!DHT_DQ_IN&&retry<100)//DHT���ͺ���ٴ�����40~80us
	{
		retry++;
		delay_us(1);
	};
	if(retry>=100)return 1;	    
	return 0;
}
//��DHT��ȡһ��λ
//����ֵ��1/0
u8 DHT_Read_Bit(void) 			 
{
 	u8 retry=0;
	while(DHT_DQ_IN&&retry<100)//�ȴ���Ϊ�͵�ƽ
	{
		retry++;
		delay_us(1);
	}
	retry=0;
	while(!DHT_DQ_IN&&retry<100)//�ȴ���ߵ�ƽ
	{
		retry++;
		delay_us(1);
	}
	delay_us(40);//�ȴ�40us
	if(DHT_DQ_IN)
		return 1;
	else return 0;		   
}
//��DHT��ȡһ���ֽ�
//����ֵ������������
u8 DHT_Read_Byte(void)    
{        
    u8 i,dat;
    dat=0;
	for (i=0;i<8;i++) 
	{
   		dat<<=1; 
	    dat|=DHT_Read_Bit();
    }						    
    return dat;
}
//��DHT��ȡһ������
//temp:�¶�ֵ(��Χ:0~50��)
//humi:ʪ��ֵ(��Χ:20%~90%)
//����ֵ��0,����;1,��ȡʧ��
u8 DHT_Read_Data(u8 *temp,u8 *humi)    
{        
 	u8 buf[5];
	u8 i;
	DHT_Rst();
	if(DHT_Check()==0)
	{
		for(i=0;i<5;i++)//��ȡ40λ����
		{
			buf[i]=DHT_Read_Byte();
		}
		if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])
		{
			*humi=buf[0];
			*temp=buf[2];
		}
	}else return 1;
	return 0;	    
}
//��ʼ��DHT��IO�� DQ ͬʱ���DHT�Ĵ���
//����1:������
//����0:����    	 
u8 DHT_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��GPIOGʱ��

  //GPIOF9,F10��ʼ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��
	DHT_Rst();
	return DHT_Check();
}







