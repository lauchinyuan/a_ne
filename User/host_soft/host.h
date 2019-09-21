#ifndef _HOST_H_
#define _HOST_H_
#include "stm32f4xx.h"
#include "usart.h"

/*��λ��Э����ض���*/
#define BYTE0(Temp)       (*(int8_t *)(&Temp))       /*ȡ�������ĵ��ֽ�*/
#define BYTE1(Temp)       (*((int8_t *)(&Temp) + 1)) /*ȡ�洢�ڴ˱�����һ�ڴ��ֽڵ����ݣ������ֽڣ�����ͬ��*/
#define BYTE2(Temp)       (*((int8_t *)(&Temp) + 2))
#define BYTE3(Temp)       (*((int8_t *)(&Temp) + 3))


/*�û��Զ��庯��*/
//void HOST_Send_MPU_Data(int16_t* MPUdata);
void HOST_Send_float(float data,uint8_t fun);
void HOST_Send_32bit(uint32_t data,uint8_t fun);

#endif
