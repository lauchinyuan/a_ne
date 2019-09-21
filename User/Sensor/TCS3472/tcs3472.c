#include "tcs3472.h"
#include "iic.h"
#include "stdio.h"
#include "tim.h"

/*************************************************
Function: TCS3472_Write_
Description: ��ָ����ַ�ļĴ�����д����
Input: addrΪ�Ĵ�����ַ,numΪд��8λ���ݵĸ���,dataΪ�����׵�ַ
Output:��
Return: ��
Others: ��
*************************************************/
void TCS3472_Write_(uint8_t *data,uint8_t num,uint8_t addr)
{
	uint8_t i;
	Start_Signal();
	I2C_Write_Byte(TCS3472_DEVICE_WRITE_ID);/*�����豸дָ��*/
	while(!Wait_Ask());/*�ȴ���Ӧ�ź�*/
	I2C_Write_Byte(addr|TCS3472_COMMAND_Bit);/*д��Ĵ���Ѱַָ��*/
	while(!Wait_Ask());
	for(i = 0;i < num;i++)
	{
		I2C_Write_Byte(data[i]);
		while(!Wait_Ask());
	}
	Stop_Signal();
	
}

/*************************************************
Function: TCS3472_Read_
Description: ��ȡָ���Ĵ����������
Input: addrΪ�Ĵ�����ַ,numΪ��ȡ8λ���ݵĸ���
Output:datastoΪ���ݽ���׵�ַ
Return: ��
Others: ��
*************************************************/
void TCS3472_Read_(uint8_t *datasto,uint8_t num,uint8_t addr)
{
	uint8_t i;
	Start_Signal();
	I2C_Write_Byte(TCS3472_DEVICE_WRITE_ID);/*�����豸дָ��*/   
	while(!Wait_Ask());
	I2C_Write_Byte(addr|TCS3472_COMMAND_Bit);/*д��Ĵ���Ѱַָ��*/
	while(!Wait_Ask());
	Start_Signal();/*�ڶ�����ʼ�ź�*/	
	
	I2C_Write_Byte(TCS3472_DEVICE_READ_ID);/*�����豸��ָ��*/
	while(!Wait_Ask());
	
	/*��������*/
	for(i=0;i<num;i++)
	{
		datasto[i] = I2C_Read_Byte();
		if(i==num - 1)
		{
			NAsk_Signal();
		}
		else
		{
			Ask_Signal();
		}
	}
	Stop_Signal();
}

/*************************************************
Function: TCS3472_Enable
Description: ʹTCS34725���������빤��ģʽ��AEN��
Input: ��
Output:��
Return: ��
Others: ��
*************************************************/
void TCS3472_Enable(void)
{
	/*�Ƚ���Idleģʽ*/
	uint8_t Command = TCS3472_ENABLE_PON;/*PON����*/
     
	TCS3472_Write_(&Command,1,TCS3472_ENABLE_REGISTER);/*������д���Ĵ���*/
	
	/*���빤��ģʽ���ҿ����ȴ�����*/
	Command = (TCS3472_ENABLE_PON|TCS3472_ENABLE_AEN|TCS3472_ENABLE_WEN);
    
	TCS3472_Write_(&Command,1,TCS3472_ENABLE_REGISTER);
    
	/*�˴���ʼ������Ҫ2.4����ĵȴ�ʱ�䣬�ʼ�����ʱ��������ʱ3����*/
    General_TIM_Delay_ms(3);
	
}

/*************************************************
Function: TCS3472_Set_WTIME
Description: �趨�ȴ�ʱ��WTIMEֵ
Input: wtimeΪ��Ĵ���д���ֵ
Output:��
Return: ��
Others: ��
*************************************************/
void TCS3472_Set_WTIME(uint8_t wtime)
{
	TCS3472_Write_(&wtime,1,TCS3472_WTIME_REGISTER);
}


/*************************************************
Function: TCS3472_Get_Conv_Status
Description: ��ȡ״̬�Ĵ������λ��ֵ��ȷ���Ƿ����ת��
Input: ��
Output:��
Return: ��ת����ɷ���1�����򷵻�0
Others: ��
*************************************************/
uint8_t TCS3472_Get_Conv_Status(void)
{
	uint8_t state = 0;/*ת��״̬*/	
	TCS3472_Read_(&state,1,TCS3472_STATUS_REGISTER);
	
	if((state&0x01) == 0x01)/*ת�����*/
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*************************************************
Function: TCS3472_Read_RGBData
Description: ��ȡRGB����ֵ���Ҷ�ȡ˳��ΪC->R->G->B
Input: ��
Output:datastoΪ���ڴ洢���ݵ�����ָ��
Return: ��
Others: ��
*************************************************/
void TCS3472_Read_RGBData(uint16_t* temp)
{
    uint8_t datasto[8] = {0};
    
	while(!TCS3472_Get_Conv_Status());/*�ȴ�ת�����*/

    TCS3472_Read_(datasto,8,TCS3472_CDATAL_REGISTER);/*һ�ζ�ȡ�˸��ֽ�*/
    
    /*���ݴ�����ԭʼ�������ת��ΪRGB����*/
    
    /*��ȡ16λC,R,G,Bֵ*/
    temp[0] = ((uint16_t)(datasto[1]<<8)|datasto[0]);       /*ʮ��λCԭʼ����*/
    temp[1] = ((uint16_t)(datasto[3]<<8)|datasto[2]);       /*ʮ��λRԭʼ����*/
    temp[2] = ((uint16_t)(datasto[5]<<8)|datasto[4]);       /*ʮ��λGԭʼ����*/
    temp[3] = ((uint16_t)(datasto[7]<<8)|datasto[6]);       /*ʮ��λBԭʼ����*/
    
}

/*************************************************
Function: TCS3472_White_Balance
Description: �Ի�ȡ����16λRGB���ݽ��а�ƽ�⴦��������ƽ��ת�����Ӵ洢��W25Q16��
Input: ��
Output:��
Return: ��
Others: ���ô˺���ʱ��ɫ������Ӧ���ڰ�ɫ������
*************************************************/
void TCS3472_White_Balance(void)
{
    float RGB_Factor[3] = {0};/*RGBУ׼����*/
    uint8_t i,j = 0;          
    uint16_t data[6][4] = {0};/*2ά����洢�ɼ�����*/
    uint32_t sum[3] = {0};     /*�ֱ�ΪRGB������ɫ���ݺ�*/

    LED1_ON();/*��1����ʾ��ʼת��*/
    
    for(i = 0;i<6;i++)/*�����ɼ��������*/
    {
        TCS3472_Read_RGBData(data[i]);
        General_TIM_Delay_ms(10);
    }
    /*�ֱ�������ɼ�RGBֵ��ƽ��ֵ*/
    
    for(i = 0;i<3;i++)/*����RGB��ɫ*/
    {
        for(j = 0;j<6;j++)/*����6������*/
        {
            sum[i]+=data[j][i+1];
        }
        sum[i] /= 6;/*��ƽ��ֵ*/
    }
    
    /*����У׼����*/
    RGB_Factor[0] = 255.0/sum[0];
    RGB_Factor[1] = 255.0/sum[1];
    RGB_Factor[2] = 255.0/sum[2];
    
    /*��ת�����Ӵ洢���ⲿFlash�У��Ա��������*/
    W25Q16_Sector_Erase(TCS3472_R_Factor);/*��������*/
    
    W25Q16_Write_Byte(TCS3472_R_Factor,(uint8_t*)RGB_Factor,12);/*ÿ��float�ͱ���ռ��4���ֽڿռ�*/
    
    LED_OFF();
    LED2_ON();/*��2����ʾת�����*/
    
}
/*************************************************
Function: TCS3472_Read_Deal
Description: ��ȡRGB16λԭʼ���ݲ������ⲿFlash�е�У׼���Ӵ�������
Input:  ��
Output: ��
Return: RGB888����
Others: �� 
*************************************************/
uint32_t TCS3472_Read_Deal(void)
{
    float kr = 0,kg = 0, kb = 0;/*RGBУ׼����*/
    uint32_t sum[3] = {0};
    uint8_t i,j;
    uint16_t data[6][4] = {0};/*���ݻ�������*/
    uint32_t result = 0;/*������*/
    W25Q16_Read_Byte(TCS3472_R_Factor,(uint8_t*)&kr,4);/*���ⲿFlash�ж�ȡ����*/
    W25Q16_Read_Byte(TCS3472_G_Factor,(uint8_t*)&kg,4);
    W25Q16_Read_Byte(TCS3472_B_Factor,(uint8_t*)&kb,4);
    
    for(i = 0;i<6;i++)/*�����ɼ��������,�ɼ����ݴ������ƽ��У׼ʱһ��*/
    {
        TCS3472_Read_RGBData(data[i]);
        General_TIM_Delay_ms(10);
    }
    /*�ֱ�������ɼ�RGBֵ��ƽ��ֵ*/
    for(i = 0;i<3;i++)
    {
        for(j = 0;j<6;j++)
        {
            sum[i]+=data[j][i+1];
        }
        sum[i] /= 6;
    }
    
    /*�������ս��*/
    result |= (uint8_t)(sum[0]*kr);
    result<<=8;
    result |= (uint8_t)(sum[1]*kg);
    result<<=8;
    result |= (uint8_t)(sum[2]*kb);
   return  result;
}


/*************************************************
Function: TCS3472_Init
Description: TCS3472��ʼ��
Input: ��
Output:��
Return: ��
Others: ��
*************************************************/
void TCS3472_Init(void)
{
	/*���Ὺ���ȴ�ģʽ(WEN)�������õȴ�ʱ��Ĵ�����ֵ*/
	TCS3472_Set_WTIME(WTIME_Used);
    
	/*��������ת��ʱ��*/
	TCS3472_Set_ATIME(ATIME_Used);
    
    /*��������*/
    TCS3472_Set_AGAIN(AGAIN_Used);
    
	/*ʹ��TCS3472������AEN*/
	TCS3472_Enable();
	
}


/*************************************************
Function: TCS3472_Set_ATIME
Description: �����ڲ�����ʱ�䣬��ֵ�������ɼ�ֵ�����ֵ
Input: atimeΪ��Ĵ���д���ֵ
Output:��
Return: ��
Others: ��
*************************************************/
void TCS3472_Set_ATIME(uint8_t atime)
{
	TCS3472_Write_(&atime,1,TCS3472_RGBC_TIMING_REGISTER);
}


/*************************************************
Function: TCS3472_Set_AGAIN
Description: �������棬��ֵ�������ɼ�ֵ�����ֵ
Input: atimeΪ��Ĵ���д���ֵ
Output:��
Return: ��
Others: ��
*************************************************/
void TCS3472_Set_AGAIN(uint8_t again)
{
	TCS3472_Write_(&again,1,TCS3472_CONTROL_REGISTER);
}


