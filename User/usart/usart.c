#include "usart.h"

/*************************************************
Function: USART_GPIO_Conf
Description: ����USART���GPIO����
Input: ��
Output:��
Return: ��
Others: ��
*************************************************/
void USART_GPIO_Conf(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	/*����GPIOʱ��*/
	RCC_AHB1PeriphClockCmd((USART_RX_GPIO_RCC|USART_TX_GPIO_RCC), ENABLE);
	
	/*����TX*/
	/*���ø���ģʽ*/
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = USART_TX_GPIOPin;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USART_TX_GPIOPort,&GPIO_InitStruct);
	
	/*����RX*/
	/*���ø���ģʽ*/
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = USART_RX_GPIOPin;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USART_RX_GPIOPort,&GPIO_InitStruct);
	
	/*ѡ��GPIO���ù���*/
	GPIO_PinAFConfig(USART_RX_GPIOPort,USART_RX_PinSource,USART_AF_FUNCTION);
	GPIO_PinAFConfig(USART_TX_GPIOPort,USART_TX_PinSource,USART_AF_FUNCTION);
	
}

/*************************************************
Function: USART_Conf
Description: ����USART��ز���
Input: ��
Output:��
Return: ��
Others: ��
*************************************************/
void USART_Conf(void)
{
	USART_InitTypeDef USART_InitStruct;
	
	/*����USARTʱ��*/
	USART_RCC_Cmd_FUNCTION(USART_RCC_FUNCTION_PARA,ENABLE);
	
	/*������ز���*/
	/*
    ��W25Q16д���ֿ��ļ�ʱ�ٶ�̫�쵼����ģ���ݶ�ʧ��
    �˴�Ӧ���Ͳ�����Ϊ19200*/
	USART_InitStruct.USART_BaudRate =115200;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = (USART_Mode_Rx|USART_Mode_Tx);
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART_Used,&USART_InitStruct);
	
}


/*************************************************
Function: USART_User_Init
Description: Usart��ʼ��
Input: ��
Output:��
Return: ��
Others: ��
*************************************************/
void USART_User_Init(void)
{
	/*�����ж����ȼ�������ʱע�͵�����*/
//	USART_NVIC_Conf();
	
	USART_GPIO_Conf();
	USART_Conf();
	
	/*�ж����󣬲���ʱע�͵�����*/
//	USART_ITConfig(USART_Used,USART_IT_RXNE, ENABLE);
	
	/*ʹ��USART*/
	USART_Cmd(USART_Used,ENABLE);
	
	/*�ֶ����TC��־λ*/
	USART_ClearFlag(USART_Used, USART_FLAG_TC);
}


/*************************************************
Function: USART_Send_Byte
Description: ͨ�����ڷ���һ����λ����
Input: dataΪ����
Output: ��
Return: ��
Others: �� 
*************************************************/
void USART_Send_Byte(uint8_t data)
{
	USART_SendData(USART_Used,data);
	
	/*�ȴ��������*/
	while(USART_GetFlagStatus(USART_Used, USART_FLAG_TXE)==0);
}

/*************************************************
Function: USART_Send_NByte
Description: ͨ�����ڷ��Ͷ����λ����
Input: dataΪ���ݣ�NumΪ���ݸ���
Output: ��
Return: ��
Others: �� 
*************************************************/
void USART_Send_NByte(uint8_t *data,uint8_t Num)
{
    uint8_t i = 0;
    for(i = 0;i < Num;i++)
    {
        USART_Send_Byte(data[i]);
    }
}

/*************************************************
Function: USART_Receive_Byte
Description: ͨ�����ڽ���һ����λ����
Input:��
Output: ���յ�������
Return: ��
Others: �� 
*************************************************/
uint8_t USART_Receive_Byte(void)
{
	uint8_t temp;
	while(USART_GetFlagStatus(USART_Used, USART_FLAG_RXNE)==0);
	temp = (uint8_t)(USART_ReceiveData(USART_Used)&0xFF);
	return temp;
}


/*************************************************
Function: USART_NVIC_Conf
Description: ����USART�������ж����ȼ�
Input: ��
Output:��
Return: ��
Others: ��
*************************************************/
void USART_NVIC_Conf(void)
{
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStruct.NVIC_IRQChannel = USART_IRQ_Channel;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
}
