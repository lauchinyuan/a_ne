#include "fsmc.h"
/*************************************************
Function: FSMC_GPIO_Conf
Description: ����FSMC�õ���GPIO
Input: ��
Output:��
Return: ��
Others: ��
*************************************************/
void FSMC_GPIO_Conf(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	/*����GPIOʱ��*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOE|
							RCC_AHB1Periph_GPIOF|RCC_AHB1Periph_GPIOG,ENABLE);
	/*����FSMC_D0*/
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin = FSMC_D0_Pin;
	GPIO_Init(FSMC_D0_Port, &GPIO_InitStruct);
	GPIO_PinAFConfig(FSMC_D0_Port,FSMC_D0_PinSource, FSMC_AF);
	
	/*����FSMC_D1*/
	GPIO_InitStruct.GPIO_Pin = FSMC_D1_Pin;
	GPIO_Init(FSMC_D1_Port, &GPIO_InitStruct);
	GPIO_PinAFConfig(FSMC_D1_Port,FSMC_D1_PinSource, FSMC_AF);
	
	
	/*����FSMC_D2*/
	GPIO_InitStruct.GPIO_Pin = FSMC_D2_Pin;
	GPIO_Init(FSMC_D2_Port, &GPIO_InitStruct);
	GPIO_PinAFConfig(FSMC_D2_Port,FSMC_D2_PinSource, FSMC_AF);
	
	
	/*����FSMC_D3*/
	GPIO_InitStruct.GPIO_Pin = FSMC_D3_Pin;
	GPIO_Init(FSMC_D3_Port, &GPIO_InitStruct);
	GPIO_PinAFConfig(FSMC_D3_Port,FSMC_D3_PinSource, FSMC_AF);
	
	
	/*����FSMC_D4*/
	GPIO_InitStruct.GPIO_Pin = FSMC_D4_Pin;
	GPIO_Init(FSMC_D4_Port, &GPIO_InitStruct);
	GPIO_PinAFConfig(FSMC_D4_Port,FSMC_D4_PinSource, FSMC_AF);
	
	
	/*����FSMC_D5*/
	GPIO_InitStruct.GPIO_Pin = FSMC_D5_Pin;
	GPIO_Init(FSMC_D5_Port, &GPIO_InitStruct);
	GPIO_PinAFConfig(FSMC_D5_Port,FSMC_D5_PinSource, FSMC_AF);

	/*����FSMC_D6*/
	GPIO_InitStruct.GPIO_Pin = FSMC_D6_Pin;
	GPIO_Init(FSMC_D6_Port, &GPIO_InitStruct);
	GPIO_PinAFConfig(FSMC_D6_Port,FSMC_D6_PinSource, FSMC_AF);

	/*����FSMC_D7*/
	GPIO_InitStruct.GPIO_Pin = FSMC_D7_Pin;
	GPIO_Init(FSMC_D7_Port, &GPIO_InitStruct);
	GPIO_PinAFConfig(FSMC_D7_Port,FSMC_D7_PinSource, FSMC_AF);
	
	/*����FSMC_D8*/
	GPIO_InitStruct.GPIO_Pin = FSMC_D8_Pin;
	GPIO_Init(FSMC_D8_Port, &GPIO_InitStruct);
	GPIO_PinAFConfig(FSMC_D8_Port,FSMC_D8_PinSource, FSMC_AF);
	
	
	/*����FSMC_D9*/
	GPIO_InitStruct.GPIO_Pin = FSMC_D9_Pin;
	GPIO_Init(FSMC_D9_Port, &GPIO_InitStruct);
	GPIO_PinAFConfig(FSMC_D9_Port,FSMC_D9_PinSource, FSMC_AF);
	
	
	/*����FSMC_D10*/
	GPIO_InitStruct.GPIO_Pin = FSMC_D10_Pin;
	GPIO_Init(FSMC_D10_Port, &GPIO_InitStruct);
	GPIO_PinAFConfig(FSMC_D10_Port,FSMC_D10_PinSource, FSMC_AF);
	
	
	/*����FSMC_D11*/
	GPIO_InitStruct.GPIO_Pin = FSMC_D11_Pin;
	GPIO_Init(FSMC_D11_Port, &GPIO_InitStruct);
	GPIO_PinAFConfig(FSMC_D11_Port,FSMC_D11_PinSource, FSMC_AF);
	
	
	/*����FSMC_D12*/
	GPIO_InitStruct.GPIO_Pin = FSMC_D12_Pin;
	GPIO_Init(FSMC_D12_Port, &GPIO_InitStruct);
	GPIO_PinAFConfig(FSMC_D12_Port,FSMC_D12_PinSource, FSMC_AF);
	
	
	/*����FSMC_D13*/
	GPIO_InitStruct.GPIO_Pin = FSMC_D13_Pin;
	GPIO_Init(FSMC_D13_Port, &GPIO_InitStruct);
	GPIO_PinAFConfig(FSMC_D13_Port,FSMC_D13_PinSource, FSMC_AF);
	
	
	/*����FSMC_D14*/
	GPIO_InitStruct.GPIO_Pin = FSMC_D14_Pin;
	GPIO_Init(FSMC_D14_Port, &GPIO_InitStruct);
	GPIO_PinAFConfig(FSMC_D14_Port,FSMC_D14_PinSource, FSMC_AF);
	
	
	/*����FSMC_D15*/
	GPIO_InitStruct.GPIO_Pin = FSMC_D15_Pin;
	GPIO_Init(FSMC_D15_Port, &GPIO_InitStruct);
	GPIO_PinAFConfig(FSMC_D15_Port,FSMC_D15_PinSource, FSMC_AF);
	
	/*����FSMC_A6*/
	GPIO_InitStruct.GPIO_Pin = FSMC_A6_Pin;
	GPIO_Init(FSMC_A6_Port, &GPIO_InitStruct);
	GPIO_PinAFConfig(FSMC_A6_Port,FSMC_A6_PinSource, FSMC_AF);
	
	/*����FSMC_NWE*/
	GPIO_InitStruct.GPIO_Pin = FSMC_NWE_Pin;
	GPIO_Init(FSMC_NWE_Port, &GPIO_InitStruct);
	GPIO_PinAFConfig(FSMC_NWE_Port,FSMC_NWE_PinSource, FSMC_AF);
	
	/*����FSMC_NOE*/
	GPIO_InitStruct.GPIO_Pin = FSMC_NOE_Pin;
	GPIO_Init(FSMC_NOE_Port, &GPIO_InitStruct);
	GPIO_PinAFConfig(FSMC_NOE_Port,FSMC_NOE_PinSource, FSMC_AF);
	
	/*����FSMC_NE4*/
	GPIO_InitStruct.GPIO_Pin = FSMC_NE4_Pin;
	GPIO_Init(FSMC_NE4_Port, &GPIO_InitStruct);
	GPIO_PinAFConfig(FSMC_NE4_Port,FSMC_NE4_Pinsource, FSMC_AF);
	
}

/*************************************************
Function: FSMC_Conf
Description: ��������Һ����ʾ����FSMC
Input: ��
Output:��
Return: ��
Others: ��
*************************************************/
void FSMC_Conf(void)
{
	/*�˴�����FSMC����NOR FLASH��ʱ���LCD��ʾ�����в���*/
	FSMC_NORSRAMTimingInitTypeDef FSMC_TimingInitStruct;
	FSMC_NORSRAMInitTypeDef FSMC_InitStruct;
	
	/*��������*/
	FSMC_GPIO_Conf();
	
	/*����FSMCʱ��*/
	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);
	
	/*����Timeing�ṹ���Աֵ*/
	
	/*ʹ��ģʽB����LCD*/
	FSMC_TimingInitStruct.FSMC_AccessMode = FSMC_AccessMode_B;
	
	/*��ַ����ʱ�䣬��ӦLCD��ʾ����ֵ��5��HCLKʱ�����ڣ�*/
	FSMC_TimingInitStruct.FSMC_AddressSetupTime = 0x04;
	/*���ݽ���ʱ�䣬��ӦLCD��ʾ����ֵ��5��HCLKʱ�����ڣ�*/
	FSMC_TimingInitStruct.FSMC_DataSetupTime = 0x04;
	
	
	/*�����첽ģʽ��δ�õ�*/
	FSMC_TimingInitStruct.FSMC_AddressHoldTime = 0x00;
	FSMC_TimingInitStruct.FSMC_BusTurnAroundDuration = 0x00;
	FSMC_TimingInitStruct.FSMC_CLKDivision = 0x00;
	FSMC_TimingInitStruct.FSMC_DataLatency = 0x00;
	
	/*�ṹ��д����ɣ���ʼ���ó�ʼ���ṹ���ֵ*/
	FSMC_InitStruct.FSMC_Bank = FSMC_Bank1_NORSRAMx;
	FSMC_InitStruct.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
	FSMC_InitStruct.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
	FSMC_InitStruct.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
	FSMC_InitStruct.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
	FSMC_InitStruct.FSMC_MemoryType = FSMC_MemoryType_NOR;
	FSMC_InitStruct.FSMC_ReadWriteTimingStruct = &FSMC_TimingInitStruct;
	FSMC_InitStruct.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
	FSMC_InitStruct.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
	FSMC_InitStruct.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	FSMC_InitStruct.FSMC_WrapMode = FSMC_WrapMode_Disable;
	FSMC_InitStruct.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
	FSMC_InitStruct.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
	FSMC_InitStruct.FSMC_WriteTimingStruct = &FSMC_TimingInitStruct;
	FSMC_NORSRAMInit(&FSMC_InitStruct);
	
	/*ʹ��FSMC*/
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAMx,ENABLE);
	
}




