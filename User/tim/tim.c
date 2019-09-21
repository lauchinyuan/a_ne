#include  "tim.h"

/*���жϷ������и��µı��������ڼƴ�*/
extern uint16_t times;

/*************************************************
Function: General_TIM_Conf
Description: ����ͨ�ö�ʱ���ж����ȼ�
Input:��
Output:��
Return: ��
Others: ��ͨ�ö�ʱ��������ʱ�����ʱ��
*************************************************/
void General_TIM_NVIC_Conf(void)
{
    NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStruct.NVIC_IRQChannel = General_TIM_IRQ_Channel;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
}

/*************************************************
Function: General_TIM_Conf
Description: ����ͨ�ö�ʱ��
Input:��
Output:��
Return: ��
Others: ��
*************************************************/
void General_TIM_Conf(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;
    
    /*����TIMʱ��*/
    General_TIM_Clock_Cmd(General_TIM_RCC,ENABLE);
    
    /*��������*/
    TIM_TimeBaseInitStruct.TIM_Prescaler = General_TIM_Prescaler_Used;/*Ԥ��Ƶ����*/
    TIM_TimeBaseInitStruct.TIM_Period = General_TIM_Period_Used;/*��������*/
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
    TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
     
    TIM_TimeBaseInit(General_TIM_Used, &TIM_TimeBaseInitStruct);
    
}



/*************************************************
Function: General_TIM_Init
Description: ͨ�ö�ʱ����ʼ��
Input: ��
Output:��
Return: ��
Others: ��
*************************************************/
void General_TIM_Init(void)
{
    General_TIM_NVIC_Conf();
    
    /*��ʱ����������*/
    General_TIM_Conf();
    
    TIM_ITConfig(General_TIM_Used, TIM_IT_Update, ENABLE);
    
    /*ʹ�ܶ�ʱ��*/
    TIM_Cmd(General_TIM_Used, ENABLE);
    
    /*��ʼʱ����жϱ�־*/
    TIM_ClearITPendingBit(General_TIM_Used, TIM_IT_Update);
    
}

/*************************************************
Function: General_TIM_Delay_ms
Description: ʹ��ͨ�ö�ʱ�����к��뼶��ʱ
Input: nΪ��ʱ������
Output:��
Return: ��
Others: ��
*************************************************/
void General_TIM_Delay_ms(uint16_t n)
{
    times = 0;/*�Ƚ�times����*/
    while(times<n)
    {
        /*timeÿ1ms�Լ�һ�Σ�����������С��nʱ���ȴ�*/
    }   
}


/*************************************************
Function: IC_TIM_GPIO_Conf
Description: ���벶��ʱ��GPIO��ʼ��
Input: ��
Output:��
Return: ��
Others: ��
*************************************************/
void IC_TIM_GPIO_Conf(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
	/*����GPIOʱ��*/ 
	RCC_AHB1PeriphClockCmd(IC_TIM_GPIO_RCC,ENABLE); 
	
	/*����GPIO��ز���*/
	GPIO_InitStructure.GPIO_Pin = IC_TIM_GPIOPin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(IC_TIM_GPIOPort,&GPIO_InitStructure);
    
    /*���ù�������*/
    GPIO_PinAFConfig(IC_TIM_GPIOPort,IC_TIM_GPIO_Pinsource,IC_TIM_GPIO_AF); 
    
}


/*************************************************
Function: IC_TIM_NVIC_Conf
Description: �������벶��ʱ���ж����ȼ�
Input:  ��
Output: ��
Return: ��
Others: ��
*************************************************/
void IC_TIM_NVIC_Conf(void)
{
    NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStruct.NVIC_IRQChannel = IC_TIM_IRQ_Channel;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;/*���벶���ж����ȼ���Ϊ���*/
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStruct);
}


/*************************************************
Function: IC_TIM_Conf
Description: �������벶��ʱ��
Input:��
Output:��
Return: ��
Others: ��
*************************************************/
void IC_TIM_Conf(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;
    TIM_ICInitTypeDef  TIM_ICInitStructure;
    
    /*����TIMʱ��*/
    IC_TIM_Clock_Cmd(IC_TIM_RCC,ENABLE);
    
    /*����ʱ���������*/
    TIM_TimeBaseInitStruct.TIM_Prescaler = IC_TIM_Prescaler_Used;
    TIM_TimeBaseInitStruct.TIM_Period = IC_TIM_Period_Used;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;/*���ϼ���*/
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;/*��ʹ���ظ�����*/
    TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_TimeBaseInit(IC_TIM_Used, &TIM_TimeBaseInitStruct);
    
    /*���벶������*/
    TIM_ICInitStructure.TIM_Channel = IC_TIM_Channel;
    TIM_ICInitStructure.TIM_ICFilter = 0x03;      /*8����ʱ��ʱ�������˲��������ɼ�8�ζ��Ǹߵ�ƽ����Ч*/
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;/*���β���������*/
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;/*ûһ�����ض�Ҫ���*/
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;/*ֱ��ģʽ*/
    TIM_ICInit(IC_TIM_Used, &TIM_ICInitStructure);
    
    
}

/*************************************************
Function: IC_TIM_Init
Description: ���벶��ʱ����ʼ��
Input: ��
Output:��
Return: ��
Others: ��
*************************************************/
void IC_TIM_Init(void)
{
   
    IC_TIM_NVIC_Conf();/*�����ж����ȼ�*/
    
    IC_TIM_GPIO_Conf();/*�˿�����*/
        
    IC_TIM_Conf();/*��ʱ����������*/
    
    TIM_ITConfig(IC_TIM_Used, IC_TIM_ITS, ENABLE);/*�ж�����*/

    TIM_Cmd(IC_TIM_Used,ENABLE);/*ʹ�ܶ�ʱ��*/
      
    TIM_ClearITPendingBit(IC_TIM_Used, TIM_IT_Update);/*��ʼʱ����жϱ�־*/
    
}


