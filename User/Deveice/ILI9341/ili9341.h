#ifndef _ILI9341_H_
#define _ILI9341_H_
#include "stm32f4xx.h"

/*RGB565��ɫ����*/
#define   ILI9431_Back_Color        BLACK        /*������ɫ*/
#define   ILI9431_Text_Color        DCYAN       /*������ɫ*/

#define   BLACK                     0x0000       /*��ɫ*/
#define   PURPLE                    0x780F       /*��ɫ*/
#define   WHITE                     0xFFFF       /*��ɫ*/
#define   RED                       0xF800       /*��ɫ*/
#define   BLUE                      0x001F       /*��ɫ*/
#define   OLIVE                     0x7BE0       /*�����*/
#define   CYAN                      0x07FF       /*��ɫ*/
#define   MAGENTA                   0xF81F       /*Ʒ��*/
#define   DCYAN                     0x03EF       /*����ɫ*/

/*RGB565��RGB888ת������*/
#define RGB888_RED      0x00ff0000
#define RGB888_GREEN    0x0000ff00
#define RGB888_BLUE     0x000000ff
 
#define RGB565_RED      0xf800
#define RGB565_GREEN    0x07e0
#define RGB565_BLUE     0x001f

/*�ֿ���ģ��������*/
/*����������ģΪGB2312 �����СΪA*B����ģ*/
#define   A                         16       /*������򳤶�*/
#define   B                         16       /*�������򳤶�*/

#define   ILI9431_Y_Lenth           240     /*��Ļ���򳤶�*/
#define   ILI9431_X_Lenth           360     /*��Ļ���򳤶�*/

#define   ILI9431_Data_Size         ((A/8)*B)   /*ÿ�������õ��ֽڴ�С*/


/*�����������*/
#define      ILI9431_BK_CLK                RCC_AHB1Periph_GPIOB   
#define      ILI9431_BK_PORT               GPIOB
#define      ILI9431_BK_Pin                GPIO_Pin_15

/*����ʹ�õĴ洢����ΪFSMC_Bank1_NORSRAM4����������ַΪ0x6C000000-0x6FFFFFFF��
��ʹ����Ļʱ������FSMC_A0ģ��DCX������Ϊ�ߵ�ƽʱ��ʾ���ݣ��͵�ƽʱ��ʾ���
���� HADDR Ϊ�ֽڵ�ַ�����洢������Ѱַ�����Ը��ݴ洢�����ݿ�Ȳ�ͬ��
ʵ����洢�����͵ĵ�ַҲ��������ͬ���˴���ַΪ16λ��ַ�����ο��ֲᣬд���ֵ������1λ
Ϊ��ʹA0��ֵΪ�û����ƣ���������1λ*/
#define 	 ILI9431_Data_ADDR		(uint32_t)(0x6E000000|(1<<7))	
#define 	 ILI9431_Cmd_ADDR		(uint32_t)(0x6E000000&~(1<<7))

#define      W25Q16_ASCII_Start_Addr    (uint32_t)0x1F0000
#define      W25Q16_GB2312_Start_Addr    (uint32_t)0x000000

/*���������*/
#define ILI9431_Cmd_Read_ID4		0xD3
#define ILI9431_Cmd_Reset			0x01

#define DEBUG_DELAY()               ILI9341_Delay(0x5000)

/*�û��Զ��庯��*/
void ILI9341_GPIO_Conf(void);
void ILI9341_Init(void);
void ILI9341_BackLight(uint8_t state);
void ILI9341_Delay(uint32_t time);
void ILI9341_Default(void);
uint16_t RGB888ToRGB565(uint32_t n888Color);

/*������д����*/
void ILI9341_Write_Command(uint16_t cmd);
void ILI9341_Write_Data(uint16_t data);

/*��Ļ�������*/
void ILI9341_Drew_Rec(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color);
void ILI9341_Open_Windows(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
void ILI9341_Print_GBChar(uint16_t x,uint16_t y,uint16_t ch);
void ILI9341_Print_ASChar(uint16_t x,uint16_t y,uint8_t ch);
void ILI9341_Print_Str(uint16_t x,uint16_t y,char* str);
void ILI9341_Line_Print(uint8_t line,char* str);
void ILI9431_Drew_Cross(uint16_t x,uint16_t y,uint16_t color);
void ILI9431_Drew_All_Bak(void);
void ILI9431_Clean_Cross(uint16_t x,uint16_t y);
void ILI9341_Draw_Point(uint16_t x,uint16_t y,uint16_t color);
void ILI9341_Drew_Line(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color);
void ILI9341_Next_Win(void);
void ILI9341_Last_Win(void);
#endif
