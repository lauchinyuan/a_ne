#include "host.h"

/*************************************************
Function: HOST_Send_float
Description: ���͵������������ݵ�������λ��
Input: dataΪ���������ݣ�funΪָ�������֣���������ͬ����֡
Output: ��
Return: ��
Others: �� 
*************************************************/
void HOST_Send_float(float data,uint8_t fun)
{
    uint8_t sum = 0;/*У���*/
	uint8_t i = 0;
	uint8_t cnt = 0;
    unsigned char *p;
    uint8_t data_to_send[23] = {0};/*�˴���Ҫʱ������ռ�*/
	
	data_to_send[cnt++]=0xAA;/*֡ͷΪ0xAAAA*/
	data_to_send[cnt++]=0xAA;
    
	data_to_send[cnt++]=fun;/*�����֣�������յ���������*/
    
	data_to_send[cnt++]=0;/*��Ҫ�������ݵ��ֽ�������ʱ��0��������������������ٸ�ֵ*/
	
    p=(unsigned char *)&data;/*flot����ռ��4���ֽ�*/
    data_to_send[cnt++]=(unsigned char)(*(p+3));
    data_to_send[cnt++]=(unsigned char)(*(p+2));
    data_to_send[cnt++]=(unsigned char)(*(p+1));
    data_to_send[cnt++]=(unsigned char)(*(p+0));
	
	data_to_send[3] = cnt-4;/*�������ֽڸ�������ֵ������֡����λ*/
	
	for(i=0;i<cnt;i++)/*����У���*/
    {
        sum += data_to_send[i];
    }
		
	data_to_send[cnt++] = sum;/*���һλ��У��λ*/
	
    USART_Send_NByte(data_to_send, cnt);/*ʹ�ô��ڷ�������*/

}


/*************************************************
Function: HOST_Send_32bit
Description: ���͵���32λ���ݵ�������λ��
Input:  dataΪ32λ����,funΪָ�������֣���������ͬ����֡
Output: ��
Return: RGB888����
Others: �� 
*************************************************/
void HOST_Send_32bit(uint32_t data,uint8_t fun)
{
    uint8_t sum = 0;/*У���*/
	uint8_t i = 0;
	uint8_t cnt = 0;
    unsigned char *p;
    uint8_t data_to_send[23] = {0};/*�˴���Ҫʱ������ռ�*/
	
	data_to_send[cnt++]=0xAA;/*֡ͷΪ0xAAAA*/
	data_to_send[cnt++]=0xAA;
    
	data_to_send[cnt++]=fun;/*�����֣�������յ���������*/
    
	data_to_send[cnt++]=0;/*��Ҫ�������ݵ��ֽ�������ʱ��0��������������������ٸ�ֵ*/
	
    p=(unsigned char *)&data;/*32λ����ռ��4���ֽ�*/
    data_to_send[cnt++]=(unsigned char)(*(p+3));
    data_to_send[cnt++]=(unsigned char)(*(p+2));
    data_to_send[cnt++]=(unsigned char)(*(p+1));
    data_to_send[cnt++]=(unsigned char)(*(p+0));
	
	data_to_send[3] = cnt-4;/*�������ֽڸ�������ֵ������֡����λ*/
	
	for(i=0;i<cnt;i++)/*����У���*/
    {
        sum += data_to_send[i];
    }
		
	data_to_send[cnt++] = sum;/*���һλ��У��λ*/
	
    USART_Send_NByte(data_to_send, cnt);/*ʹ�ô��ڷ�������*/
}



