#ifndef _MPU9250_H_
#define _MPU9250_H_
#include "stm32f4xx.h"
#include "iic.h"
#include "tim.h"
#include "w25q16.h"


/* ����ǶȽṹ�����Ͷ��� */
typedef struct Angle
{
    double Angle_X;
    double Angle_Y;
    double Angle_Z;
} MPU9250_Angle;


/*һЩ���ݶ���*/
#define DEG_to_RAD 57.29577f     /*1���� = 57.29577�Ƕ�*/
#define RAD_to_DEG 0.0174533f    /*1�Ƕ� = 0.0174533����*/

/*�豸��ַ���壬������AD0�˿ڽӵأ��ʵ�ַ����*/
#define MPU9250_DEVICE_ADDR     0x68  
#define MPU9250_READ_ADDR      ((MPU9250_DEVICE_ADDR<<1)|0x01) 
#define MPU9250_WRITE_ADDR     ((MPU9250_DEVICE_ADDR<<1)|0x00)

/*MPU9250�Ĵ�����ַ����*/
#define MPU9250_CONF_REG                            0x1A/*�������ֵ�ͨ�˲������ⲿSYNC*/
#define MPU9250_GYRO_CONF_REG                       0x1B/*�����������Լ������*/
#define MPU9250_ACC_CONF1_REG                       0x1C/*���ü��ٶȼ��Լ������*/
#define MPU9250_ACC_CONF2_REG                       0x1D/*FCHOICE�����ֵ�ͨ�˲�*/
#define MPU9250_PWR_MNG_REG                         0x6B/*��Դ����*/
#define MPU9250_SMPLRT_DIV_REG                      0x19/*SAMPLE_RATE = Internal_Sample_Rate / (1 + SMPLRT_DIV)*/

#define MPU9250_ACCEL_YOUT_H                        0x3D
#define MPU9250_ACCEL_YOUT_L                        0x3E

/*w25q16��ַ���壬���ڴ洢У������*/
#define MPU9250_ACC_YOFFSET_ARRD                     0x1EFF02

/*�û��Զ��庯��*/
void MPU9250_Init(void);

/*��д���*/
void MPU9250_Write(uint8_t Addr,uint8_t* data,uint8_t num);
void MPU9250_Read(uint8_t Addr,uint8_t *datasto,uint8_t num);
void MPU9250_Write_Byte(uint8_t Addr,uint8_t data);
void MPU9250_Read_Accel(uint8_t* datasto);
int16_t MPU9250_Cal_Accel(void);
void MPU9250_Offset(void);
void MPU9250_Get_Angle(MPU9250_Angle *data);
int16_t MPU9250_filter(void);

#endif
