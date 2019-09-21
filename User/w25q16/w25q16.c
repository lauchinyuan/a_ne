#include "w25q16.h"


/*************************************************
Function: W25Q16_GPIO_Conf
Description: ��������
Input: ��
Output:��
Return: ��
Others: �������ù̶�Ƭѡ����ΪPB14
*************************************************/
static void W25Q16_GPIO_Conf(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitTypeDef GPIOINIT_Struct;
    /*����GPIOʱ��*/
    RCC_AHB1PeriphClockCmd(W25Q16_GPIO_RCC, ENABLE);
	
	/*MISO��������*/
	GPIOINIT_Struct.GPIO_Mode = GPIO_Mode_AF;
	GPIOINIT_Struct.GPIO_OType = GPIO_OType_PP;
	GPIOINIT_Struct.GPIO_Pin = W25Q16_SPI_MISO_Pin;
	GPIOINIT_Struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIOINIT_Struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(W25Q16_SPI_MISO_Port,&GPIOINIT_Struct);
	GPIO_PinAFConfig(W25Q16_SPI_MISO_Port, W25Q16_SPI_MISO_PinSource, W25Q16_SPI_AF);

	/*SCK��������*/
	GPIOINIT_Struct.GPIO_Mode = GPIO_Mode_AF;
	GPIOINIT_Struct.GPIO_OType = GPIO_OType_PP;
	GPIOINIT_Struct.GPIO_Pin = W25Q16_SPI_SCK_Pin;
	GPIOINIT_Struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIOINIT_Struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(W25Q16_SPI_SCK_Port,&GPIOINIT_Struct);	
	GPIO_PinAFConfig(W25Q16_SPI_SCK_Port, W25Q16_SPI_SCK_PinSource, W25Q16_SPI_AF);
	
	/*MOSI��������*/
	GPIOINIT_Struct.GPIO_Mode = GPIO_Mode_AF;
	GPIOINIT_Struct.GPIO_OType = GPIO_OType_PP;
	GPIOINIT_Struct.GPIO_Pin = W25Q16_SPI_MOSI_Pin;
    GPIOINIT_Struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIOINIT_Struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(W25Q16_SPI_MOSI_Port,&GPIOINIT_Struct);
	GPIO_PinAFConfig(W25Q16_SPI_MOSI_Port, W25Q16_SPI_MOSI_PinSource, W25Q16_SPI_AF);

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = W25Q16_CS_GPIOPin;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(W25Q16_CS_GPIOPort, &GPIO_InitStruct);
}

/*************************************************
Function: W25Q16_Write_Enable
Description: W25Q16дʹ��
Input: ��
Output:��
Return: ��
Others: ��
*************************************************/
static void W25Q16_Write_Enable(void)
{
	W25Q16_CS_Low;
	W25Q16_Read_Write(0x06);
	W25Q16_CS_Hight;
    
    W25Q16_Wait();/*�ȴ���д���*/
}


/*************************************************
Function: W25Q16_Sector_Erase
Description: ������ַ��������
Input: addrΪ24λ��ַ
Output:��
Return: ��
Others: ��
*************************************************/
void W25Q16_Sector_Erase(uint32_t addr)
{
    /*����ַ���Ϊ�����ֽ�����*/
    uint8_t Addr[3] = {0};
    Addr[0] = (addr&0x00FF0000) >> 16;
    Addr[1] = (addr&0x0000FF00) >> 8;
    Addr[2] = (addr&0x000000FF) >> 0;
    
    W25Q16_CS_Low;/*����Ƭѡ����ʼ����*/
    W25Q16_Read_Write(0x20);
    W25Q16_Read_Write(Addr[0]);
    W25Q16_Read_Write(Addr[1]);
    W25Q16_Read_Write(Addr[2]);
    W25Q16_CS_Hight;/*����ֹͣ*/
 
    W25Q16_Wait();/*�ȴ���д���*/
   
    W25Q16_Write_Enable();/*�����������¿���дʹ��*/
}

/*************************************************
Function: W25Q16_Write_Byte
Description: ��ָ����ʼ��ַ֮��д�����ɸ�����
Input: addrΪָ����ַ
       datasendΪ�跢�͵�����
       numΪ���ݴ�С
Output:��
Return: ��
Others: �˴�Num���ֵΪ255
*************************************************/
void W25Q16_Write_Byte(uint32_t addr,uint8_t *datasend,uint8_t num)
{
     uint8_t Addr[3] = {0};
     uint8_t i;
    W25Q16_Write_Enable();
    /*����ַ���Ϊ��������*/
   
    Addr[0] = (addr&0x00FF0000) >> 16;
    Addr[1] = (addr&0x0000FF00) >> 8;
    Addr[2] = (addr&0x000000FF) >> 0;
    W25Q16_CS_Low;
    W25Q16_Read_Write(0x02);
    W25Q16_Read_Write(Addr[0]);
    W25Q16_Read_Write(Addr[1]);
    W25Q16_Read_Write(Addr[2]);
    if(num<256)/*w25q16��һ��Ƭѡ���͹����У���ഫ��256������*/
    {
        
        for(i = 0;i<num;i++)/*��������*/
        {
            W25Q16_Read_Write(datasend[i]);
        }
    }
    W25Q16_CS_Hight;
    
    /*�ȴ���д���*/
    W25Q16_Wait();
    
   
}

/*************************************************
Function: W25Q16_Read_Byte
Description: ��ȡָ����ַ֮�����ɸ��ֽ�����
Input: addrΪָ����ַ��numΪ���ȡ���ֽ���
Output: datastoΪ�洢���ݽ�����׵�ַ
Return: ��
Others: �� 
*************************************************/
void W25Q16_Read_Byte(uint32_t addr,uint8_t *datasto,uint8_t num)
{
    uint8_t i;
    /*����ַ���Ϊ��������*/
    uint8_t Addr[3] = {0};
    Addr[0] = (addr&0x00FF0000) >> 16;
    Addr[1] = (addr&0x0000FF00) >> 8;
    Addr[2] = (addr&0x000000FF) >> 0;
    W25Q16_CS_Low;
    W25Q16_Read_Write(0x03);
    W25Q16_Read_Write(Addr[0]);
    W25Q16_Read_Write(Addr[1]);
    W25Q16_Read_Write(Addr[2]);
    
    /*������ȡ*/
    for(i = 0;i<num;i++)
    {
        datasto[i] = W25Q16_Read_Write(0x00);
    }
    W25Q16_CS_Hight;
    /*�ȴ���д���*/
    W25Q16_Wait();
    
}


/*************************************************
Function: W25Q16_Wait
Description: �ж��Ƿ����ڶ�д,�����ڶ�д������ȴ�
Input: ��
Output:��
Return: ��
Others: ��
*************************************************/
static void W25Q16_Wait(void)
{
    uint8_t temp = 0;
    W25Q16_CS_Low;
    W25Q16_Read_Write(0x05);
    
    /*������ȡ״̬�Ĵ���1��ֵ*/
    do
    {
        temp = W25Q16_Read_Write(0x00);
    }
    while(temp&0x01==1); /*�ж�״̬�Ĵ������λ�����λΪ1��ʾæµ*/
    
    W25Q16_CS_Hight;
    
}

/*************************************************
Function: W25Q16_Read_Write
Description: ʹ��SPIЭ���w25q16���ж�д�������˺���ͬʱʵ�ֶ�ȡ��д��
Input: ��д�������
Output:��
Return: ��ȡ���
Others: ��
*************************************************/
static uint16_t W25Q16_Read_Write(uint16_t Data)
{
	uint16_t d;
	
	while(SPI_I2S_GetFlagStatus(W25Q16_SPI_Used, SPI_I2S_FLAG_TXE)==RESET);/*�ȴ��������ݼĴ���Ϊ��*/
	SPI_I2S_SendData(W25Q16_SPI_Used,Data);
	
	/*���������Ƿ������*/
	while(SPI_I2S_GetFlagStatus(W25Q16_SPI_Used, SPI_I2S_FLAG_RXNE)==RESET);
	
	/*���ݷ������ʱҲ���յ�����*/
	d = SPI_I2S_ReceiveData(W25Q16_SPI_Used);
	
	
	return d;
}


/*************************************************
Function: W25Q16_SPI_Conf
Description: ����W25Q16�õ���SPIͨ��ģʽ
Input: ��
Output:��
Return: ��
Others: ��
*************************************************/
void W25Q16_SPI_Conf(void)
{
	SPI_InitTypeDef SPI_Init_Struct;
	
	/*����GPIO*/
    W25Q16_GPIO_Conf();

	W25Q16_CS_Hight;/*Ƭѡ���ų�ʼ��Ϊ�ߵ�ƽ*/
    
	/*����SPIʱ��*/
	W25Q16_SPI_RCC_Cmd(W25Q16_RCC_SPI,ENABLE);
	
	/*����SPI����*/
	SPI_Init_Struct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;
	
	/*W25Q16֧��ģʽ0��ģʽ3���˴�����Ϊģʽ3*/
	SPI_Init_Struct.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_Init_Struct.SPI_CPOL = SPI_CPOL_High;
	
	SPI_Init_Struct.SPI_DataSize = SPI_DataSize_8b;
	SPI_Init_Struct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_Init_Struct.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_Init_Struct.SPI_Mode = SPI_Mode_Master;
	
	/*ѡ�����Ƭѡ*/
	SPI_Init_Struct.SPI_NSS = SPI_NSS_Soft;
	
	/*δʹ��CRCУ��ʱ���˴�������Ч*/
	SPI_Init_Struct.SPI_CRCPolynomial = 7;
    
	SPI_Init(W25Q16_SPI_Used,&SPI_Init_Struct);
	/*ʹ��SPI*/
	SPI_Cmd(W25Q16_SPI_Used,ENABLE);
    
    /*����дʹ��*/
    W25Q16_Write_Enable();
	
}






