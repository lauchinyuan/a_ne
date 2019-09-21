#ifndef _MAIN_H_
#define _MAIN_H_

#include "led.h"
#include "usart.h"
#include "inoutput.h"
#include "iic.h"
#include "tcs3472.h"
#include "dht12.h"
#include "max6675.h"
#include "ili9341.h"
#include "rtc.h"
#include "w25q16.h"
#include "tsc2046.h"
#include "tim.h"
#include "hx1838.h"
#include "mpu9250.h"
#include "host.h"
#include "math.h"

uint16_t CurrentX = 0;       /*��Ļ����X����*/
uint16_t CurrentY = 0;       /*��Ļ����Y����*/

/*��ֵ�����ж�DHT12����ת��֮���Ƿ���������������
   ��ֵ���ڶ�ʱ���жϷ���������1����1��������ʱ����*/
extern uint8_t SenState;

uint8_t Print_Model = 6;/*�����ж���Ļ��ӡ�ĸ�����,��λ�����Print_Model = 6��ȫ����Ϣ��ʾ*/
    
uint8_t Print_State = 0;/*��Ļ��ʾ��ӡ״̬����ֵΪ0ʱ����Ļ�ɴ�ӡ��ʾ��Ϣ*/

float Dhtout[2] = {0};/*DHT12�¶ȱ���*/
uint8_t Dhtdata[5] = {0};

/*Һ��������,Һ������������675���ַ���������Ҫ�������������Ԫ�ظ���*/
char str[20] = {0};
char dhtsoult[20] = {0};
int16_t ang = 0;/*���߻���*/

/*ʵʱʱ�ӱ���*/
uint8_t Clock_Print_Model = 0;/*����ʱ�����ʱ�л�����*/
uint8_t Rtctmp=0;             /*ʱ���������¼��ǰRTC��ֵ*/
RTC_TimeTypeDef RTC_TimeStructure;          /*ʱ�ӽṹ���������¼ʱ����*/
RTC_DateTypeDef RTC_DateStructure;          /*���ڽṹ���������¼������*/
RCT_Temp RCT_Tem_Time;/*��ʱʱ��ṹ����������ڸ���ʱ��*/



uint8_t point_state;/*���ڼ�¼����Ӧ�ú��� TSC2046_Applic���� ����ֵ*/
    
float maxsoult = 0;/*MAX6675����*/
    
uint16_t RGB565color = 0;/*TCS34725��ɫ����������*/
uint32_t RGB888color = 0;

uint16_t touch_posit[2] = {0};/*TSC2046����������*/
  
uint8_t remote_rec = 0;/*ң������������¼ң�������� HX1838_Deal_Data���� ����ֵ*/
extern uint8_t IC_Stase;

MPU9250_Angle MPUANG;/*MPU9250�ṹ��������洢�Ƕ�*/

uint16_t x2,y2; /*��������*/ 


/*��������*/     
#define Line_Length   50/*���߳���*/

/*�û��Զ��庯��*/
void SYSTEM_Init(void);

#endif

