#include "dht12.h"
#include "iic.h"

/*************************************************
Function: DHT12_Read_
Description: ��ȡָ���Ĵ����������
Input: datastoΪ���ڴ洢���ݵ�����ָ�룬addrΪ�Ĵ�����ַ��num Ϊ��ȡ8λ���ݵĸ���
Output: ��
Return: ��
Others: �� 
*************************************************/
void DHT12_Read_(uint8_t *datasto)
{
	uint8_t i;
	Start_Signal();
	/*�����豸д��ַ*/
	I2C_Write_Byte(DHT12_DEV_WRITE_ADDR);
	while(!Wait_Ask());
	
	/*д��Ĵ�����ַ����0x00��ʼ��ȡ*/
	I2C_Write_Byte(0x00);
	while(!Wait_Ask());
	
	/*���·�����ʼ�ź�*/
	Start_Signal();
	
	/*�����豸����ַ*/
	I2C_Write_Byte(DHT12_DEV_READ_ADDR);
	while(!Wait_Ask());
	
	/*������ȡ5������*/
	for(i = 0;i<5;i++)
	{
		datasto[i] = I2C_Read_Byte();
		if(i == 4)
		{
			NAsk_Signal();
		}
		else
		{
			Ask_Signal();
		}
		
	}
	/*��ֹ�ź�*/
	Stop_Signal();
	
}

/*************************************************
Function: DHT12_Deal_Tem_Hum
Description: ��������ת��Ϊ��ʪ��
Input: datastoΪ���ڴ洢���ݵ�����ָ��,���е�һλΪʪ����Ϣ�����Ϊ�¶���Ϣ
	   datasrcΪ����Դָ�룬������ȡ�Ĵ�����5������
Output: ��
Return: ����ֵΪ����˵������������������У����ȷ����1
Others: �� 
*************************************************/
uint8_t DHT12_Deal_Tem_Hum(float* datasto,uint8_t *datasrc)
{
	uint8_t state = 0;
	uint8_t check = 0,i;
	float Tem_Int = 0,Tem_Dec = 0,Hum_Int = 0,Hum_Dec = 0;
	/*ͳһת��Ϊ������*/
	Hum_Int = (float)datasrc[0];
	Hum_Dec = (float)datasrc[1];
	/*�˴����λ��ʾ�¶�����*/
	Tem_Int = (float)(datasrc[2]&0x7F);
	Tem_Dec = (float)datasrc[3];
	
	/*����У���*/
	for(i = 0;i<4;i++)
	{
		check += datasrc[i];
	}
	
	/*�ж�У����Ƿ���ȷ*/
	if(check == datasrc[4])
	{
		/*У�����ȷ����1*/
		state = 1;
		
		/*��ʪ��С��λ������λ��ϣ���д��datasto[0]��*/
		/*С��λֻ��һλ���ʽ����10�ɵ���ʵС��ֵ*/
		datasto[0] = Hum_Int + (Hum_Dec/10.0f);
		
		/*���¶�С��λ������λ��ϣ���д��datasto[1]��*/
        
		/*�¶����ж�����*/
		if((datasrc[2]&0x80)==0x80)/*���λΪ1����ʾ�¶�Ϊ��ֵ*/
		{
			
			datasto[1] = (0-Tem_Int-(Tem_Dec/10.0f));
		}
		else
		{
			datasto[1] = Tem_Int + (Tem_Dec/10.0f);
		}
		
	}
	
	return state;
}

