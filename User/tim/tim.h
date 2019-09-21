#ifndef  _TIM_H_
#define  _TIM_H_
#include "stm32f4xx.h"

/*���ļ���ͨ�ö�ʱ��13������ʱ������
ͨ�ö�ʱ��9����ң�������źŵ����벶��*/


/*ͨ�ö�ʱ����ض���*/
#define General_TIM_Used            TIM13
#define General_TIM_IRQ_Channel     TIM8_UP_TIM13_IRQn

#define General_TIM_Clock_Cmd       RCC_APB1PeriphClockCmd
#define General_TIM_RCC             RCC_APB1Periph_TIM13

/*���벶��ʱ����ض���*/
#define IC_TIM_Used            TIM9
#define IC_TIM_IRQ_Channel     TIM1_BRK_TIM9_IRQn

#define IC_TIM_Clock_Cmd       RCC_APB2PeriphClockCmd
#define IC_TIM_RCC             RCC_APB2Periph_TIM9

#define IC_TIM_GPIOPort        GPIOE
#define IC_TIM_GPIOPin         GPIO_Pin_5
#define IC_TIM_GPIO_RCC        RCC_AHB1Periph_GPIOE
#define IC_TIM_GPIO_Pinsource  GPIO_PinSource5
#define IC_TIM_GPIO_AF         GPIO_AF_TIM9
#define IC_TIM_Channel         TIM_Channel_1
#define IC_TIM_ITS             TIM_IT_CC1

/*�����궨��*/

/*���ü���Ƶ��Ϊ10000HZ*/

/*���ڹ���δ���� system_stm32f4xx.c��PLL_M�е�ֵ��ϵͳʱ�Ӳ���168MHZ���ʴ˴�ֵ��Ϊ16800-1*/
#define General_TIM_Prescaler_Used  (2800-1)
#define IC_TIM_Prescaler_Used       (700-1)


/*һ�㶨ʱʵ�ֺ��뼶��ʱ���ö�ʱ��ÿһ�������һ�θ����ж�*/
#define General_TIM_Period_Used     (10-1)

/*����ʱ�����ʱ��Ϊ10ms*/
#define IC_TIM_Period_Used          (1000-1)

/*�û��Զ��庯��*/
void General_TIM_Conf(void);
void General_TIM_NVIC_Conf(void);
void General_TIM_Init(void);
void General_TIM_Delay_ms(uint16_t n);
void IC_TIM_GPIO_Conf(void);
void IC_TIM_NVIC_Conf(void);
void IC_TIM_Conf(void);
void IC_TIM_Init(void);

#endif
