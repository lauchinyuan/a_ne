#ifndef _RTC_H_
#define _RTC_H_
#include "stm32f4xx.h"

/*�ṹ�嶨��*/
typedef struct RCT_Time
{
    uint16_t tem_year;/*��ʱʱ��ֵ�����ڸ���ʱ��*/
    uint8_t tem_month;
    uint8_t tem_date;
    uint8_t tem_hour;
    uint8_t tem_min;
    uint8_t tem_week;
} RCT_Temp;

/*��غ궨��*/
#define RTC_CLOCK_SOURCE_LSI     /*ʹ��LSEʱ��*/
#define RTC_ASYHCHPREDIV       0X7F/*�첽��Ƶ����*/
#define RTC_SYHCHPREDIV        0XFF/*ͬ����Ƶ����*/
#define RTC_Format_BINorBCD    RTC_Format_BIN/*ʱ���ʽ*/
#define RTC_BKP_DRX            RTC_BKP_DR0/*ʹ��DR0��Ϊ���ݼĴ���*/


/*�û��Զ��庯��*/
void RTC_UserInit(void);
void RTC_NVIC_Conf(void);
void RTC_Conf(void);
void RTC_Set_Time(uint16_t year,uint8_t month,uint8_t date,uint8_t weekday,uint8_t hour,uint8_t min,uint8_t sec,uint8_t AM_OR_PM);
void RTC_LCD_Show_Time(void);
#endif

