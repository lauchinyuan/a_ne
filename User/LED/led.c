#include "led.h"
#include "tim.h"

/*************************************************
Function: LED_GPIO_Conf
Description: ����LED���GPIO
Input: ��
Output:��
Return: ��
Others: ��
*************************************************/
void LED_GPIO_Conf(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_AHB1PeriphClockCmd(LED1_RCC_Periph,ENABLE);/*����GPIOʱ��*/
	RCC_AHB1PeriphClockCmd(LED2_RCC_Periph,ENABLE);
	
	/*����GPIO��ز�����������LED1*/
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = LED1_GPIO_Pin;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;

	GPIO_Init(LED1_GPIO_Port,&GPIO_InitStruct);
	
	/*����LED2*/
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = LED2_GPIO_Pin;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
	
	GPIO_Init(LED2_GPIO_Port,&GPIO_InitStruct);

	LED_OFF();/*Ĭ�Ϲص�*/
}


/*************************************************
Function: LED_OFF
Description: Ϩ������LED
Input: ��
Output:��
Return: ��
Others: ��
*************************************************/
void LED_OFF(void)
{
	GPIO_SetBits(LED2_GPIO_Port,LED2_GPIO_Pin);
	GPIO_SetBits(LED1_GPIO_Port,LED1_GPIO_Pin);
}


/*************************************************
Function: LED2_ON
Description: ����LED2
Input: ��
Output:��
Return: ��
Others: ��
*************************************************/
void LED2_ON(void)
{
	GPIO_ResetBits(LED2_GPIO_Port, LED2_GPIO_Pin);
}
	
/*************************************************
Function: LED1_ON
Description: ����LED1
Input: ��
Output:��
Return: ��
Others: ��
*************************************************/
void LED1_ON(void)
{
	GPIO_ResetBits(LED1_GPIO_Port, LED1_GPIO_Pin);
}


/*************************************************
Function: LED_ON_OFF
Description: LED��˸
Input: ��
Output:��
Return: ��
Others: ��
*************************************************/
void LED_ON_OFF(void)
{
      while (1)
  {
      LED_OFF();
      General_TIM_Delay_ms(200);
      LED1_ON();
      LED2_ON();
      General_TIM_Delay_ms(200);
      
  }
    
}

