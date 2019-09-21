/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.8.0
  * @date    04-November-2016
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */
  
  

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "led.h"
#include "w25q16.h"
#include "tim.h"
#include "usart.h"
//#include "systick.h"
//uint32_t Start_Addr  =   0x1F0000;/*д���ֿ�ʱ�õ����׵�ַ*/

uint8_t SenState = 0;
/*  bit0ΪTCS3475ʱ��״̬��Ϊ1��ʾ�����ϴβ������������趨��ʱ����
    bit1ΪDHT12ʱ��״̬����ֵΪ1ʱ��ʾ�����ϴβ���DHT12�¶��ѹ�ȥ����2��
    bit2ΪMAX6675ʱ��״̬*/

/*���ʱ�����Ӷ��壬���ڶ�ʱ*/
uint16_t times = 0;/*������ͨ��ʱ����*/
uint16_t times1 = 0;/*���ڴ�����ʱ��������*/

/*ң�������벶����ɱ�־����0˵������δ��ɣ���1��ʾ������ɣ���ֵ���жϷ������иı�*/
uint8_t IC_Stase = 0;

/*ң��������ߵ͵�ƽ��־����ֵΪ1��ʾ�ϴβ��������أ�Ϊ0��ʾδ������ϴβ����½���*/
uint8_t IC_LandH = 0;

/*ң��������CNT����*/
uint16_t IC_CNT = 0;

/*ң��״̬,��ֵΪ��ʶ���ܵ���ʼͬ���ź�*/
uint8_t IC_Remote_state = 0;

/*ң��������������*/
uint32_t IC_Remote_Read = 0;

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
    LED_ON_OFF();
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
    LED_ON_OFF();
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/*�����жϷ�����*/
void USART1_IRQHandler(void)
{
    
 
//    uint8_t temp = 0;
//    if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET)
//    {
//        /*�жϴ����Ƿ��н���*/
//        LED_OFF();
//		LED1_ON();
//        
//        temp = USART_ReceiveData(USART_Used);
//        
//        /*д������*/
//        W25Q16_Write_Byte(Start_Addr++,&temp,1);
//      
//        /*����жϱ�־λ*/
//        USART_ClearITPendingBit(USART1,USART_IT_RXNE); 
//    }
	
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
    LED_ON_OFF();
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
    LED_ON_OFF();
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
    LED_ON_OFF();
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
    LED_ON_OFF();
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
    LED_ON_OFF();
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
    LED_ON_OFF();
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
    LED_ON_OFF();
	
}



/*���жϷ���������һ�����ʱ��ÿ1ms����һ���ж�*/
void TIM8_UP_TIM13_IRQHandler(void)
{
    
    /*�ж��ж��Ƿ����*/
    if(TIM_GetITStatus(General_TIM_Used, TIM_IT_Update)==SET)
    {
        times++; 
        times1++;
        
        if(times1%2==0)
        {
            SenState |= 0x01;/*TCS34725֧�ֽϿ칤��*/
        }
        
        if(times1%2000==0)/*DHT12�¶ȴ�����ʱ����2s�㹻*/
        {  
            SenState |= 0x02;
        }
        
        if(times1%100==0)/*�趨MAX6675ʱ����Ϊ500ms���˴�������ȡ̫��ʱ���ݲ�׼*/
        {
            SenState |= 0x04;
        }
        
        if(times1>60000)/*��������*/
        {
            times1 = 0; 
            
        }
        if(times>60000)/*��������*/
        {
            times = 0; 
            
        }
        /*����жϱ�־*/
        TIM_ClearITPendingBit(General_TIM_Used, TIM_IT_Update);
    }
}



/*ң�����õ����жϷ�����*/
void TIM1_BRK_TIM9_IRQHandler(void)
{
   
    if(TIM_GetITStatus(IC_TIM_Used, IC_TIM_ITS) != RESET)/*�ж��Ƿ��в����ж�*/
    {
        
        /*�ж����������жϻ����½����ж�*/
        /*����������*/
        if(IC_LandH == 0)
        {
            
            /*����������ı���ر�־*/       
            TIM_SetCounter(IC_TIM_Used, 0);
            IC_LandH = 1;      
            /*��Ϊ�����½���*/
            TIM_OC1PolarityConfig(IC_TIM_Used, TIM_OCPolarity_Low);
            
        }
        /*�����½���*/
        else if(IC_LandH == 1)
        {
             /*��������*/
           IC_CNT = TIM_GetCapture1(IC_TIM_Used);
            //printf("%d\n",IC_CNT);
            IC_LandH = 0;
 
            /*��Ϊ����������*/
            TIM_OC1PolarityConfig(IC_TIM_Used, TIM_OCPolarity_High);
            
                  /*�ж�ң���ź�����*/
                if(IC_Remote_state==1)/*��ʾ�н��յ�ͬ���ź�*/
                {
                         if((IC_CNT > 25) && (IC_CNT < 55))       /*�߼� 0 �� 560us ��+560us ��*/
                        {
                            
                            IC_Remote_Read <<= 1;
                            IC_Remote_Read |= 0;
                        }else if((IC_CNT > 100) && (IC_CNT < 140))/*�߼� 1 �� 560us ��+1680us ��*/
                        {
                            
                            IC_Remote_Read <<= 1;
                            IC_Remote_Read |= 1;
                        }
                        else if((IC_CNT > 155) && (IC_CNT < 200))/*�����ź�*/
                        {
                            IC_Stase = 1;/*һ���źŴ������*/
                            IC_Remote_state=0;
                        }
                    
                }
                
                       /*��ʾδ�յ�ң���ź�*/
               else if(((IC_CNT > 300) && (IC_CNT < 450)))
                {
                    
                        IC_Remote_state=1;/*��ʾ���յ�ͬ���źţ��״η��͵���9ms�ĵ͵�ƽ���壬�����4.5ms�ĸߵ�ƽ*/
                }
          
        }
         
        TIM_ClearITPendingBit(IC_TIM_Used, IC_TIM_ITS);/*����жϱ�־*/
        
   }
    

    
}
/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
