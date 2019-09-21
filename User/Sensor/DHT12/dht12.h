#ifndef _DHT_12_H_
#define _DHT_12_H_
#include "stm32f4xx.h"

/*�豸��ַ����*/
#define DHT12_DEV_ADDR			0xB8
#define DHT12_DEV_READ_ADDR		0xB9
#define DHT12_DEV_WRITE_ADDR	0xB8

/*BYTE ADDR����*/
#define DHT12_HUM_INT   		0x00    /*ʪ������λ*/
#define DHT12_HUM_DEC			0x01	/*ʪ��С��λ*/
#define DHT12_TEM_INT			0x02	/*�¶�����λ*/
#define DHT12_TEM_DEC			0x03    /*�¶�С��λ*/
#define DHT12_CHECK_SUM			0x04	/*У���*/
/*�Զ��庯��*/
void DHT12_Read_(uint8_t *datasto);
uint8_t DHT12_Deal_Tem_Hum(float* datasto,uint8_t *datasrc);

#endif    /*_DHT_12_H_*/
