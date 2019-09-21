#include "iic.h"
#include "tim.h"

/*************************************************
Function: IIC_CONF
Description: ����IIC
Input: ��
Output:��
Return: ��
Others: ��
*************************************************/
void IIC_CONF(void)
{
	GPIO_InitTypeDef GPIOInit_Struct;
	RCC_AHB1PeriphClockCmd(GPIO_CLOCK,ENABLE);
	
	/*����GPIOģ��SDA��*/
	GPIOInit_Struct.GPIO_Mode = GPIO_Mode_OUT;
	GPIOInit_Struct.GPIO_OType = GPIO_OType_PP;
	GPIOInit_Struct.GPIO_Pin = I2C_SDA_GPIO_Pin;
	GPIOInit_Struct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIOInit_Struct.GPIO_Speed = GPIO_Fast_Speed;
	GPIO_Init(I2C_SDA_GPIOPort,&GPIOInit_Struct);
	/*����GPIOģ��SCL��*/
	GPIOInit_Struct.GPIO_Mode = GPIO_Mode_OUT;
	GPIOInit_Struct.GPIO_OType = GPIO_OType_PP;
	GPIOInit_Struct.GPIO_Pin = I2C_SCL_GPIO_Pin;
	GPIOInit_Struct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIOInit_Struct.GPIO_Speed = GPIO_Fast_Speed;
	GPIO_Init(I2C_SCL_GPIOPort,&GPIOInit_Struct);
	
    General_TIM_Delay_ms(10);
    
	/*��ʼ״̬*/
    I2C_SDA_1();
	I2C_SCL_1();
}

/*************************************************
Function: Wait_Ask
Description: �ȴ��ӻ�Ӧ���ź�
Input: ��
Output:��
Return: ����ֵΪ0ʱ��δ�յ�Ӧ���źţ�����ֵΪ1ʱ���յ�Ӧ���ź�
Others: ��
*************************************************/
uint8_t Wait_Ask(void)
{
    uint8_t state = 0;
    
    I2C_SDA_IN();

    /*ȷ��SDA����SCL�͵�ƽ�����仯*/
    I2C_SCL_0();
	i2c_Delay();
    
	/*��SDA��Ϊ�ߵ�ƽ,CPU�ͷ�SDA����*/
	I2C_SDA_1();
	i2c_Delay();
	/*����ʱ��*/
	I2C_SCL_1();
	i2c_Delay();
	if(SDA_Vaule==0)
	{
		state = 1;
	}
	I2C_SCL_0();
	i2c_Long_Delay();
	return state;
}

/*************************************************
Function: Start_Signal
Description: ģ��IICЭ�����ʼ�ź�
Input: ��
Output:��
Return: ��
Others: ��
*************************************************/
void Start_Signal(void)
{
    
    I2C_SDA_OUT();

	/*��SDA��SCL��Ϊ�ߵ�ƽ*/
	I2C_SDA_1();
	i2c_Delay();
	I2C_SCL_1();
	i2c_Delay();
	/* SDA���������ر�ʾI2C���������ź� */
	I2C_SDA_0();
	i2c_Delay();
	
	I2C_SCL_0();
	i2c_Delay();
	
}

/*************************************************
Function: Stop_Signal
Description: ģ��IICЭ�����ֹ�ź�
Input: ��
Output:��
Return: ��
Others: ��
*************************************************/
void Stop_Signal(void)
{
    I2C_SDA_OUT();
    
    /*ȷ��SDA����SCL�͵�ƽ�����仯*/
    I2C_SCL_0();
	i2c_Delay();
    
	/*��ʼ����*/
	I2C_SDA_0();
	i2c_Delay();
	I2C_SCL_1();
	i2c_Delay();
	/* SDA���������ر�ʾI2C����ֹͣ�ź� */
	I2C_SDA_1();
	i2c_Delay();
	
	
}

/*************************************************
Function: Ask_Signal
Description: ����ģ��IICЭ��Ӧ��
Input: ��
Output:��
Return: ��
Others: ��
*************************************************/
void Ask_Signal(void)
{
    I2C_SDA_OUT();
    
    /*ȷ��SDA����SCL�͵�ƽ�����仯*/
    I2C_SCL_0();
	i2c_Delay();
	
	I2C_SDA_0();
	i2c_Delay();
	I2C_SCL_1();/* CPU����1��ʱ������ */
	i2c_Delay();
	I2C_SCL_0();
	i2c_Delay();
    
	I2C_SDA_1();/* CPU�ͷ�SDA���� */
	i2c_Delay();
}


/*************************************************
Function: NAsk_Signal
Description: ����ģ��IICЭ���Ӧ��
Input: ��
Output:��
Return: ��
Others: ��
*************************************************/
void NAsk_Signal(void)
{
    I2C_SDA_OUT();
    
    /*ȷ��SDA����SCL�͵�ƽ�����仯*/
    I2C_SCL_0();
	i2c_Delay();
	
    
	I2C_SDA_1();
	i2c_Delay();
	I2C_SCL_1();/* CPU����1��ʱ������ */
	i2c_Delay();
	I2C_SCL_0();
	i2c_Delay();
                    
                   
}


/*************************************************
Function: I2C_Read_Byte
Description: ģ��IICЭ���ȡһ���ֽ�����
Input: ��
Output:��
Return: ���ݽ��
Others: ��
*************************************************/
uint8_t I2C_Read_Byte(void)
{
	uint8_t i;
	uint8_t temp = 0;
    
    I2C_SDA_IN();
    
    /*ȷ��SDA����SCL�͵�ƽ�����仯*/
    I2C_SCL_0();
	i2c_Long_Delay();
	
	
	for(i = 0;i<8;i++)
	{
		temp<<=1;
		I2C_SCL_1();/* CPU����1��ʱ������ */
		i2c_Long_Delay();
		
		if(SDA_Vaule!=0)
		{
			temp|=0x01;
		}
		I2C_SCL_0();
		i2c_Long_Delay();
	}
	
	
	return temp;

}


/*************************************************
Function: I2C_Write_Byte
Description: ģ��IICЭ�鷢��һ���ֽ�����
Input: �跢�͵�����
Output:��
Return: ��
Others: ��
*************************************************/
void I2C_Write_Byte(uint8_t data)
{    
	uint8_t i;
    
    I2C_SDA_OUT();
    
	I2C_SCL_0();
	i2c_Delay();
	 
	for(i = 0;i<8;i++)
	{
		if((data&0x80)!=0)
		{
			I2C_SDA_1();
		}
		else
		{
			I2C_SDA_0();
		}
		i2c_Delay();
		
		I2C_SCL_1();	/* CPU����1��ʱ�� */
		i2c_Delay();
		I2C_SCL_0();
		i2c_Delay();	
				
		data<<= 1;
		if(i==7)
		{
			I2C_SDA_1();/*�ͷ�����*/
			i2c_Delay();
		}
	}
	
}



/*************************************************
Function: i2c_Delay
Description: �򵥵�IIc��ʱ����
Input: ��
Output:��
Return: ��
Others: ��
*************************************************/
void i2c_Delay(void)
{
    /*180ΪDHT12�¶ȴ����������ʵ�����õý�Ϊ�ɿ���ֵ��
    ��ֵƫ��ʱ���ݲɼ�У����ڴ���������ʱ��ϳ�ʱ����ƫ��ʱӰ���������*/
	uint16_t i;
	for (i = 0; i < 10; i++);
}


/*************************************************
Function: i2c_Long_Delay
Description: �򵥵�IIc��ʱ����ʱ����
Input: ��
Output:��
Return: ��
Others: �˴���Ҫ��Ϊ�˱���DHT12������������Ӧ
*************************************************/
void i2c_Long_Delay(void)
{
    uint8_t i;
    for(i = 0;i<18;i++)
    {
        i2c_Delay();
    }
}



/*************************************************
Function: I2C_SDA_IN
Description: ����SDAΪ����ģʽ������ת��SDAģʽ
Input: ��
Output:��
Return: ��
Others: ��
*************************************************/
void I2C_SDA_IN(void)
{
   GPIO_InitTypeDef  GPIO_InitStructure;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
   GPIO_InitStructure.GPIO_Pin = I2C_SDA_GPIO_Pin;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed; 
   GPIO_Init(I2C_SDA_GPIOPort, &GPIO_InitStructure);	
}
 


/*************************************************
Function: I2C_SDA_OUT
Description: ����SDAΪ���ģʽ������ת��SDAģʽ
Input: ��
Output:��
Return: ��
Others: ��
*************************************************/
void I2C_SDA_OUT(void)
{
    GPIO_InitTypeDef GPIOInit_Struct;
    GPIOInit_Struct.GPIO_Mode = GPIO_Mode_OUT;
	GPIOInit_Struct.GPIO_OType = GPIO_OType_PP;
	GPIOInit_Struct.GPIO_Pin = I2C_SDA_GPIO_Pin;
	GPIOInit_Struct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIOInit_Struct.GPIO_Speed = GPIO_Fast_Speed;
	GPIO_Init(I2C_SDA_GPIOPort,&GPIOInit_Struct);	
}

