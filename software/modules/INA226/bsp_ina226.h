#ifndef __INA226_H
#define __INA226_H

#include "bsp_iic.h"


#define MODE_INA226 0X4327

#define 	CFG_REG	 		0X00		//
#define 	SV_REG 			0X01		//分流电压
#define 	BV_REG 			0X02		//总线电压
#define 	PWR_REG 		0X03		//电源功率
#define 	CUR_REG 		0X04		//电流
#define 	CAL_REG 		0X05		//校准，设定满量程范围以及电流和功率测数的 
#define 	ONFF_REG 		0X06		//屏蔽 使能 警报配置和转换准备就绪
#define 	AL_REG 			0X07		//包含与所选警报功能相比较的限定值
#define 	INA226_GET_ADDR 0XFF		//包含唯一的芯片标识号
#define   	INA226_ADDR1	0x80
#define     INA226_GETALADDR	0X14

//定义配置数据
#define 	INA226_VAL_LSB	2.5f	//分流电压 LSB 2.5uV
#define     Voltage_LSB		1.25f   //总线电压 LSB 1.25mV
#define     CURRENT_LSB 	1.0f 	//电流LSB 1mA
#define     POWER_LSB       25*CURRENT_LSB
#define     CAL             1024     //0.00512/(Current_LSB*R_SHUNT) = 512  //电流偏大改小

typedef struct
{
    float voltageVal;			//mV
    float Shunt_voltage;		//uV
    float Shunt_Current;		//mA
    float Power_Val;			//功率
    float Power;				//功率mW
    uint32_t   ina226_id;
} INA226;

void INA226_SetRegPointer(uint8_t addr,uint8_t reg);
void INA226_SendData(uint8_t addr,uint8_t reg,uint16_t data);
uint16_t INA226_ReadData(uint8_t addr);

void     INA226_Get_ID(uint8_t addr);			//获取 id
uint16_t INA226_GET_CAL_REG(uint8_t addr);		//获取校准值
uint16_t INA226_GetVoltage( uint8_t addr);		//获取总线电压装载值
int16_t INA226_GetShunt_Current(uint8_t addr);	//获取分流电流装载值
int16_t INA226_GetShuntVoltage(uint8_t addr);	//分流电压装载值
uint16_t INA226_Get_Power(uint8_t addr);		//获取功率装载值，不使用

void mx_ina226_init(void);
void GetVoltage(float *Voltage);
void Get_Shunt_voltage(float *Current);
void Get_Shunt_Current(float *Current);
void get_power(void);						////获取功率= 总线电压 * 电流

uint8_t	INA226_AlertAddr(void);
void Get_Power(float *Power);

extern INA226 ina226_data;
#endif

