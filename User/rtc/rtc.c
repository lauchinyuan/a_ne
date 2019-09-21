#include "rtc.h"
/*************************************************
Function: RTC_UserInit
Description: ʵʱʱ�ӳ�ʼ��
Input: ��
Output:��
Return: ��
Others: ��
*************************************************/
void RTC_UserInit(void)
{
    if (RTC_ReadBackupRegister(RTC_BKP_DRX) != 0x2019)/*��һ�����ã��˴�0x2019Ϊһ��־*/
    {
        /*����RTCʱ�Ӽ���Ƶ*/
        RTC_Conf();
        
        /*��󱸼Ĵ���д���־�������Ѿ����ù�ʱ�䣬�ٴ��ϵ�ʱ��������*/
        RTC_WriteBackupRegister(RTC_BKP_DRX, 0x2019);
        
        /*���ó�ʼʱ��*/
        RTC_Set_Time(2019,7,31,6,20,37,00,RTC_H12_PM);
    }
    else/*���ǵ�һ������*/
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);/*ʹ��PWRʱ��*/
        PWR_BackupAccessCmd(ENABLE);/*�󱸼Ĵ���ʹ��*/
        RTC_WaitForSynchro();/*�ȴ�ͬ��*/        
    }
}


/*************************************************
Function: RTC_Conf
Description: ѡ��RTCʱ��Դ������RTC_CLK�ķ�Ƶϵ��
Input: ��
Output:��
Return: ��
Others: �����첽��Ƶ����Ϊ��127��
                ͬ����Ƶ����Ϊ��255��
                ���������������������ʱ�� = 32.768/(127+1)*(255+1)=1HZ
                ��ÿ�����һ��
*************************************************/
void RTC_Conf(void)
{
    RTC_InitTypeDef RTC_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);/*ʹ�� PWR ʱ��*/
    PWR_BackupAccessCmd(ENABLE);/*�󱸼Ĵ���ʹ��*/
    RCC_LSEConfig(RCC_LSE_ON);/* ʹ��LSE */
    while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);/* �ȴ�LSE�ȶ� */
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);/*ʹ��32.768khz������Ϊ����Դ*/
    RCC_RTCCLKCmd(ENABLE);	/*ʹ��RTCʱ��*/
    RTC_WaitForSynchro();   /*�ȴ�ͬ��*/
    
    /*��ʼ��RTC_InitStructure�ṹ�帳ֵ*/
    RTC_InitStructure.RTC_AsynchPrediv = RTC_ASYHCHPREDIV;/*�첽��Ƶ����*/
    RTC_InitStructure.RTC_SynchPrediv =  RTC_SYHCHPREDIV;/*ͬ����Ƶ����*/
    RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;/*24ʱ��*/
    RTC_Init(&RTC_InitStructure);
}

/*************************************************
Function: RTC_Set_Time
Description: ʱ����������ú���
Input: ʱ��ֵ,����weekdayΪ������������1��7��AM_OR_PM��ʾ��ǰ��󣬿�ΪRTC_H12_AM��RTC_H12_PM
Output:��
Return: ��
Others: AM_OR_PM��ʾ��ǰ��󣬿�ΪRTC_H12_AM��RTC_H12_PM
*************************************************/
void RTC_Set_Time(uint16_t year,uint8_t month,uint8_t date,uint8_t weekday,uint8_t hour,uint8_t min,uint8_t sec,uint8_t AM_OR_PM)
{
    RTC_TimeTypeDef RTC_TimeStructure;
    RTC_DateTypeDef RTC_DateStructure;
    /*�趨ʱ����Ϣ*/
    RTC_TimeStructure.RTC_H12 = AM_OR_PM;/*��ǰ������趨*/
    RTC_TimeStructure.RTC_Hours = hour;
    RTC_TimeStructure.RTC_Minutes = min;
    RTC_TimeStructure.RTC_Seconds = sec;
    RTC_SetTime(RTC_Format_BINorBCD, &RTC_TimeStructure);
    
    /*�趨��������Ϣ*/
    RTC_DateStructure.RTC_WeekDay = weekday;
    RTC_DateStructure.RTC_Date = date;
    RTC_DateStructure.RTC_Month = month;
    RTC_DateStructure.RTC_Year = year-48;/*��2018��Ϊ��׼*/
    RTC_SetDate(RTC_Format_BIN, &RTC_DateStructure);
      
}

