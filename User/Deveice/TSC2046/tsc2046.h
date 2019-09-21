#ifndef _TSC2046_H_
#define _TSC2046_H_
#include "stm32f4xx.h"
#include "ili9341.h"
#include "tim.h"
#include "w25q16.h"

/*�����������*/
#define TSC2046_CS_Port                 GPIOC
#define TSC2046_CS_Pin                  GPIO_Pin_13

#define TSC2046_MISO_Port               GPIOB
#define TSC2046_MISO_Pin                GPIO_Pin_2

#define TSC2046_MOSI_Port               GPIOF
#define TSC2046_MOSI_Pin                GPIO_Pin_11

#define TSC2046_SCK_Port                GPIOB
#define TSC2046_SCK_Pin                 GPIO_Pin_0

#define TSC2046_PEN_Port                GPIOB
#define TSC2046_PEN_Pin                 GPIO_Pin_1

#define TSC2046_RCC_CLOCK               (RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOF|RCC_AHB1Periph_GPIOC)



/*���Ÿߵ͵�ƽ����*/
#define TSC_2046_CS_Hight               GPIO_SetBits(TSC2046_CS_Port,TSC2046_CS_Pin)
#define TCS_2046_CS_Low                 GPIO_ResetBits(TSC2046_CS_Port,TSC2046_CS_Pin)

#define TCS_2046_MOSI_Hight             GPIO_SetBits(TSC2046_MOSI_Port,TSC2046_MOSI_Pin)
#define TCS_2046_MOSI_Low               GPIO_ResetBits(TSC2046_MOSI_Port,TSC2046_MOSI_Pin)

#define TCS_2046_SCK_Hight              GPIO_SetBits(TSC2046_SCK_Port,TSC2046_SCK_Pin)
#define TCS_2046_SCK_Low                GPIO_ResetBits(TSC2046_SCK_Port,TSC2046_SCK_Pin)

/*����ⲿ����*/
#define TCS_2046_MISO_Hight             (GPIO_ReadInputDataBit(TSC2046_MISO_Port,TSC2046_MISO_Pin)==1)

#define TCS_2046_PEN_Low                (GPIO_ReadInputDataBit(TSC2046_PEN_Port,TSC2046_PEN_Pin)==0)
/*���������*/
#define TCS_2046_Cmd_Read_Y_Pos         0xD0            /*��������Y����λ��*/
#define TCS_2046_Cmd_Read_X_Pos         0x90            /*��������X����λ��*/

/*Flash��ַ��ض���,�õ�ַ�����ֿ���Ϣ��ַ���ͻ*/
#define TCS_2046_Sec_Addr                   0x1E0000
#define TCS_2046_kx_Addr                    0x1E0000
#define TCS_2046_ky_Addr                    0x1E0004
#define TCS_2046_Cen_Logic_X_Addr           0x1E0008
#define TCS_2046_Cen_Logic_Y_Addr           0x1E000A

#define TCS_2046_Calibration_Error          15           /*�������У׼�������������ƽ�����*/

/*�û��Զ��庯��*/
void TSC2046_SoftSPI_GPIO_Conf(void);
void TSC2046_DelayUS (uint32_t ulCount);
uint16_t TSC2046_Write_Read(uint8_t data);
uint16_t TSC2046_Ave_Value(uint8_t Cmd);
void TSC2046_Calibration(void);
void TSC2046_Calculate_XY(uint16_t *datasto);
uint8_t TSC2046_Applic(uint16_t* postion);

#endif
