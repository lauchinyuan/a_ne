#include "stm32f4xx.h"
#include "main.h"

/*�����������*/
#define MPU9250_CALIB  1    /*��1ʱ�Խ��ٶȼ����ݽ���У׼*/
#define TCS3472_CALIB  0    /*��1ʱ����ɫ���������а�ƽ��У׼*/
#define TSC2046_CALIB  0    /*��1ʱʹ�ô���У׼���棬�Դ���������У׼*/

int main(void)
{
    
    /*ϵͳ��ʼ��*/    
    SYSTEM_Init();
    
    #if MPU9250_CALIB /*MPU9250���ٶȼƼ�������У׼*/    
    MPU9250_Offset();  
    #endif  /*MPU9250_CALIB*/
    
    #if TCS3472_CALIB /*TCS3472��ɫ��������ƽ��У׼*/    
    TCS3472_White_Balance();
    #endif  /*TCS3472_CALIB*/
    
    #if TSC2046_CALIB /*�������У����У׼ʱ����Һ������ʾУ׼�㣬���ε��У׼�㼴��*/    
    TSC2046_Calibration();    
    #endif  /*TSC2046_CALIB*/
        
     while(1)
    {
    
/*******************MPU9250�����������ж���ʱ***********************/        
        
            MPU9250_Get_Angle(&MPUANG);/*���Ƕ�ֵ��ֵ���ṹ��*/
            ang = (int16_t)MPUANG.Angle_Y;/*�ӽṹ��õ��Ƕ�ֵ*/
            HOST_Send_float(MPUANG.Angle_Y,0xF3);/*�����ݷ��͵�������λ��*/
            
            
            if(Print_Model==4)/*�������ʾ���棨Print_Model=4��Ҫ�����״̬ͨ����Ļ��ʾ��
                                ���У�112��80��Ϊ����ԭ�㣬Line_LengthΪ�߳���*/
            {
               x2 = 112 + Line_Length * cos(ang*RAD_to_DEG);/*���㻭���յ��X,Y����*/
               y2 = 80 + Line_Length * sin(ang*RAD_to_DEG);
                
               ILI9341_Drew_Rec(112,80-Line_Length,112+Line_Length,80+Line_Length,BLACK);/*�����һ����*/
                
               ILI9341_Drew_Line(112,80,x2,y2,RED);/*����*/
               sprintf(str,"���Ϊ%.3lf��\n��б״̬����",MPUANG.Angle_Y);/*ת��Ϊ�ַ���*/
               ILI9341_Line_Print(3,str);/*���ַ����������Ļ*/
               
            }
            else if(Print_Model==6)/*��ȫ��ģʽ��Print_Model=6��ҲҪ��ʾ�����У�128��50��Ϊ����ԭ��*/
            {
               x2 = 128 + Line_Length * cos(ang*RAD_to_DEG);/*���㻭���յ��X,Y����*/
               y2 = 50 +  Line_Length * sin(ang*RAD_to_DEG);
                
               ILI9341_Drew_Rec(128,50-Line_Length,128+Line_Length,50+Line_Length,BLACK);/*�����һ����*/
               ILI9341_Drew_Line(128,50,x2,y2,RED);
                
               sprintf(str,"���Ϊ%.3lf��\n",MPUANG.Angle_Y);
               ILI9341_Line_Print(3,str);   
            }
            
            /*�˴��趨��ʾ��ǽ��棨Print_Model=4����ȫ��ģʽ��Print_Model=6��ʱ�޷�ͨ����Ǹı���Ļ����*/
             else if(MPUANG.Angle_Y>30)/*����������Ǵ���30��ʱ��׼�����н����л�*/
            {
                
                ILI9341_Print_Str(112,144,"���������л�");
                General_TIM_Delay_ms(500);/*��ʱ�ȴ��жϽ��*/
                MPU9250_Get_Angle(&MPUANG);/*���ж�һ�νǶȣ��Ƿ������Ҫ�л�*/
                if(MPUANG.Angle_Y>30)/*��Ҫ�����л�*/
                {
                    ILI9341_Next_Win();
                }
                else
                {
                    ILI9341_Drew_Rec(112,0,128,240,ILI9431_Back_Color);/*�����л��������ʾ���*/
                }
                General_TIM_Delay_ms(5);
            }
            
            else if(MPUANG.Angle_Y<-30)/*����������Ǵ���30��ʱ��׼�����н����л�*/
            {
                ILI9341_Print_Str(112,0,"���������л�");
                General_TIM_Delay_ms(500);
                MPU9250_Get_Angle(&MPUANG);
                if(MPUANG.Angle_Y<-30)/*��Ҫ�����л�*/
                {
                    ILI9341_Last_Win();
                }
                else
                {
                    ILI9341_Drew_Rec(112,0,128,240,ILI9431_Back_Color);/*�����л��������ʾ���*/
                }
                
                General_TIM_Delay_ms(5);
            }
             
        
/***********************��һ���жϣ��ж��Ƿ���ң���źű��ɼ�*********************/       
    if(IC_Stase==1)
    {
        remote_rec = HX1838_Deal_Data(HX1838_REC_Data());/*��ȡ������ֵ*/
            switch(remote_rec)/*�жϰ�����ֵ������ش����ı����״̬Print_Model��*/
            {
            case 1:/*����1*/
                Print_State = 0;/*ʹ��Ļ���Դ�ӡ��ʾ��Ϣ*/
                ILI9431_Drew_All_Bak();/*�����Ļ*/
                Print_Model = 0;/*�ı�Print_Modelֵ*/
            break;
            
            case 2:/*����2*/
                Print_State = 0;
                ILI9431_Drew_All_Bak();
                Print_Model = 1;
            break;
            
            case 3:/*����3*/
                Print_State = 0;
                ILI9431_Drew_All_Bak();
                Print_Model = 2;
            break;
            
            case 4:/*����4*/
                Print_State = 0;
                ILI9431_Drew_All_Bak();
                Print_Model = 3;
            break;
            
            case 5:/*����5*/
                Print_State = 0;
                ILI9431_Drew_All_Bak();
                Print_Model = 4;
            break;
            
            case 6:/*����6*/
                Print_State = 0;
                ILI9431_Drew_All_Bak();
                Print_Model = 5;
            break;
            
            case 7:/*��������<��*/
                ILI9341_Last_Win();
            break;
            
            case 8:/*��������>��*/
                ILI9341_Next_Win();
            break;
            
            default:
            break;
                
            }

    }    
  

       
/***************�ڶ����жϣ��ж��Ƿ���Ҫ��ӡ���澲̬������ʾ��Ϣ********************/
       if(Print_State == 0)
        {
            Print_State = 1;/*�ı��־����ֹ��Ļ���ϴ�ӡռ��ϵͳ��Դ*/ 
            
            ILI9341_Drew_Rec(250,0,300,64,RED);/*�����л�������ɫ����*/
            ILI9341_Drew_Rec(250,176,300,240,RED);
            
             switch(Print_Model)/*�ж�Ҫ��ʾ�ĸ�����*/
             {
                 case 0:/*������0����ʾDHT12�¶���Ϣ*/
                     ILI9341_Print_Str(200,28,"�������ఴť���л�����");
                     ILI9341_Print_Str(230,22,"��ǰ��ʾDHT12�¶Ȳɼ����");
                     ILI9341_Print_Str(301,0,"ȫ��ģʽ");
                     ILI9341_Print_Str(301,176,"������Ϣ");   
                 break;
                 
                 case 1:/*������1����ʾ������Ϣ*/
                     ILI9341_Print_Str(230,36,"��ǰ��ʾ����������Ϣ");
                     ILI9341_Print_Str(180,60,"���º�ʼ��ʾ");
                     ILI9341_Print_Str(301,0,"DHT�¶�");
                     ILI9341_Print_Str(301,146,"MAX6675�¶�");
                 break;
                 
                 case 2:/*������2����ʾRGB��ɫ��Ϣ*/
                     ILI9341_Print_Str(230,6,"��ǰ��ʾ�ȵ�ż�¶ȴ��������");
                     ILI9341_Print_Str(301,0,"������Ϣ");
                     ILI9341_Print_Str(301,176,"RGB��ɫ");
                 break;
                 
                 case 3:/*������3����ʾ��ɫ���������*/
                     ILI9341_Print_Str(230,16,"��ǰ��ʾRGB��ɫ���������");
                     ILI9341_Print_Str(301,0,"������Ϣ");
                     ILI9341_Print_Str(301,176,"�����Ϣ");
                 break;
                 
                 case 4:/*������4����ʾ��б״̬*/
                     ILI9341_Print_Str(180,28,"�˴����޷�ʹ������л�");
                     ILI9341_Print_Str(230,26,"��ǰ��ʾ���ٶȼ������Ϣ");
                     ILI9341_Print_Str(301,0,"RGB��ɫ");
                     ILI9341_Print_Str(301,176,"ʱ�����");
                 break;
                 
                 case 5:/*������5��ʱ���������*/
                     ILI9341_Print_Str(301,0,"�����Ϣ");
                     ILI9341_Print_Str(301,176,"ȫ��ģʽ");
                        switch(Clock_Print_Model)/*�ж�ʱ���������ģʽ����������ط�Ӧ*/
                        {
                            case 0:/*������6*/
                                /*��ʾ��ʱ������йص���ʾ��Ϣ*/
                            ILI9341_Print_Str(201,0,"ʱ�ӵ���");
                            ILI9341_Print_Str(201,176,"���ڵ���");              
                            ILI9341_Drew_Rec(160,0,200,64,0x0A10);
                            ILI9341_Drew_Rec(160,176,200,240,0x0A10);                
                            break;
                            
                            case 1:/*������6�е��ӻ���1*/
                                /*����ʱ��ʱ�Ļ���*/
                            ILI9341_Print_Str(241,102,"ȷ��");
                            ILI9341_Drew_Rec(200,90,240,150,0x0F30);/*0x0F30Ϊһ��ɫֵ��RGB565��*/
                            RCT_Tem_Time.tem_hour = RTC_TimeStructure.RTC_Hours;
                            RCT_Tem_Time.tem_min = RTC_TimeStructure.RTC_Minutes;
                            sprintf(str,"Сʱ\n�ϵ�\n\n%02d\n\nСʱ\n�µ�\n",RCT_Tem_Time.tem_hour);
                            ILI9341_Print_Str(64,0,str);
                            sprintf(str,"����\n�ϵ�\n\n%02d\n\n����\n�µ�\n",RCT_Tem_Time.tem_min);
                            ILI9341_Print_Str(64,192,str);                
                            break;
                            
                            case 2:/*������6�е��ӻ���2*/
                                /*��������ʱ�Ļ���*/
                            ILI9341_Print_Str(241,102,"ȷ��");
                            ILI9341_Drew_Rec(200,90,240,150,0x0F30);
                            RCT_Tem_Time.tem_year = RTC_DateStructure.RTC_Year+2000;
                            RCT_Tem_Time.tem_month = RTC_DateStructure.RTC_Month;
                            RCT_Tem_Time.tem_date = RTC_DateStructure.RTC_Date;
                            RCT_Tem_Time.tem_week = RTC_DateStructure.RTC_WeekDay;
                            
                            sprintf(str,"���\n�ϵ�\n\n%04ld\n\n���\n�µ�\n",RCT_Tem_Time.tem_year);
                            ILI9341_Print_Str(64,0,str);
                            sprintf(str,"�·�\n�ϵ�\n\n%02d\n\n�·�\n�µ�\n",RCT_Tem_Time.tem_month);
                            ILI9341_Print_Str(64,64,str);
                            sprintf(str,"����\n�ϵ�\n\n%02d\n\n����\n�µ�\n",RCT_Tem_Time.tem_date);
                            ILI9341_Print_Str(64,128,str);
                            sprintf(str,"����\n�ϵ�\n\n%02d\n\n����\n�µ�\n",RCT_Tem_Time.tem_week);
                            ILI9341_Print_Str(64,192,str);  
                            ILI9341_Line_Print(3,"ע��ƽ���꼰��С��");
                            break;
                            
                            }
                
                    break; 
                 
                 case 6:/*������6��ȫ��ģʽ*/
                     ILI9341_Print_Str(180,28,"�˴����޷�ʹ������л�");
                     ILI9341_Print_Str(230,36,"��ǰ��ʾȫ���ɼ���Ϣ");
                     ILI9341_Print_Str(301,0,"ʱ�����");
                     ILI9341_Print_Str(301,176,"DHT�¶�");
                 break;
                 
                 default:
                     break;
             }

        }  

        
/**************�������жϣ��ж�DHT12�Ƿ���Բɼ��¶����ݣ����ɲɼ�����IIC���߸�DHT12ʹ��*********************/         
        if((SenState&0x02)==0x02)
        {
            /*����ʱ��������ɼ�����*/
            DHT12_Read_(Dhtdata);
            if(DHT12_Deal_Tem_Hum(Dhtout,Dhtdata))/*����У׼��ȷ*/
            {
                HOST_Send_float(Dhtout[1],0xF1);
                HOST_Send_float(Dhtout[0],0xF2);
                if(Print_Model==0)/*�ڵ�һ�����ڵ�����ӡ����Ļ��*/
                {
                    sprintf(dhtsoult,"�¶ȣ�%.2f��\nʪ�ȣ�%.2f��\n",Dhtout[1],Dhtout[0]);
                    ILI9341_Line_Print(3,dhtsoult);
                }
                else if(Print_Model==6)/*ȫ��ģʽ��ҲҪ��ʾ*/
                {
                    sprintf(dhtsoult,"�¶ȣ�%.2f��\nʪ�ȣ�%.2f��\n",Dhtout[1],Dhtout[0]);
                    ILI9341_Line_Print(6,dhtsoult);
                }
            }
     
            /*��־λ����*/
            SenState &= ~(0x02);
        }        

        
/**********���ĸ��жϣ��ж���Ļָ�������Ƿ񱻰��£���������ı����״ֵ̬��ʹ��Ļ���Ըı��ӡ����************/       
         if(TCS_2046_PEN_Low)/*��Ļ����ʱ�������ж����ű�Ϊ�͵�ƽ*/
         {
             
             TSC2046_Calculate_XY(touch_posit);/*������������*/
             
              if(Print_Model==1)/*��������1(Print_Model==1)��Ҫ��������Ϣ��ʾ����Ļ��*/
             {
                 sprintf(str,"��������Ϊ��%03hu��%03hu��",touch_posit[0],touch_posit[1]);
                 ILI9341_Print_Str(32,0,str);
             } 
             else if(Print_Model==6)/*ȫ��ģʽ(Print_Model==6)��ҲҪ��ʾ*/
              {
                 sprintf(str,"��������Ϊ��%03hu��%03hu��",touch_posit[0],touch_posit[1]);
                 ILI9341_Line_Print(8,str);
              }
             point_state = TSC2046_Applic(touch_posit);/*��ȡTSC2046_Applic����ֵ����ֵ������ش�������*/            
             switch(point_state)/*����point_state�Ĳ�ֵͬ���в�ͬ����*/
             {
                 case 1:/*�л�����һ����*/
                     ILI9341_Last_Win();
                     break;
                 
                 
                 case 2:/*�л�����һ����*/
                     ILI9341_Next_Win();
                     break;
                 
                 
                 case 3:
                     /*����ʱ������ӻ��棨Clock_Print_Model=1��*/
                  Clock_Print_Model = 1;
                  Print_State = 0;
                  ILI9431_Drew_All_Bak();                 
                     break;
                 
                 
                 case 4:
                     /*�������ڵ����ӻ��棨Clock_Print_Model=2��*/
                  Clock_Print_Model = 2;
                  Print_State = 0;
                  ILI9431_Drew_All_Bak();                 
                     break;
                 
                 
                 case 5:/*����ȷ�ϼ�*/
                    Print_State = 0;
                    if(Clock_Print_Model==1)/*ʱ�ӵ�������ȷ�ϼ�����ʾҪ��������ʱ��*/
                    {
                        /*������ʱ��*/                
                      RTC_Set_Time(RTC_DateStructure.RTC_Year-48,
                        RTC_DateStructure.RTC_Month,
                        RTC_DateStructure.RTC_Date,
                        RTC_DateStructure.RTC_WeekDay,
                        RCT_Tem_Time.tem_hour,RCT_Tem_Time.tem_min,00,RTC_H12_PM);
                      
                    } 
                    
                    else if(Clock_Print_Model==2)/*���ڵ�������ȷ�ϼ�����ʾҪ��������ʱ��*/
                    {
                        /*����������*/               
                      RTC_Set_Time(RCT_Tem_Time.tem_year,RCT_Tem_Time.tem_month,RCT_Tem_Time.tem_date,RCT_Tem_Time.tem_week,
                        RTC_TimeStructure.RTC_Hours,
                        RTC_TimeStructure.RTC_Minutes,
                        RTC_TimeStructure.RTC_Seconds,RTC_H12_PM);
                      
                    }
                    
                      Clock_Print_Model = 0;/*�ص�ʱ����������棨Clock_Print_Model=0��*/
                      ILI9431_Drew_All_Bak();                                  
                     break;
                 
                 
                 case 6:/*Сʱֵ�ϵ�*/                     
                 if(RCT_Tem_Time.tem_hour<23)/*hour���Ϊ23*/
                 {
                     RCT_Tem_Time.tem_hour++;
                     General_TIM_Delay_ms(50);/*��ֹ�����л�*/
                 }
                 else/*��������*/
                 {
                     RCT_Tem_Time.tem_hour = 0;
                 }
                 sprintf(str,"%02d",RCT_Tem_Time.tem_hour);/*�����������е�����ת��Ϊ�ַ���*/
                 ILI9341_Print_Str(112,0,str);/*��ʾ���������е���ֵ�ı�*/                 
                     break;
                 
                 
                 case 7:/*Сʱֵ�µ�*/                     
                 if(RCT_Tem_Time.tem_hour>0)/*hour��СΪ0*/
                 {
                     RCT_Tem_Time.tem_hour--;
                     General_TIM_Delay_ms(50);/*��ֹ�����л�*/
                 }
                 else/*��������*/
                 {
                     RCT_Tem_Time.tem_hour = 23;
                 }
                 sprintf(str,"%02d",RCT_Tem_Time.tem_hour);/*�����������е�����ת��Ϊ�ַ���*/
                 ILI9341_Print_Str(112,0,str);
                     break;
                 
                 
                 case 8:
                     /*����ֵ�ϵ�*/
                 if(RCT_Tem_Time.tem_min<59)/*min���Ϊ59*/
                 {
                     RCT_Tem_Time.tem_min++;
                     General_TIM_Delay_ms(50);/*��ֹ�����л�*/
                 }
                 else/*��������*/
                 {
                     RCT_Tem_Time.tem_min = 0;
                 }
                 sprintf(str,"%02d",RCT_Tem_Time.tem_min);/*�����������е�����ת��Ϊ�ַ���*/
                 ILI9341_Print_Str(112,192,str);                 
                     break;
                 
                 
                 case 9:
                     /*����ֵ�µ�*/
                 if(RCT_Tem_Time.tem_min>0)/*min��ΪС0*/
                 {
                     RCT_Tem_Time.tem_min--;
                     General_TIM_Delay_ms(50);/*��ֹ�����л�*/
                 }
                 else/*��������*/
                 {
                     RCT_Tem_Time.tem_min = 59;
                 }
                 sprintf(str,"%02d",RCT_Tem_Time.tem_min);/*�����������е�����ת��Ϊ�ַ���*/
                 ILI9341_Print_Str(112,192,str);
                     break;
                 
                 
                 case 10:
                     /*������ϵ���*/
                 RCT_Tem_Time.tem_year++;
                 General_TIM_Delay_ms(50);/*��ֹ�����л�*/
                 sprintf(str,"%04ld",RCT_Tem_Time.tem_year);/*�����������е�����ת��Ϊ�ַ���*/
                 ILI9341_Print_Str(112,0,str);
                     break;
                 
                 
                 case 11:
                     /*������µ���*/
                 RCT_Tem_Time.tem_year--;
                 General_TIM_Delay_ms(50);/*��ֹ�����л�*/
                 sprintf(str,"%04ld",RCT_Tem_Time.tem_year);/*�����������е�����ת��Ϊ�ַ���*/
                 ILI9341_Print_Str(112,0,str);
                     break;
                 
                 
                 case 12:
                     /*�·����ϵ���*/
                 if(RCT_Tem_Time.tem_month<12)/*�·����ֵΪ12*/
                 {
                     RCT_Tem_Time.tem_month++;
                 }   
                 else
                 {
                     RCT_Tem_Time.tem_month = 1;
                 }
                 General_TIM_Delay_ms(50);/*��ֹ�����л�*/
                 sprintf(str,"%02d",RCT_Tem_Time.tem_month);
                 ILI9341_Print_Str(112,64,str);
                     break;
                 
                 
                 case 13:
                     /*�·����µ���*/
                 if(RCT_Tem_Time.tem_month>0)/*�·����ֵΪ12*/
                 {
                     RCT_Tem_Time.tem_month--;
                 }   
                 else
                 {
                     RCT_Tem_Time.tem_month = 12;
                 }
                 General_TIM_Delay_ms(50);/*��ֹ�����л�*/
                 sprintf(str,"%02d",RCT_Tem_Time.tem_month);
                 ILI9341_Print_Str(112,64,str);
                     break;
                 
                 
                 case 14:
                     /*�������ϵ���*/
                 if(RCT_Tem_Time.tem_date<31)/*�·����ֵΪ31*/
                 {
                     RCT_Tem_Time.tem_date++;
                 }   
                 else
                 {
                     RCT_Tem_Time.tem_date = 1;
                 }
                 General_TIM_Delay_ms(50);/*��ֹ�����л�*/
                 sprintf(str,"%02d",RCT_Tem_Time.tem_date);
                 ILI9341_Print_Str(112,128,str);
                     break;
                 
                 
                 case 15:
                      /*�������µ���*/
                 if(RCT_Tem_Time.tem_date>1)
                 {
                     RCT_Tem_Time.tem_date--;
                 }   
                 else
                 {
                     RCT_Tem_Time.tem_date = 31;
                 }
                 General_TIM_Delay_ms(50);/*��ֹ�����л�*/
                 sprintf(str,"%02d",RCT_Tem_Time.tem_date);
                 ILI9341_Print_Str(112,128,str);
                     break;
                 
                 
                 case 16:
                     /*�������ϵ���*/
                 if(RCT_Tem_Time.tem_week<7)/*�������ֵΪ7*/
                 {
                     RCT_Tem_Time.tem_week++;
                 }   
                 else
                 {
                     RCT_Tem_Time.tem_week = 1;
                 }
                 General_TIM_Delay_ms(50);/*��ֹ�����л�*/
                 sprintf(str,"%02d",RCT_Tem_Time.tem_week);
                 ILI9341_Print_Str(112,192,str);
                     break;
                 
                 case 17:
                     /*�������µ���*/
                 if(RCT_Tem_Time.tem_week>1)/*������СֵΪ1*/
                 {
                     RCT_Tem_Time.tem_week--;
                 }   
                 else
                 {
                     RCT_Tem_Time.tem_week = 7;
                 }
                 General_TIM_Delay_ms(50);/*��ֹ�����л�*/
                 sprintf(str,"%02d",RCT_Tem_Time.tem_week);
                 ILI9341_Print_Str(112,192,str);
                     break;
                 
                 default:
                     break;
                 
             }
         }



/**********������жϣ��ж�TCS3472��������ʱ������Լ200ms���Ƿ����㣬�Ҳ���DHT12��ռIIC��Դ***********/       
      if(((SenState&0x01)==0x01))
      {
            SenState &= ~(0x01);/*�����־λ*/ 
            RGB888color = TCS3472_Read_Deal();
            HOST_Send_32bit(RGB888color,0xF5);
            if(Print_Model==3)
            {
                 sprintf(str,"RGB888ֵΪ%#x\n��ɫ����",RGB888color);
                 ILI9341_Line_Print(3,str);
                 RGB565color = RGB888ToRGB565(RGB888color);
                 ILI9341_Drew_Rec(64,0,128,64,RGB565color);
            }
            if(Print_Model==6)
            {
                 sprintf(str,"RGB888ֵΪ%#x\n",RGB888color);
                 ILI9341_Line_Print(4,str);
                 RGB565color = RGB888ToRGB565(RGB888color);
                 ILI9341_Drew_Rec(32,176,96,240,RGB565color);
            }
          
      }	
      
      
/****************�������жϣ��ж��Ƿ�Ҫ�ɼ�MAX6675����*********************/
      if((SenState&0x04)==0x04)
      {
          SenState &= ~(0x04);/*�����־λ*/
          
          maxsoult = MAX6675_DealData(MAX6675_AVE());
          HOST_Send_float(maxsoult,0xF4);/*���ͽ����������λ��*/
          sprintf(str,"�в��¶�Ϊ%.2f��\n",maxsoult);
          if(Print_Model==2)
          {
              
              ILI9341_Line_Print(3,str);
          }
          if(Print_Model==6)
          {
              
              ILI9341_Line_Print(5,str);   
          }
          
          
      }
 

/*��ȡʵʱʱ��*/
    RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
    RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);
/******************���߸��жϣ��ж�ʱ��ֵ�Ƿ��и���*********************/
        if (Rtctmp != RTC_TimeStructure.RTC_Seconds)/*��ֵ�и���*/
        {
            
            sprintf(str,"ʱ�� : %0.2d:%0.2d:%0.2d\n���� : Y:20%0.2d-M:%0.2d-D:%0.2d-W:%0.2d\n",
                    RTC_TimeStructure.RTC_Hours,
                    RTC_TimeStructure.RTC_Minutes,
                    RTC_TimeStructure.RTC_Seconds,
                    RTC_DateStructure.RTC_Year,
                    RTC_DateStructure.RTC_Month,
                    RTC_DateStructure.RTC_Date,
                    RTC_DateStructure.RTC_WeekDay);
            ILI9341_Print_Str(0,0,str);/*��ӡʱ��*/
            
            Rtctmp = RTC_TimeStructure.RTC_Seconds;/*������ʱ����*/
        }


  }
 

}

/*************************************************
Function: SYSTEM_Init
Description: ϵͳ���ó�ʼ��
Input: ��
Output:��
Return: ��
Others: ��
*************************************************/
void SYSTEM_Init(void)
{
    IC_TIM_Init();/*��ʱ����ʼ��*/
    General_TIM_Init();
    
    LED_GPIO_Conf();/*LED���ڼ򵥵���*/
	USART_User_Init();

    W25Q16_SPI_Conf();/*�ⲿFlashӲ��SPI��ʼ��*/
    
    ILI9341_Init();/*Һ������ʼ��*/

    TSC2046_SoftSPI_GPIO_Conf();/*TSC2046�������ģ��SPI��ʼ��*/
    
    IIC_CONF();/*ʹ��ģ��IIC*/
    
    MPU9250_Init();/*MPU9250��ʼ��*/
    TCS3472_Init();/*��ɫ��������ʼ��*/
    MAX6675_SPI_Conf();/*�ȵ�ż�¶ȴ�������ʼ��*/
    RTC_UserInit();/*ʵʱʱ�ӳ�ʼ��*/
     
}
