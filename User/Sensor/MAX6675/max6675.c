#include "max6675.h"

/****
������������ȡMAX6675���ص�16λԭʼ����
����16λ����
****/
uint16_t MAX6675_ReadData(void)
{
	uint16_t temp = 0;
	
	/*����Ƭѡ*/
	MAX6675_CSS_Low;
	
	/*�˴�ʵ����ֻ���ڶ�ȡ���ݣ��ʷ��ͼٶ���DUMMY*/
	temp = MAX6675_SPI_Read_Write(DUMMY);
	
	MAX6675_CSS_Hight;
	
	return temp;
}

/*************************************************
Function: MAX6675_AVE
Description: ��ȡ���16λԭʼ���ݣ���ͨ����ֵ�˲��㷨������������
Input: ��
Output:16λ���ݽ��
Return: ��
Others: ��
*************************************************/
uint16_t MAX6675_AVE(void)
{
    uint16_t data[21] = {0};
    uint8_t i = 0,j = 0;
    uint8_t min = 0;
    uint16_t temp = 0;
    for(i = 0;i<21;i++)
    {
        data[i] = MAX6675_ReadData();
        General_TIM_Delay_ms(2);
    }
    
    /*ѡ������*/
    for (i = 0 ; i < 20 ; i++) 
    {
        min = i;
        for (j = i + 1; j < 21; j++)
        {
             if (data[j] < data[min])
             {
                 min = j;    
                 
             }
             temp = data[min];
             data[min] = data[i];
             data[i] = temp;
        }
                
    }
    
    return data[10];/*�����м�ֵ*/
  
}
/*************************************************
Function: MAX6675_DealData
Description: ����MAX6675����ȡ��16λ���ݣ�����ת��Ϊ�¶�ֵ
Input: ����16λԭʼ����
Output:��
Return: ���������͵��¶�ֵ
Others: ��
*************************************************/
float MAX6675_DealData(uint16_t data)
{
	float temp;
	/*��ȡBit3��Bit14��12λ��Чֵ*/
	uint16_t vaild = ((data&0x7FF8)>>3);
	
	/*�����¶�ֵ���˴���MAX6675�ڲ�ADC���12λ��ȷ����ֵ��������ΧΪ0-1023.75��*/
	temp = (vaild*0.25)-2;
	
	return temp;
}

/*************************************************
Function: MAX6675_SPI_Conf
Description: ����MAX6675���õ���SPI2
Input: ��
Output:��
Return: ��
Others: ��
*************************************************/
void MAX6675_SPI_Conf(void)
{
	SPI_InitTypeDef SPI_Init_Struct;
	
	
	MAX6675_SPI_GPIO_Conf();/*����GPIO*/
	
	MAX6675_SPI_RCC_Cmd(MAX6675_RCC_SPI,ENABLE);/*����SPIʱ��*/
	
	/*����SPI����*/
	SPI_Init_Struct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;/*����MAX6675�������ʱ����ƵΪ4.3MHZ*/
	
	SPI_Init_Struct.SPI_CPHA = SPI_CPHA_1Edge;/*��������ֲ�����*/
	SPI_Init_Struct.SPI_CPOL = SPI_CPOL_Low;
	SPI_Init_Struct.SPI_DataSize = SPI_DataSize_16b;
	SPI_Init_Struct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_Init_Struct.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_Init_Struct.SPI_Mode = SPI_Mode_Master;
	
	SPI_Init_Struct.SPI_NSS = SPI_NSS_Soft;/*ѡ�����Ƭѡ*/
	
	SPI_Init_Struct.SPI_CRCPolynomial = 7;/*δʹ��CRCУ��ʱ���˴�������Ч*/
	SPI_Init(MAX6675_SPI_Used,&SPI_Init_Struct);/*δʹ��CRCУ��ʱ���˴�������Ч*/
	
	SPI_Cmd(MAX6675_SPI_Used,ENABLE);/*ʹ��SPI*/
	
}

/*************************************************
Function: MAX6675_SPI_GPIO_Conf
Description: ����SPI2�������
Input: ��
Output:��
Return: ��
Others: ��
*************************************************/
void MAX6675_SPI_GPIO_Conf(void)
{
	GPIO_InitTypeDef GPIOINIT_Struct;
	
	/*����GPIOʱ��*/
	RCC_AHB1PeriphClockCmd(MAX6675_RCC_GPIO,ENABLE);
	
	/*MISO��������*/
	GPIOINIT_Struct.GPIO_Mode = GPIO_Mode_AF;
	GPIOINIT_Struct.GPIO_OType = GPIO_OType_PP;
	GPIOINIT_Struct.GPIO_Pin = MAX6675_SPI_MISO_Pin;
	GPIOINIT_Struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIOINIT_Struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MAX6675_SPI_MISO_Port,&GPIOINIT_Struct);
	GPIO_PinAFConfig(MAX6675_SPI_MISO_Port, MAX6675_SPI_MISO_PinSource, MAX6675_SPI_AF);

	/*SCK��������*/
	GPIOINIT_Struct.GPIO_Mode = GPIO_Mode_AF;
	GPIOINIT_Struct.GPIO_OType = GPIO_OType_PP;
	GPIOINIT_Struct.GPIO_Pin = MAX6675_SPI_SCK_Pin;
	GPIOINIT_Struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIOINIT_Struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MAX6675_SPI_SCK_Port,&GPIOINIT_Struct);	
	GPIO_PinAFConfig(MAX6675_SPI_SCK_Port, MAX6675_SPI_SCK_PinSource, MAX6675_SPI_AF);


	/*���CS��������*/
	GPIOINIT_Struct.GPIO_Mode = GPIO_Mode_OUT;
	GPIOINIT_Struct.GPIO_OType = GPIO_OType_PP;
	GPIOINIT_Struct.GPIO_Pin = MAX6675_SPI_SOFT_CS_Pin;
	GPIOINIT_Struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIOINIT_Struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MAX6675_SPI_SOFT_CS_Port,&GPIOINIT_Struct);
	
	/*ƬѡĬ�ϸߵ�ƽ*/
	MAX6675_CSS_Hight;
}

/*************************************************
Function: MAX6675_SPI_Read_Write
Description: SPI��д����
Input: DataΪд���16λ����
Output:��
Return: ��ȡ��16λ����
Others: ��
*************************************************/
uint16_t MAX6675_SPI_Read_Write(uint16_t Data)
{
	uint16_t d;
	
	while(SPI_I2S_GetFlagStatus(MAX6675_SPI_Used, SPI_I2S_FLAG_TXE)==RESET);
	SPI_I2S_SendData(MAX6675_SPI_Used,Data);
	
	/*���������Ƿ������*/
	while(SPI_I2S_GetFlagStatus(MAX6675_SPI_Used, SPI_I2S_FLAG_RXNE)==RESET);
	
	/*���ݷ������ʱҲ���յ�����*/
	d = (uint16_t)SPI_I2S_ReceiveData(MAX6675_SPI_Used);

	return d;
}



