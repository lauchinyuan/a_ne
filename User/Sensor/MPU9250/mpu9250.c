#include "mpu9250.h"
#include "led.h"
#include "math.h"
#include "inoutput.h"

/*************************************************
Function: MPU9250_Init
Description: MPU9250��ʼ��
Input: ��
Output:��
Return: ��
Others: ��
*************************************************/
void MPU9250_Init(void)
{
    MPU9250_Write_Byte(MPU9250_PWR_MNG_REG,0x00);/*����MPU9250*/
    MPU9250_Write_Byte(MPU9250_SMPLRT_DIV_REG,0x07); /*���ò������ʷ�Ƶ���˴�Ϊ8��Ƶ*/
    MPU9250_Write_Byte(MPU9250_ACC_CONF2_REG,0x06); /*�����˲���*/
    MPU9250_Write_Byte(MPU9250_CONF_REG,0x06);
    MPU9250_Write_Byte(MPU9250_ACC_CONF1_REG,0x00);/*���ü��ٶȼ�����Ϊ+-2g*/
}

/*************************************************
Function: MPU9250_Write_Byte
Description: �ӼĴ�����ʼ��ַ��ʼд��num���ֽ�����
Input: AddrΪָ����ַ��dataΪ���ֽ������׵�ַ��numΪ�����ֽ���
Output:��
Return: ��
Others: ��
*************************************************/
void MPU9250_Write(uint8_t Addr,uint8_t* data,uint8_t num)
{
    uint8_t i;
	Start_Signal();
	I2C_Write_Byte(MPU9250_WRITE_ADDR);/*�����豸дָ��*/
    
	while(!Wait_Ask());/*�ȴ���Ӧ�ź�*/
    LED2_ON();
	I2C_Write_Byte(Addr);/*д��Ĵ���Ѱַָ��*/
	while(!Wait_Ask());
	for(i = 0;i < num;i++)
	{
		I2C_Write_Byte(data[i]);
		while(!Wait_Ask());
	}
	Stop_Signal();
}


/*************************************************
Function: MPU9250_Write_Byte
Description: �ӼĴ�����ʼ��ַ��ʼд�뵥���ֽ�����
Input: AddrΪָ����ַ��dataΪ���ֽ�����
Output:��
Return: ��
Others: ��
*************************************************/
void MPU9250_Write_Byte(uint8_t Addr,uint8_t data)
{
    
	MPU9250_Write(Addr,&data,1);
    
}

/*************************************************
Function: MPU9250_Read
Description: �ӼĴ�����ʼ��ַ��ʼ������ȡnum���ֽ�����
Input: AddrΪ�Ĵ�����ʼ��ַ��numΪҪ��ȡ���ֽ���
Output:��ȡ����洢��datasto������
Return: ��
Others: ��
*************************************************/
void MPU9250_Read(uint8_t Addr,uint8_t *datasto,uint8_t num )
{
    uint8_t i;
	Start_Signal();
    
	I2C_Write_Byte(MPU9250_WRITE_ADDR);/*�����豸дָ��*/   
	while(!Wait_Ask());
    
	I2C_Write_Byte(Addr);/*д��Ĵ���Ѱַָ��*/
	while(!Wait_Ask());
    
	Start_Signal();/*�ڶ�����ʼ�ź�*/	
	
	I2C_Write_Byte(MPU9250_READ_ADDR);/*�����豸��ָ��*/
	while(!Wait_Ask());
	
	/*��������*/
	for(i=0;i<num;i++)
	{
		datasto[i] = I2C_Read_Byte();
		if(i==num - 1)/*���һλ���ͷ�Ӧ���ź�*/
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
Function: MPU9250_Cal_Accel
Description: ��ȡ��������ٶȼ����ݣ���8λԭʼ����ת��Ϊ16λ���ݣ�
Input: ��
Output:��
Return: ����16λ���ٶȼ�����
Others: ��
*************************************************/
int16_t MPU9250_Cal_Accel(void)
{
    int16_t dataout = 0;
    
    uint8_t data[2] = {0};
    
    /*�ֱ��ȡ�ߵ�8λ����*/
    MPU9250_Read(MPU9250_ACCEL_YOUT_H,data,2);
    
    /*ƴ�ӳ�16λ����*/
    dataout = (((uint16_t)(data[0]<<8))|data[1]);
    return dataout;
}

/*************************************************
Function: MPU9250_Offset
Description: �Լ��ٶȼ������ֵ������������������ֵ�洢���ⲿFlash��
Input: ��
Output:��
Return: ��
Others: ���ô˺���ʱӦȷ��������ƽ�ţ��ұ��־�ֹ
*************************************************/
void MPU9250_Offset(void)
{
    int16_t Accel_Y_Offset = -30000;/*����У׼��ֵ����ֵ��-30000��ʼ������ֱ������(MPUdata+Accel_Y_Offset)=0*/    
    int16_t MPUdata = 0;/*MPU9250ԭʼ16λ����*/
    MPUdata = MPU9250_Cal_Accel();/*��ȡԭʼֵ*/
    while((MPUdata+Accel_Y_Offset)!=0)/*У�����ٶȼ�Y��*/
    {
        Accel_Y_Offset++;/*�������������Լ�*/
        if(Accel_Y_Offset>30000)/*����У׼��Χ*/
        {
            printf("���ٶ�У��ʧ��\n");
            break;
        }
    }
    
    /*��У�����Ӵ洢���ⲿFlash�У��Ա����*/
    W25Q16_Sector_Erase(MPU9250_ACC_YOFFSET_ARRD);/*��������*/
    
    /*����ÿ��ֵռ2���ֽڿռ�*/
    W25Q16_Write_Byte(MPU9250_ACC_YOFFSET_ARRD,(uint8_t*)&Accel_Y_Offset,2); 
    
}


/*************************************************
Function: MPU9250_Get_Angle
Description: �򵥼����������ٶȼн�(�Ƕ�)
Input: ��
Output: dataΪ�洢�Ƕȱ����Ľṹ���׵�ַ
Return: ��
Others: �� 
*************************************************/
void MPU9250_Get_Angle(MPU9250_Angle *data)
{  
    int16_t MPUdata = 0;
    int16_t MPUAccl_Y_Offset = 0;/*У��ֵ*/

    W25Q16_Read_Byte(MPU9250_ACC_YOFFSET_ARRD,(uint8_t*)&MPUAccl_Y_Offset,2);/*��ȡУ��ֵ*/

    MPUdata = MPU9250_filter();/*ͨ���˲���ȡ16λ����*/
    
    /* ������Ǻ������ü��ٶȼ���x, y, z ����ǣ��õ�����ֵ*/
    data->Angle_Y = asin((MPUdata + MPUAccl_Y_Offset) / 16384.0);
    
    data->Angle_Y  *=  DEG_to_RAD;/* ����ֵת��Ϊ�Ƕ�ֵ */
} 


/*************************************************
Function: MPU9250_filter
Description: ��ԭʼ���ݽ��л����˲�����
Input: ��
Output: ��
Return: �˲����������ݣ���ǰ�˲�����ƽ��ֵ��
Others: �˺���ǰN�����ֵ��׼ȷ 
*************************************************/
#define N 9/*�궨��*/
int16_t value_buf[N]; 
extern uint8_t q = 0;
int16_t MPU9250_filter(void)
{
     uint8_t count = 0;
     int32_t sum=0;  
     int16_t temp=0;
     value_buf[q++] = MPU9250_Cal_Accel();/*�����ֵ*/
    if (q == N) /*������Χ���������е�һ���������¸�ֵ*/
    {
         q = 0;
    }
    for (count=0;count<N;count++)
    {
        sum += value_buf[count];/*��ǰ�˲������ܺ�*/
    }
    temp=(int16_t)(sum/N);/*���㵱ǰ����ƽ��ֵ*/
    return temp;/*���ص�ǰ����ƽ��ֵ*/
}
#undef N/*ȡ���궨��*/
