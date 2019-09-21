#ifndef _LED_H_
#define _LED_H_
#include "stm32f4xx.h"

/*GPIO�˿ڼ����Ŷ���*/
#define LED1_GPIO_Port 			GPIOF
#define LED1_GPIO_Pin			GPIO_Pin_9

#define LED2_GPIO_Port 			GPIOF
#define LED2_GPIO_Pin			GPIO_Pin_10

/*������������*/
#define LED1_RCC_Periph 		RCC_AHB1Periph_GPIOF
#define LED2_RCC_Periph 		RCC_AHB1Periph_GPIOF



/*�û��Զ��庯��*/
void LED_GPIO_Conf(void);
void LED_OFF(void);
void LED2_ON(void);
void LED1_ON(void);
void LED_ON_OFF(void);





#endif
