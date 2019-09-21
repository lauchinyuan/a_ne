#include "tsc2046.h"
extern uint8_t Clock_Print_Model;/*����ʱ�����ʱ�л�����*/
extern uint8_t Print_Model;
/*************************************************
Function: TSC2046_SoftSPI_GPIO_Conf
Description: ���ģ��SPI������������
Input: ��
Output:��
Return: ��
Others: ��
*************************************************/
void TSC2046_SoftSPI_GPIO_Conf(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    /*����GPIOʱ��*/
    RCC_AHB1PeriphClockCmd(TSC2046_RCC_CLOCK,ENABLE);
    
     /*����ģ��MISO��*/
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Pin = TSC2046_MISO_Pin;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(TSC2046_MISO_Port, &GPIO_InitStruct);
    
     /*����Pen*/
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Pin = TSC2046_PEN_Pin;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(TSC2046_PEN_Port, &GPIO_InitStruct);
    
    /*����ģ��SCK��*/
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = TSC2046_SCK_Pin;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(TSC2046_SCK_Port, &GPIO_InitStruct);
    
    /*����ģ��MOSI��*/
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = TSC2046_MOSI_Pin;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(TSC2046_MOSI_Port, &GPIO_InitStruct);
    
    /*����ģ��CS��*/
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = TSC2046_CS_Pin;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(TSC2046_CS_Port, &GPIO_InitStruct);
    
}


/*************************************************
Function: TSC2046_Ave_Value
Description: ͨ��ģ��SPIʱ����TSC2046����һ���ֽ���������,����ȡ12λADCת�����ֵ
Input: dataΪ�����͵�����
Output:��
Return: 12λADCת�����ֵ
Others: ��
*************************************************/
uint16_t TSC2046_Write_Read(uint8_t data)
{
    uint8_t i = 0;
    uint16_t Read_Data = 0;
    
     /*Ĭ�ϵ�ƽ*/
    TCS_2046_SCK_Low;
    TSC2046_DelayUS (5);
    
    /*����Ƭѡ����*/
    TCS_2046_CS_Low;
    TSC2046_DelayUS (5);
    
    /*��λ��������*/
    for(i = 0;i<8;i++)
    {
        /*�����λΪ1*/
        if((data&0x80)==0x80)
        {
           TCS_2046_MOSI_Hight;
        }
        else
        {
            TCS_2046_MOSI_Low;
            
        }
        TSC2046_DelayUS (5);
        
        /*����SCK��ƽ�������أ�����ʱ�ӻ����һλ����*/
        TCS_2046_SCK_Hight;
        TSC2046_DelayUS (5);
        
        TCS_2046_SCK_Low;
        TSC2046_DelayUS (5);
        
        data<<=1;
    }
    
    /*����ʱ��ͼ��Ҫ��BUSY�ź���һ��ʱ�����ں󣬴ӻ��Żᷢ������*/
     TCS_2046_SCK_Hight;
     TSC2046_DelayUS (5);
        
     TCS_2046_SCK_Low;
     TSC2046_DelayUS (5);
    
    /*��λ�������ݣ��м�Ƭѡ��������*/
    
    for(i = 0;i<12;i++)
    {
        Read_Data<<=1;
        
        /*�����أ�ʹ�ӻ��ȷ�������*/
        TCS_2046_SCK_Hight;
        TSC2046_DelayUS (5);
        
        /*��ȡ����λ*/
        if(TCS_2046_MISO_Hight)
        {
            Read_Data|=0x01;
        }
        
        else
        {
             Read_Data|=0x00;
        }
        TSC2046_DelayUS (5);
        
        TCS_2046_SCK_Low;
        TSC2046_DelayUS (5);
        
        
    }
    
    /*��ȫʣ��ʱ���ź�*/
    for(i = 0;i<4;i++)
    {
        TCS_2046_SCK_Hight;
        TSC2046_DelayUS (5);
        
        TCS_2046_SCK_Low;
        TSC2046_DelayUS (5);
    }
    
    
   return Read_Data; 
}
/*************************************************
Function: TSC2046_DelayUS
Description: ����TSC2046�ļ�΢���ʱ����
Input: ulCountΪ��ʱ������
Output:��
Return: ��
Others: ��
*************************************************/
static void TSC2046_DelayUS (uint32_t ulCount )
{
	uint32_t i;
	for ( i = 0; i < ulCount; i ++ )
	{  
		uint8_t uc = 12;/*����ֵΪ12����Լ��1΢��*/   
		while ( uc -- );    
	}
	
}

/*************************************************
Function: TSC2046_Ave_Value
Description: �����ɼ����ADC�������ݣ�ȥ�������Сֵ����ƽ��ֵ
Input: Cmd�����SPiͨ��Э�飬��ʵ������
Output:��
Return: ƽ�����
Others: ��
*************************************************/
uint16_t TSC2046_Ave_Value(uint8_t Cmd)
{
    uint8_t i;
    uint16_t soult = 0;
    uint32_t sum  = 0;
    uint16_t max = 0,min = 0;
    uint16_t data[15] = {0};
 
    /*��¼����������*/
    for(i = 0;i<15;i++)
    {
        /*�ɼ�12��X����*/
        data[i]=TSC2046_Write_Read(Cmd);
    }
    if(i==15)
    {
        /*����12�βɼ�*/
        /*�ж������Сֵ���޳�*/
        for(i = 0;i<15;i++)
        {
            if(max<data[i])
            {
                max = data[i];
            }
            if(min>data[i])
            {
                min = data[i];
            }
            
            sum+=data[i];
        
        }
        
        /*����ƽ��ֵ*/
        soult = ((sum-max-min)/13);  
       
       
    }
    
    else
        {
            /*��δ�����������������ʾ����ʧ��*/
             ILI9341_Print_Str(200,0,"����ʱ�䲻�㣬���´���");
            
        }
    
    
     return soult;
}


/*************************************************
Function: TSC2046_Calibration
Description: ����������Һ����ʾ������У׼,�˴�ʹ��5��У׼��,�˷�����һ�����
Input: ��
Output:��
Return: ��
Others: �ο������еļ��㷽�� https://blog.csdn.net/yangseng1987/article/details/20780379
*************************************************/
void TSC2046_Calibration(void)
{
    /*�������������*/
    uint16_t Drew_X[5] = {90,270,270,90,180};
    uint16_t Drew_Y[5] = {160,160,80,80,120};
    
    uint16_t Logic_X[5] = {0},Logic_Y[5] = {0};/*�������ڴ洢�߼�ֵ������*/
     
    uint8_t i = 0;/*��i���д�������ͳ��*/
    
    uint8_t Drew_flag = 0;/*�����־����־Ϊ0ʱ�������*/
    
    float kx = 0,ky = 0;/*��������У��ϵ��ֵ*/
    
    /*��Whileѭ���вɼ���������*/
    while(i<5)
    {
        /*�������ʾ��Ϊ��ֹ�ظ����û�����㺯��ռ����Դ���˴���һ��־Dreew_flag*/
        if(Drew_flag == 0)
        {
            Drew_flag = 1;
            ILI9431_Drew_Cross(Drew_X[i],Drew_Y[i],BLUE); 
        }
        
        if(TCS_2046_PEN_Low)/*��⵽����*/
        {
            /*��⵽�������¼ADCת�����õ��߼�ֵ*/
            Logic_Y[i] = TSC2046_Ave_Value(TCS_2046_Cmd_Read_Y_Pos);
            Logic_X[i] = TSC2046_Ave_Value(TCS_2046_Cmd_Read_X_Pos);
            
            /*��ʱ����ֹi�������*/
            General_TIM_Delay_ms(500);
            
            /*���ݲɼ��꣬�����һ�����*/
            ILI9431_Clean_Cross(Drew_X[i],Drew_Y[i]);
            
            /*������һ����*/
            /*Dreew_flag������0��ʹ��Ļ���Ի���*/
            Drew_flag = 0;
             
            i++;
        }
    }
    
    /*����Whileѭ����ʾ�߼����ݼ�¼���*/
    
    /*����ϵ��*/
    kx = (float)(((float)(Logic_X[1] - Logic_X[0])/(float)(Drew_X[1] - Drew_X[0]))+((float)(Logic_X[2] - Logic_X[3])/(float)(Drew_X[2] - Drew_X[3])))/2;
    ky = (float)(((float)(Logic_Y[2] - Logic_Y[1])/(float)(Drew_Y[2] - Drew_Y[1]))+((float)(Logic_Y[2] - Logic_Y[1])/(float)(Drew_Y[2] - Drew_Y[1])))/2;
    
    /*������ϵ��������У׼�����ݴ洢���ⲿFlash�У��˴�����洢˳��Ϊkx->ky->���ĵ��߼�Xֵ->���ĵ��߼�Yֵ*/
    
    /*��������*/
    W25Q16_Sector_Erase(TCS_2046_Sec_Addr);
    
    /*float�ͱ���ռ��4���ֽڿռ�,ADCת������ֵռ2���ֽڿռ�*/
    
    /*���д������ֵ*/
    W25Q16_Write_Byte(TCS_2046_kx_Addr,(uint8_t*)&kx,4);
    W25Q16_Write_Byte(TCS_2046_ky_Addr,(uint8_t*)&ky,4);
    W25Q16_Write_Byte(TCS_2046_Cen_Logic_X_Addr,(uint8_t*)&Logic_X[4],2);
    W25Q16_Write_Byte(TCS_2046_Cen_Logic_Y_Addr,(uint8_t*)&Logic_Y[4],2);
    
}

/*************************************************
Function: TSC2046_Calculate_XY
Description: �����������㲢�洢��ָ��������
Input: ��
Output:datasto��Ϊ���ս����������
Return: ��
Others: ��
*************************************************/
void TSC2046_Calculate_XY(uint16_t *datasto)
{
    float kx = 0,ky = 0;
    uint16_t logic_X = 0,logic_Y = 0;
    uint16_t Current_Logicx = 0,Current_Logicy = 0;
    
    /*���ȶ�ȡ�洢���ⲿFlash�е�У׼����*/
    W25Q16_Read_Byte(TCS_2046_kx_Addr,(uint8_t*)&kx,4);
    W25Q16_Read_Byte(TCS_2046_ky_Addr,(uint8_t*)&ky,4);
    W25Q16_Read_Byte(TCS_2046_Cen_Logic_X_Addr,(uint8_t*)&logic_X,2);
    W25Q16_Read_Byte(TCS_2046_Cen_Logic_Y_Addr,(uint8_t*)&logic_Y,2);
    
    /*��ȡʵʱ����ADCת��ֵ*/
    Current_Logicx = TSC2046_Ave_Value(TCS_2046_Cmd_Read_X_Pos);
    
    
    Current_Logicy = TSC2046_Ave_Value(TCS_2046_Cmd_Read_Y_Pos);
     
    /*����У׼ԭ��Ĺ�ʽ������������*/
    
    /* X = ( XL - XLC ) / KX + XC 
       Y = ( YL - YLC ) / KY + YC*/
    
    datasto[0] = ((uint16_t)(((Current_Logicx - logic_X)/kx)+180));
    
    
    datasto[1] = (uint16_t)(((Current_Logicy - logic_Y)/ky)+120);
    
    /*�������*/
    
}
/*************************************************
Function: TSC2046_Applic
Description: ��ϴ�������д��Ӧ�ó��򣬴˴������жϴ���λ�ã���������Ӧֵ
Input: ����λ�ã�����postion[1]Ϊ��������X��ֵ��postion[2]Ϊ��������Y��ֵ
Output:��
Return: ����1�������������л�����
        ����2����������Ļ�����л�����
        ����3��ʾ����ʱ��
        ����4��ʾ��������
        ����5���������ϣ���ʱ��������ϣ�
        ����6����Сʱ�ϵ�
        ����7����Сʱ�µ�
        ����8��������ϵ�
        ����9��������µ�
        ����10��������ϵ�
        ����11��������µ�
        ����12�����·��ϵ�
        ����13�����·��µ�
        ����14���������ϵ�
        ����15���������µ�
Others: ��
*************************************************/
uint8_t TSC2046_Applic(uint16_t *postion)
{  
    uint8_t state = 0; 
    
/************���κ�Print_Modle�£�ֻҪ�������ڵ���ʱ�䣬��Ҫ�ж��Ƿ������л�����****************/
    
        if((postion[0]>250-TCS_2046_Calibration_Error)&&(postion[0]<300+TCS_2046_Calibration_Error))
        {
            /*��Ļ����������X�᷶Χ��ͬ����Ϊ250-300���˴������������ֵ*/
            
            /*�жϴ���Y�����Ƿ�Ҳ����ָ������*/
            if(postion[1]<(64+TCS_2046_Calibration_Error))
            {
                /*��ʾ���������������*/
                
                state = 1;
            }
            
             if(postion[1]>(176-TCS_2046_Calibration_Error))
            {
                /*��ʾ���������ұ�����*/
                
                state = 2;
            }
        }
        
/**********************����ʱ��������棨Print_Model==5���ж����´���**************************/
        if(Print_Model==5)
        {
            if(Clock_Print_Model==0)/*��ʱ������ĳ�ʼ���棬�ж��Ƿ��µ�������*/
            {
                /*�ڳ�ʼ�����е���˵�������*/
                 if((postion[0]>160-TCS_2046_Calibration_Error)&&(postion[0]<200+TCS_2046_Calibration_Error))
                {
                
                
                    /*�жϴ���Y�����Ƿ�Ҳ����ָ������*/
                    if(postion[1]<(64+TCS_2046_Calibration_Error))
                    {
                        /*��ʾ���������������*/   
                        state = 3; /*��ʾҪ����ʱ��*/
                    }
                
                     else if(postion[1]>(176-TCS_2046_Calibration_Error))
                    {
                        /*��ʾ���������ұ�����*/
                        state = 4;/*��ʾҪ��������*/
                        
                    }
               }
            }
            
            
            
            
            
/*��ʱ�ӵ��������У��ж�Сʱ����ӵ��������µ��������Ƿ񴥼�*/
            else if(Clock_Print_Model==1)
            {
                
                if((postion[0]>64-TCS_2046_Calibration_Error)&&(postion[0]<96+TCS_2046_Calibration_Error))
                {
                
                
                    /*�жϴ���Y�����Ƿ�Ҳ����ָ������*/
                    if(postion[1]<(32+TCS_2046_Calibration_Error))
                    {
                        /*��ʾ���������������*/   
                        state = 6; /*��ʾСʱ���ϵ���*/
                    }
                
                     else if(postion[1]>(192-TCS_2046_Calibration_Error))
                    {
                        /*��ʾ���������ұ�����*/
                        state = 8;/*��ʾ����ֵ���ϵ���*/
                        
                    }
                    
                    
               }
                
               else if((postion[0]>144-TCS_2046_Calibration_Error)&&(postion[0]<176+TCS_2046_Calibration_Error))
                {
                
                
                    /*�жϴ���Y�����Ƿ�Ҳ����ָ������*/
                    if(postion[1]<(32+TCS_2046_Calibration_Error))
                    {
                        /*��ʾ���������������*/   
                        state = 7; /*��ʾСʱ���µ���*/
                    }
                
                     else if(postion[1]>(192-TCS_2046_Calibration_Error))
                    {
                        /*��ʾ���������ұ�����*/
                        state = 9;/*��ʾ����ֵ���µ���*/
                        
                    }
                    
                    
               }
                
               /*�ж��Ƿ���ʱ�ӽ��水��ȷ�ϼ�*/
               if((postion[0]>200-TCS_2046_Calibration_Error)&&(postion[0]<240+TCS_2046_Calibration_Error))/*X��Χһ��*/
               {
                   if((postion[1]>90-TCS_2046_Calibration_Error)&&(postion[1]<150+TCS_2046_Calibration_Error))/*Y��Χһ�£�ȷ�ϰ���ȷ�ϼ�*/
                   {
                       state = 5;
                   }
               }
                
                
            }
            
/*�����ڵ��������У��ж����������µ��������Ƿ񴥼�*/            
            else if(Clock_Print_Model==2)
            {
                
                /*X�����������ϵ������λ��*/
                if((postion[0]>64-TCS_2046_Calibration_Error)&&(postion[0]<96+TCS_2046_Calibration_Error))
                {
                
                
                    /*�жϴ���Y�����Ƿ�Ҳ����ָ������*/
                    if(postion[1]<(25+TCS_2046_Calibration_Error))
                    {
                        /*��ʾ����������������飬��ʾ������ϵ���*/   
                        state = 10; /*��ʾ������ϵ���*/
                    }
                    
                    /*���ڴ������ҵڶ�����*/
                    else if(postion[1]>(64+TCS_2046_Calibration_Error)&&postion[1]<(64+32+TCS_2046_Calibration_Error))
                    {
                        state = 12;/*��ʾ�·����ϵ���*/
                    }
                    /*���ڴ������ҵ�������*/
                    else if(postion[1]>(128+TCS_2046_Calibration_Error)&&postion[1]<(128+32+TCS_2046_Calibration_Error))
                    {
                        state = 14;/*��ʾ�������ϵ���*/
                    }
                    /*��ʾ���������ұ�����*/
                     else if(postion[1]>(192-TCS_2046_Calibration_Error))
                    {
                       
                        state = 16;/*��ʾ�������ϵ���*/
                        
                    }
                    
                    
               }
                
               
               
               
               /*X�����������µ������λ��*/
                if((postion[0]>64+5*16-TCS_2046_Calibration_Error)&&(postion[0]<96+5*16+TCS_2046_Calibration_Error))
                {
                
                
                    /*�жϴ���Y�����Ƿ�Ҳ����ָ������*/
                    if(postion[1]<(25+TCS_2046_Calibration_Error))
                    {
                        /*��ʾ����������������飬��ʾ������µ���*/   
                        state = 11; /*��ʾ������ϵ���*/
                    }
                    
                    /*���ڴ������ҵڶ�����*/
                    else if(postion[1]>(64+TCS_2046_Calibration_Error)&&postion[1]<(64+32+TCS_2046_Calibration_Error))
                    {
                        state = 13;/*��ʾ�·����µ���*/
                    }
                    /*���ڴ������ҵ�������*/
                    else if(postion[1]>(128+TCS_2046_Calibration_Error)&&postion[1]<(128+32+TCS_2046_Calibration_Error))
                    {
                        state = 15;/*��ʾ�������µ���*/
                    }
                    /*��ʾ���������ұ�����*/
                     else if(postion[1]>(192-TCS_2046_Calibration_Error))
                    {
                       
                        state = 17;/*��ʾ�������µ���*/
                        
                    }
                    
                    
               }
                                             
                
                /*�ж��Ƿ������ڽ��水��ȷ�ϼ�*/
               if((postion[0]>200-TCS_2046_Calibration_Error)&&(postion[0]<240+TCS_2046_Calibration_Error))/*X��Χһ��*/
               {
                   if((postion[1]>90-TCS_2046_Calibration_Error)&&(postion[1]<150+TCS_2046_Calibration_Error))/*Y��Χһ�£�ȷ�ϰ���ȷ�ϼ�*/
                   {
                       state = 5;
                   }
               }
            }

        }
    return state;
    
}



