#ifndef _FSMC_H_
#define _FSMC_H_
#include "stm32f4xx.h"

/*���Ŷ���*/
/********�����ź���***************/   
#define      FSMC_D0_Port               GPIOD
#define      FSMC_D0_Pin                GPIO_Pin_14
#define      FSMC_D0_PinSource          GPIO_PinSource14

#define      FSMC_D1_Port               GPIOD
#define      FSMC_D1_Pin                GPIO_Pin_15
#define      FSMC_D1_PinSource          GPIO_PinSource15
 
#define      FSMC_D2_Port               GPIOD
#define      FSMC_D2_Pin                GPIO_Pin_0
#define      FSMC_D2_PinSource          GPIO_PinSource0
  
#define      FSMC_D3_Port               GPIOD
#define      FSMC_D3_Pin                GPIO_Pin_1
#define      FSMC_D3_PinSource          GPIO_PinSource1
   
#define      FSMC_D4_Port               GPIOE
#define      FSMC_D4_Pin                GPIO_Pin_7
#define      FSMC_D4_PinSource          GPIO_PinSource7
   
#define      FSMC_D5_Port               GPIOE
#define      FSMC_D5_Pin                GPIO_Pin_8
#define      FSMC_D5_PinSource          GPIO_PinSource8
  
#define      FSMC_D6_Port               GPIOE
#define      FSMC_D6_Pin                GPIO_Pin_9
#define      FSMC_D6_PinSource          GPIO_PinSource9

#define      FSMC_D7_Port               GPIOE
#define      FSMC_D7_Pin                GPIO_Pin_10
#define      FSMC_D7_PinSource          GPIO_PinSource10

#define      FSMC_D8_Port               GPIOE
#define      FSMC_D8_Pin                GPIO_Pin_11
#define      FSMC_D8_PinSource          GPIO_PinSource11

#define      FSMC_D9_Port               GPIOE
#define      FSMC_D9_Pin                GPIO_Pin_12
#define      FSMC_D9_PinSource          GPIO_PinSource12
  
#define      FSMC_D10_Port               GPIOE
#define      FSMC_D10_Pin                GPIO_Pin_13
#define      FSMC_D10_PinSource          GPIO_PinSource13
   
#define      FSMC_D11_Port               GPIOE
#define      FSMC_D11_Pin                GPIO_Pin_14
#define      FSMC_D11_PinSource          GPIO_PinSource14
   
#define      FSMC_D12_Port               GPIOE
#define      FSMC_D12_Pin                GPIO_Pin_15
#define      FSMC_D12_PinSource          GPIO_PinSource15
   
#define      FSMC_D13_Port               GPIOD
#define      FSMC_D13_Pin                GPIO_Pin_8
#define      FSMC_D13_PinSource          GPIO_PinSource8
   
#define      FSMC_D14_Port               GPIOD
#define      FSMC_D14_Pin                GPIO_Pin_9
#define      FSMC_D14_PinSource          GPIO_PinSource9
   
#define      FSMC_D15_Port               GPIOD
#define      FSMC_D15_Pin                GPIO_Pin_10
#define      FSMC_D15_PinSource          GPIO_PinSource10

/********����FSMC���Ŷ���***************/
#define      FSMC_AF                    GPIO_AF_FSMC


/*ȷ��FSMC�ĵ�ַ�źſ����ߣ������ž����˷���LCDʱʹ�õĵ�ַ*/
/*PF0ΪFSMC_A0���ܽ�Ϊ����ȷ������λ������λ*/  
#define      FSMC_A6_Port                GPIOF
#define      FSMC_A6_Pin                 GPIO_Pin_12
#define      FSMC_A6_PinSource           GPIO_PinSource12
  
#define      FSMC_NWE_Port               GPIOD
#define      FSMC_NWE_Pin                GPIO_Pin_5
#define      FSMC_NWE_PinSource          GPIO_PinSource5
  
#define      FSMC_NOE_Port               GPIOD
#define      FSMC_NOE_Pin                GPIO_Pin_4
#define      FSMC_NOE_PinSource          GPIO_PinSource4

/*�˴���NE4��ΪƬѡ*/				
#define 	 FSMC_NE4_Port				 GPIOG
#define      FSMC_NE4_Pin				 GPIO_Pin_12
#define 	 FSMC_NE4_Pinsource			 GPIO_PinSource12

/*��Ƭѡ���ž�����NOR/SRAM�飬�˴�STM32F407�������ӵ�ΪFSMC_NE4���ţ���NOR��ΪFSMC_Bank1_NORSRAM4*/
#define      FSMC_Bank1_NORSRAMx         FSMC_Bank1_NORSRAM4




/*�û��Զ��庯��*/
void FSMC_GPIO_Conf(void);
void FSMC_Conf(void);



#endif
