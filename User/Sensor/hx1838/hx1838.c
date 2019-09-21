#include "hx1838.h"

extern uint32_t IC_Remote_Read;
extern uint8_t IC_Stase;
extern uint8_t IC_Remote_state;

/*************************************************
Function: HX1838_REC_Data
Description: �������ܵ������ݲ�����ʵ������ֵ
Input: ��
Output: ��
Return: ʵ��8λ��Ч����ֵ
Others: �� 
*************************************************/
uint8_t HX1838_REC_Data(void)
{
    uint8_t redata = 0;
    uint8_t data1 = 0,data2 = 0;
    if(IC_Stase==1)/*�������*/
    {
        /*��ȡ��ַ��*/
        data1 = (IC_Remote_Read&0xFF000000) >> 24;
        
        /*��ȡ��ַ�뷴��*/
        data2 = (IC_Remote_Read&0x00FF0000) >> 16;
        
        if(data1==(uint8_t)~data2)/*��ַ��У��*/
        {
            /*��ȡ������*/
            data1 = (IC_Remote_Read&0x0000FF00) >> 8;
        
            /*��ȡ�����뷴��*/
            data2 = (IC_Remote_Read&0x000000FF);
            
            if(data1==(uint8_t)~data2)/*��ַ��У�飬���鷴����Դ���Ƿ����*/
            {
                redata = data1;
            }
        }
    }
    IC_Remote_Read = 0;/*�������ԭʼ����ֵ����Ϊ0*/
    IC_Stase = 0;/*��ǣ���ʶ����δ��ɣ��Խ����´β���*/
    IC_Remote_state = 0;/*����ͬ��*/
    return redata;
}


/*************************************************
Function: HX1838_Deal_Data
Description: ��������ֵ�������������
Input: ��
Output: ��
Return: 1-6��Ӧ1-6����������7����<�����У�����8����>�����л�
Others: �� 
*************************************************/
uint8_t HX1838_Deal_Data(uint8_t data)
{
    uint8_t redata = 0;/*���صļ�ֵ*/
    if(data==0xa2)
    {
        redata = 1;/*���°���1*/
    }
    else if(data==0xc5||data==0x62)
    {
        redata = 2;
    }
    else if(data==0xe2)
    {
        redata = 3;
    }
    else if(data==0x22||data==0x45)
    {
        redata = 4;
    }
    else if(data==0x05||data==0x02)
    {
        redata = 5;
    }
    else if(data==0xc2)
    {
        redata = 6;
    }
    else if(data==0x10||data==0x21)
    {
        redata = 7;
    }
    else if(data==0xb5||data==0x5a)
    {
        redata = 8;
    }
    return redata;
    
}

