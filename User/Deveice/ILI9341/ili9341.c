#include "ili9341.h"
#include "w25q16.h"
#include "fsmc.h"
extern  uint16_t CurrentX;
extern  uint16_t CurrentY;
extern uint8_t Print_Model;
extern uint8_t Print_State;
extern uint8_t Clock_Print_Model;

/*************************************************
Function: ILI9341_GPIO_Conf
Description: ��������Һ����ʾ���������
Input: ��
Output:��
Return: ��
Others: ��
*************************************************/
void ILI9341_GPIO_Conf(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	/*����GPIOʱ��*/
	RCC_AHB1PeriphClockCmd(ILI9431_BK_CLK, ENABLE);
	
	/*���ñ�������*/
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin = ILI9431_BK_Pin;
	GPIO_Init(ILI9431_BK_PORT, &GPIO_InitStruct);
}

/*************************************************
Function: ILI9341_Init
Description: ��ʼ��ILI9341
Input: ��
Output:��
Return: ��
Others: ��
*************************************************/
void ILI9341_Init(void)
{
	
	FSMC_Conf();/*����FSMCģ��ʱ��*/
	
	ILI9341_GPIO_Conf();/*�����������*/
      
    ILI9341_Default();/*������Ļ����*/
    
    ILI9431_Drew_All_Bak();/*����Ļ���*/
    
    ILI9341_BackLight(1);/*������Ļ����Դ*/
}

/*************************************************
Function: ILI9341_Print_GBChar
Description: ��ָ��������㿪ʼ��ӡһ������
Input: xΪ���ַ�����ʼ���X����ֵ��yΪ�ַ�����ʼ���Y����ֵ��chΪ�����ַ�
Output:��
Return: ��
Others: �ֿ���Դ��w25q16�е�ȡGB2312�ֿ�
*************************************************/
void ILI9341_Print_GBChar(uint16_t x,uint16_t y,uint16_t ch)
{
    uint8_t i,j,k;/*����ѭ��*/
    uint8_t chdata1[ILI9431_Data_Size]  ={0};/*�����ַ���ģ����*/
    uint32_t pos = 0;/*���ַ����루�ֿ����ַ�����ƫ��ֵ*/
    uint32_t devi = 0;/*���ַ���ģ���ݣ��루�ֿ��һ���ֽ����ݣ�֮�������ֽ���*/
    uint8_t t = 0;
    unsigned char High8bit,Low8bit;/*�����ֿ����ݵĸߵ�8λ*/
    
   
    High8bit= (ch&0xFF00)>> 8;      /* ȡ��8λ���� */
    Low8bit= ch & 0x00FF;           /* ȡ��8λ����*/   

    
      /*�����ַ�ƫ��ֵ*/    
      if(High8bit < 0xAA)
      {
            /* GB2312 A1A0~A9FF: 1~9��, �����ż�����Ƭ��ƽ�����������ַ� */
            pos = ((High8bit-0xA1)*94 + Low8bit-0xA1);
      }
      else if((High8bit > 0xAF) && (High8bit < 0xF8))
      {
            /* GB2312 B0A0~F7FF: 16~55��: һ������, 56~87��: �������� */
            /*�˴�1410Ϊ�����ֿ�ƫ��ֵ*/
            pos = (1410 + (High8bit-0xB0)*94 + Low8bit-0xA1);
      }
      else
      {
            pos = 0;/* GB2312 ������λδ����(����) */
      }
      
      devi = pos*ILI9431_Data_Size;
      
   
    /*��w25q16�л�ȡ��ģ����,��������ȡILI9431_Data_Size���ֽ�*/
    W25Q16_Read_Byte((W25Q16_GB2312_Start_Addr+(uint32_t)devi),chdata1,ILI9431_Data_Size);
    
    /*������ӡ����*/
    ILI9341_Open_Windows(x,y,x+B-1,y+A-1);
    
    /*��ʼ���*/
    ILI9341_Write_Command(0x2C);
    
    /*��i+1��*/
	for(i = 0;i<B;i++)
	{
        
        /*��i+1�еĵ�j+1���ֽ�*/
		for(j = 0;j<(A/8);j++)
		{
            
            /*ÿ���ֽ���λ��ӡ*/
			for(k = 0;k<8;k++)
            {
                /*�����ʱ��ȡ���ֽ�����λ��*/
                t = i*(A/8)+j;
                
                if((chdata1[t]&0x80)==0x80)/*��Ҫ���������ɫ�����ص�*/
                {
                    ILI9341_Write_Data(ILI9431_Text_Color);
                }
				
                else/*��䱳����ɫ�����ص�*/
                {
                    ILI9341_Write_Data(ILI9431_Back_Color);
                }
                chdata1[t]<<=1;
            }
		}
        
		
	}
     
}


/*************************************************
Function: ILI9341_Print_ASChar
Description: ��ָ��������㿪ʼ��ӡһ��Ӣ���ַ�
Input: xΪ���ַ�����ʼ���X����ֵ��yΪ�ַ�����ʼ���Y����ֵ��chΪ�ַ�
Output:��
Return: ��
Others: �ֿ���Դ��w25q16�е�ȡASCII�ֿ�
*************************************************/
void ILI9341_Print_ASChar(uint16_t x,uint16_t y,uint8_t ch)
{
    uint8_t i,j,k;/*����ѭ��*/
    uint8_t chdata1[ILI9431_Data_Size]  ={0};/*�����ַ�����Ĥ����*/
    uint32_t pos = 0;/*���ַ�������ڣ��ֿ����ַ�����ƫ����*/
    uint32_t devi = 0;/*�ַ���ģ��������ڵ�һ���ֽ����ݵ�ƫ����*/
    uint8_t t = 0;
    
   /*�����ַ�ƫ��ֵ*/  
      pos = ch - ' ';
      
      devi = pos*ILI9431_Data_Size/2;/*ÿ��ASCII�ַ���ģ����ռ��ILI9431_Data_Size/2���ֽڿռ�*/
 
    /*ͨ��SPIЭ���w25q16�л�ȡ��ģ����,��������ȡILI9431_Data_Size���ֽڣ�*/
    W25Q16_Read_Byte((W25Q16_ASCII_Start_Addr+(uint32_t)devi),chdata1,ILI9431_Data_Size/2);
    
    /*������ӡ����*/
    ILI9341_Open_Windows(x,y,x+B-1,y+(A/2)-1);
    
    ILI9341_Write_Command(0x2C);/*�����������*/
    
    /*��i+1��*/
	for(i = 0;i<B;i++)
	{ 
        /*��i+1�еĵ�j+1���ֽ�*/
		for(j = 0;j<(A/16);j++)
		{
            
            /*ÿ���ֽ���λ��ӡ*/
			for(k = 0;k<8;k++)
            {
                /*�����ʱ��ȡ���ֽ�����λ��*/
                t = i*(A/16)+j;
                
                if((chdata1[t]&0x80)==0x80)
                {
                    ILI9341_Write_Data(ILI9431_Text_Color);
                }
				
                else
                {
                    ILI9341_Write_Data(ILI9431_Back_Color);
                }
                chdata1[t]<<=1;
            }
		}		
	}
    
}

/*************************************************
Function: ILI9341_Print_Str
Description: ��ָ��������㿪ʼ��ӡ��Ӣ���ַ���
Input: xΪ���ַ�����ʼ���X����ֵ��yΪ�ַ�����ʼ���Y����ֵ��strΪ�ַ���
Output:��
Return: ��
Others: ��
*************************************************/
void ILI9341_Print_Str(uint16_t x,uint16_t y,char* str)
{
    uint8_t i = 0;
    uint16_t ch = 0;
    /*LCD����ӡʱ������Y�����ӣ�����Y������*/
    CurrentX = x;       /*��ǰ����X�����*/
    CurrentY = y;       /*��ǰ����Y�����*/

    while(str[i]!='\0')
    {
        /*���ж��Ƿ���Ҫ����*/
        if((CurrentY+A)>ILI9431_Y_Lenth||str[i]=='\n')
        {
            /*Y��ص��趨�����*/
            CurrentY = y;
            
            CurrentX += B;
            if(str[i]=='\n')
            {
                /*����Ӧת���ַ�����������Ը��ַ�(����ӡ)*/
                i++;
                continue;
            }
        }
        
        /*STM32ʹ��С��ģʽ���˴����иߵͰ�λ���ݽ���*/
        ch = * ( uint16_t * ) &str[i];
        
        ch = ( ch << 8 ) + ( ch >> 8 );
        
        /*�ж������ֿ�*/
        if(((ch&0xFF00)>>8)>=0xA1)
        {
            /*ʹ��GB2312�ֿ�*/
             ILI9341_Print_GBChar(CurrentX,CurrentY,ch);

             CurrentY += A; /*��������*/

             i+=2;/*һ��GB2312�ַ�ռ�����ֽ�*/
            
        }
        else
        {
            /*ʹ��ASCII�ֿ�*/
            ILI9341_Print_ASChar(CurrentX,CurrentY,(uint8_t)(str[i]));
            
            CurrentY += (A/2);/*��ĸֻռһ����*/
            i+=1;
            
        }  
        
    }
}

/*************************************************
Function: ILI9341_BackLight
Description: ����ILI9341�����
Input: stateΪ1ʱ�������⣬Ϊʱ�رձ���
Output:��
Return: ��
Others: ��
*************************************************/
void ILI9341_BackLight(uint8_t state)
{
	if(state == 1)
	{
		
		GPIO_SetBits(ILI9431_BK_PORT,ILI9431_BK_Pin);/*���ñ������Ÿߵ�ƽ��������*/
		
	}
	else if(state == 0)
	{
		
		GPIO_ResetBits(ILI9431_BK_PORT,ILI9431_BK_Pin);/*���ñ������ŵ͵�ƽ�رձ���*/
	}
	
}



/*************************************************
Function: ILI9341_Write_Command
Description: ����FSMCģ��ʱ������Ļ��������
Input: cmdΪ����
Output:��
Return: ��
Others: ��
*************************************************/
void ILI9341_Write_Command(uint16_t cmd)
{
	uint16_t *p = (uint16_t*)(ILI9431_Cmd_ADDR);
	*p = cmd;
}



/*************************************************
Function: ILI9341_Write_Data
Description: ����FSMCģ��ʱ������Ļ��������
Input: dataΪ����
Output:��
Return: ��
Others: ��
*************************************************/
void ILI9341_Write_Data(uint16_t data)
{
	uint16_t *p = (uint16_t*)(ILI9431_Data_ADDR);
	*p = data;
}



/*************************************************
Function: ILI9341_GPIO_Conf
Description: д��Һ�����������ֲ��ṩ���������ݣ���ʼ����ʾ��ʵ�ֺ�������
Input: ��
Output:��
Return: ��
Others: �ú��������������
*************************************************/
void ILI9341_Default(void)
{
	/*�������������ɳ����ṩ*/
	/*  Power control B (CFh)  */
	DEBUG_DELAY  ();
	ILI9341_Write_Command ( 0xCF  );
	ILI9341_Write_Data ( 0x00  );
	ILI9341_Write_Data ( 0x81  );
	ILI9341_Write_Data ( 0x30  );
	
	/*  Power on sequence control (EDh) */
	DEBUG_DELAY ();
	ILI9341_Write_Command ( 0xED );
	ILI9341_Write_Data ( 0x64 );
	ILI9341_Write_Data ( 0x03 );
	ILI9341_Write_Data ( 0x12 );
	ILI9341_Write_Data ( 0x81 );
	
	/*  Driver timing control A (E8h) */
	DEBUG_DELAY ();
	ILI9341_Write_Command ( 0xE8 );
	ILI9341_Write_Data ( 0x85 );
	ILI9341_Write_Data ( 0x10 );
	ILI9341_Write_Data ( 0x78 );
	
	/*  Power control A (CBh) */
	DEBUG_DELAY ();
	ILI9341_Write_Command ( 0xCB );
	ILI9341_Write_Data ( 0x39 );
	ILI9341_Write_Data ( 0x2C );
	ILI9341_Write_Data ( 0x00 );
	ILI9341_Write_Data ( 0x34 );
	ILI9341_Write_Data ( 0x02 );
	
	/* Pump ratio control (F7h) */
	DEBUG_DELAY ();
	ILI9341_Write_Command ( 0xF7 );
	ILI9341_Write_Data ( 0x20 );
	
	/* Driver timing control B */
	DEBUG_DELAY ();
	ILI9341_Write_Command ( 0xEA );
	ILI9341_Write_Data ( 0x00 );
	ILI9341_Write_Data ( 0x00 );
	
	/* Frame Rate Control (In Normal Mode/Full Colors) (B1h) */
	DEBUG_DELAY ();
	ILI9341_Write_Command ( 0xB1 );
	ILI9341_Write_Data ( 0x00 );
	ILI9341_Write_Data ( 0x1B );
	
	/*  Display Function Control (B6h) */
	DEBUG_DELAY ();
	ILI9341_Write_Command ( 0xB6 );
	ILI9341_Write_Data ( 0x0A );
	ILI9341_Write_Data ( 0xA2 );
	
	/* Power Control 1 (C0h) */
	DEBUG_DELAY ();
	ILI9341_Write_Command ( 0xC0 );
	ILI9341_Write_Data ( 0x35 );
	
	/* Power Control 2 (C1h) */
	DEBUG_DELAY ();
	ILI9341_Write_Command ( 0xC1 );
	ILI9341_Write_Data ( 0x11 );
	
	/* VCOM Control 1 (C5h) */
	ILI9341_Write_Command ( 0xC5 );
	ILI9341_Write_Data ( 0x45 );
	ILI9341_Write_Data ( 0x45 );
	
	/*  VCOM Control 2 (C7h)  */
	ILI9341_Write_Command ( 0xC7 );
	ILI9341_Write_Data ( 0xA2 );
	
	/* Enable 3G (F2h) */
	ILI9341_Write_Command ( 0xF2 );
	ILI9341_Write_Data ( 0x00 );
	
	/* Gamma Set (26h) */
	ILI9341_Write_Command ( 0x26 );
	ILI9341_Write_Data ( 0x01 );
	DEBUG_DELAY ();
	
	/* Positive Gamma Correction */
	ILI9341_Write_Command ( 0xE0 ); //Set Gamma
	ILI9341_Write_Data ( 0x0F );
	ILI9341_Write_Data ( 0x26 );
	ILI9341_Write_Data ( 0x24 );
	ILI9341_Write_Data ( 0x0B );
	ILI9341_Write_Data ( 0x0E );
	ILI9341_Write_Data ( 0x09 );
	ILI9341_Write_Data ( 0x54 );
	ILI9341_Write_Data ( 0xA8 );
	ILI9341_Write_Data ( 0x46 );
	ILI9341_Write_Data ( 0x0C );
	ILI9341_Write_Data ( 0x17 );
	ILI9341_Write_Data ( 0x09 );
	ILI9341_Write_Data ( 0x0F );
	ILI9341_Write_Data ( 0x07 );
	ILI9341_Write_Data ( 0x00 );
	
	/* Negative Gamma Correction (E1h) */
	ILI9341_Write_Command ( 0XE1 ); //Set Gamma
	ILI9341_Write_Data ( 0x00 );
	ILI9341_Write_Data ( 0x19 );
	ILI9341_Write_Data ( 0x1B );
	ILI9341_Write_Data ( 0x04 );
	ILI9341_Write_Data ( 0x10 );
	ILI9341_Write_Data ( 0x07 );
	ILI9341_Write_Data ( 0x2A );
	ILI9341_Write_Data ( 0x47 );
	ILI9341_Write_Data ( 0x39 );
	ILI9341_Write_Data ( 0x03 );
	ILI9341_Write_Data ( 0x06 );
	ILI9341_Write_Data ( 0x06 );
	ILI9341_Write_Data ( 0x30 );
	ILI9341_Write_Data ( 0x38 );
	ILI9341_Write_Data ( 0x0F );
	
	/* memory access control set */
	DEBUG_DELAY ();
	ILI9341_Write_Command ( 0x36 ); 	
	ILI9341_Write_Data ( 0xC8 );    /*����  ���Ͻǵ� (���)�����½� (�յ�)ɨ�跽ʽ*/
	DEBUG_DELAY ();
	
	/* column address control set */
	ILI9341_Write_Command (0x2A ); 
	ILI9341_Write_Data ( 0x00 );
	ILI9341_Write_Data ( 0x00 );
	ILI9341_Write_Data ( 0x00 );
	ILI9341_Write_Data ( 0xEF );
	
	/* page address control set */
	DEBUG_DELAY ();
	ILI9341_Write_Command ( 0x2B ); 
	ILI9341_Write_Data ( 0x00 );
	ILI9341_Write_Data ( 0x00 );
	ILI9341_Write_Data ( 0x01 );
	ILI9341_Write_Data ( 0x3F );
	
	/*  Pixel Format Set (3Ah)  */
	DEBUG_DELAY ();
	ILI9341_Write_Command ( 0x3a ); 
	ILI9341_Write_Data ( 0x55 );
	
	/* Sleep Out (11h)  */
	ILI9341_Write_Command ( 0x11 );	
	ILI9341_Delay ( 0xAFFf<<2 );
	DEBUG_DELAY ();
	
	/* Display ON (29h) */
	ILI9341_Write_Command ( 0x29 ); 
}

/*************************************************
Function: ILI9341_Delay
Description: ��ͨ�����ʱ����
Input: ��
Output:��
Return: ��
Others: ��
*************************************************/
void ILI9341_Delay(uint32_t time)
{
	while(time--);
}

/*************************************************
Function: ILI9341_Drew_Rec
Description: ��Һ�����ϻ���һ��ɫ����
Input: ����������(x1,y1),(x2,y2)����Ϊ�ԽǶ���,colorΪ������ɫ(RGB565)
Output:��
Return: ��
Others: ��
*************************************************/
void ILI9341_Drew_Rec(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color)
{
    
	uint32_t i = 0;

    ILI9341_Open_Windows(x1,y1,x2,y2);/*������䴰��*/
	
	ILI9341_Write_Command(0x2C);/*�����ɫ*/
	
	for(i = 0;i<(x2-x1+1)*(y2-y1+1);i++)/*��ÿ�����ص㶼�����ɫ*/
	{
		ILI9341_Write_Data(color);
        
	}

}


/*************************************************
Function: ILI9341_Open_Windows
Description: ��Һ�����Ͽ�һ����������׼�����
Input: ����������(x1,y1),(x2,y2)����Ϊ�ԽǶ���
Output:��
Return: ��
Others: �˴�Ҫ��x1<x2,y1<y2
*************************************************/
void ILI9341_Open_Windows(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
	
	ILI9341_Write_Command(0x2A);/*�趨�н���*/
		
	ILI9341_Write_Data((y1&0xFF00)>>8);/*д����ʼ�и߰�λ*/
	
	ILI9341_Write_Data(y1&0x00FF);/*д����ʼ�еͰ�λ������ͬ��*/
	
	ILI9341_Write_Data((y2&0xFF00)>>8);
	ILI9341_Write_Data(y2&0x00FF);
	
	
	ILI9341_Write_Command(0x2B);/*�趨�н���*/
	
	
	ILI9341_Write_Data((x1&0xFF00)>>8);/*д����ʼ�и߰�λ*/
	
	ILI9341_Write_Data(x1&0x00FF);/*д����ʼ�еͰ�λ������ͬ��*/
	
	ILI9341_Write_Data((x2&0xFF00)>>8);
	ILI9341_Write_Data(x2&0x00FF);
}


/*************************************************
Function: RGB888ToRGB565
Description: ��TCS34725�ɼ�����RGB888����װ��ΪҺ����ʹ�õ�RGB565����
Input: n888ColorΪRGB888��ɫֵ
Output:��
Return: ת�����RGB565ֵ
Others: ��
*************************************************/
uint16_t RGB888ToRGB565(uint32_t n888Color)
{
	uint16_t n565Color = 0;
 
	/* ��ȡRGB��ɫ������ȡ��λ*/
	uint8_t cRed   = (n888Color & RGB888_RED)   >> 19;
	uint8_t cGreen = (n888Color & RGB888_GREEN) >> 10;
	uint8_t cBlue  = (n888Color & RGB888_BLUE)  >> 3;
 
	/*����ƴ��*/
	n565Color = (cRed << 11) + (cGreen << 5) + (cBlue << 0);
	return n565Color;
}

/*************************************************
Function: ILI9431_Drew_All_Bak
Description: ������ʾ��ȫ����ʾ���򣬲�������Ϊ��ɫ
Input: ��
Output:��
Return: ��
Others: ��
*************************************************/
void ILI9431_Drew_All_Bak(void)
{
    ILI9341_Drew_Rec(0,0,ILI9431_X_Lenth,ILI9431_Y_Lenth,ILI9431_Back_Color);
    
}

/*************************************************
Function: TSC2046_Calibration
Description: ���趨��Ϊ���Ļ�һʮ�ּ�
Input: x,y�ֱ�Ϊ�����x,y��ֵ��colorΪ�����ɫ
Output:��
Return: ��
Others: ��
*************************************************/
void ILI9431_Drew_Cross(uint16_t x,uint16_t y,uint16_t color)
{
    uint8_t i,j;
    /*������׼�����*/
    ILI9341_Open_Windows(x-8,y-8,x+7,y+7);
    
    /*������������ʼ���*/
    ILI9341_Write_Command(0x2C);
    
    /*����16��*/
    for(i=0;i<16;i++)
    {
        /*ÿ��16�����ص�*/
        for(j=0;j<16;j++)
        {
            /*�ж��������*/
            if(i==7||i==8||j==7||j==8)/*����м����м��м�����*/
            { 
                ILI9341_Write_Data(color);           
            }
            else/*��������ɫ*/
            {
                
                ILI9341_Write_Data(ILI9431_Back_Color);
            }
        }      
    }
}


/*************************************************
Function: ILI9431_Clean_Cross
Description: ����������Ϊ���ĵĽ����
Input: x,y�ֱ�Ϊ�����x,y��ֵ
Output:��
Return: ��
Others: ��
*************************************************/
void ILI9431_Clean_Cross(uint16_t x,uint16_t y)
{
    ILI9341_Drew_Rec(x - 8,y -8,x + 7,y + 7,ILI9431_Back_Color);
}


/*************************************************
Function: ILI9341_Draw_Point
Description: ����Ļ�ϻ�����x1,y1����
Input: x,y�ֱ�Ϊ�����x,y��ֵ,colorΪ����ɫ
Output:��
Return: ��
Others: ��
*************************************************/
void ILI9341_Draw_Point(uint16_t x,uint16_t y,uint16_t color)
{
    ILI9341_Open_Windows(x,y,x+1,y+1);/*����*/
     
    ILI9341_Write_Command(0x2C);/*�����������*/
    ILI9341_Write_Data(color); /*�����ɫ*/
}

/*************************************************
Function: ILI9341_Drew_Line
Description: ����Ļ�ϻ����ԣ�x1,y1��,(x2,y2)����Ϊ�˵��ֱ��
Input: ��x1,y1��,(x2,y2)����Ϊֱ�߶˵�����,colorΪ����ɫ
Output:��
Return: ��
Others: ��
*************************************************/
void ILI9341_Drew_Line(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color)
{
    float k = 0;/*����ֱ�߷���б�ʣ�����ȷ�����������軭���λ�������������ص�*/
    uint16_t x,y,min,max;
     k = (float)(y2-y1)/(float)(x2-x1);
    
    if(x1==x2)/*����X������ͬ����б���޹�*/
    {
        min = y1<y2?y1:y2;/*�ж�y1,y2�еĴ�С��ֵ*/
        max = y1<y2?y2:y1;
        for(y=min; y<max; y++)
        {
            ILI9341_Draw_Point(x1+1,y,color);/*���Ӵ�Ч��*/
            ILI9341_Draw_Point(x1-1,y,color);
            ILI9341_Draw_Point(x1,y,color);
        }
    }
    else
    {
        min = x1<x2?x1:x2;/*�ж�x1,x2�еĴ�С��ֵ*/
        max = x1<x2?x2:x1;
        for(x=min; x<max; x++)
        {
            y = (k * (x - x1)) + y1;/*����yֵ���ڵ�*/
            ILI9341_Draw_Point(x+1,y,color);/*�������㣬�Ӵ�Ч��*/
            ILI9341_Draw_Point(x-1,y,color);
            ILI9341_Draw_Point(x,y,color);
        }
    }
    
}

/*************************************************
Function: ILI9341_Next_Win
Description: ��Ļ������һ����
Input: ��
Output:��
Return: ��
Others: ��
*************************************************/
void ILI9341_Next_Win(void)
{
    Clock_Print_Model = 0;/*������ʱClock_Print_Model����Ϊ0*/
    Print_State = 0;/*�ı��ӡ״̬��������Ļ��ӡ��ʾ��Ϣ*/
    ILI9431_Drew_All_Bak();/*��յ�ǰ����*/
    if(Print_Model<6)
     {
         Print_Model += 1;/*������һ����ģʽ*/
     }
    else/*�������������㿪ʼ*/
    {
         Print_Model = 0;
    }
}

/*************************************************
Function: ILI9341_Last_Win
Description: ��Ļ������һ����
Input: ��
Output:��
Return: ��
Others: ��
*************************************************/
void ILI9341_Last_Win(void)
{
    Clock_Print_Model = 0;/*������ʱClock_Print_Model����Ϊ0*/
    Print_State = 0;/*�ı��ӡ״̬��������Ļ��ӡ��ʾ��Ϣ*/
    ILI9431_Drew_All_Bak();/*��յ�ǰ����*/
    if(Print_Model>0)
     {
         Print_Model -= 1;/*������һ����ģʽ*/
     }
    else/*�����������ӻ���6��ʼ*/
    {
         Print_Model = 6;
    }
}

/*************************************************
Function: ILI9341_Line_Print
Description: ��ָ����������ӡ�ַ���
Input: lineΪָ��������strΪ�ַ���
Output:��
Return: ��
Others: ��
*************************************************/
void ILI9341_Line_Print(uint8_t line,char* str)
{
    ILI9341_Print_Str(B*(line-1),0,str);/*�����ַ����������*/
}


