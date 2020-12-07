#include "bsp_ina226.h"
#include "delay.h"

INA226 ina226_data;
//初始化INA226
void mx_ina226_init(void)
{

//	IIC_Init();
    INA226_SendData(INA226_ADDR1,CFG_REG,0x8000);	//重新启动
    INA226_SendData(INA226_ADDR1,CFG_REG,MODE_INA226);
    INA226_SendData(INA226_ADDR1,CAL_REG,CAL);		//设置分辨率
    INA226_Get_ID(INA226_ADDR1);					//获取ina226的id
}



//发送,写入数据
void INA226_SendData(uint8_t addr,uint8_t reg,uint16_t data)
{
  	u8 temp=0;
	IIC_Start();

	IIC_Send_Byte(addr);
	IIC_Wait_Ack();

	IIC_Send_Byte(reg);
	IIC_Wait_Ack();
	
	temp = (u8)(data>>8);
	IIC_Send_Byte(temp);
	IIC_Wait_Ack();

	temp = (u8)(data&0x00FF);
	IIC_Send_Byte(temp);
	IIC_Wait_Ack();
	
	IIC_Stop();
}

//设置寄存器指针
void INA226_SetRegPointer(uint8_t addr,uint8_t reg)
{
	IIC_Start();

	IIC_Send_Byte(addr);
	IIC_Wait_Ack();

	IIC_Send_Byte(reg);
	IIC_Wait_Ack();

	IIC_Stop();
}

//读取数据
uint16_t INA226_ReadData(uint8_t addr)
{
	u16 temp=0;
	IIC_Start();

	IIC_Send_Byte(addr+1);
	IIC_Wait_Ack();
	
	temp = IIC_Read_Byte(1);
	temp<<=8;	
	temp |= IIC_Read_Byte(0);
	
	IIC_Stop();
	return temp;
}

//获取id
void INA226_Get_ID(uint8_t addr)
{
    uint32_t temp=0;
    INA226_SetRegPointer(addr,INA226_GET_ADDR);
    temp = INA226_ReadData(addr);
    ina226_data.ina226_id = temp;
}

//获取校准值
uint16_t INA226_GET_CAL_REG(uint8_t addr)
{
    uint32_t temp=0;
    INA226_SetRegPointer(addr,CAL_REG);
    temp = INA226_ReadData(addr);
    return (uint16_t)temp;
}

//分流电压寄存器01H----------->2.5uV/bit
int16_t INA226_GetShuntVoltage(uint8_t addr)
{
    int16_t temp = 0;
    INA226_SetRegPointer(addr,SV_REG);
    temp = INA226_ReadData(addr);
//	if(temp&0x8000)	temp = ~(temp - 1);
    return (int16_t)temp;
}

//总线电压寄存器02H----------->1.25mV/bit
uint16_t INA226_GetVoltage(uint8_t addr)
{
    uint32_t temp = 0;
    INA226_SetRegPointer(addr,BV_REG);
    temp = INA226_ReadData(addr);
    return (uint16_t)temp;
}

//功率寄存器03H----------->25mW/bit
uint16_t INA226_Get_Power(uint8_t addr)
{
    int16_t temp=0;
    INA226_SetRegPointer(addr,PWR_REG);
    temp = INA226_ReadData(addr);
    return (uint16_t)temp;
}

//电流寄存器04H----------->1mA/bit
int16_t INA226_GetShunt_Current(uint8_t addr)
{
    int16_t temp=0;
    INA226_SetRegPointer(addr,CUR_REG);
    temp = INA226_ReadData(addr);
//	if(temp&0x8000)	temp = ~(temp - 1);
    return temp;
}



//获取分流电压----------->2.5uV/bit
void Get_Shunt_voltage(float *Voltage)//uV
{
    *Voltage = (INA226_GetShuntVoltage(INA226_ADDR1)*INA226_VAL_LSB);//如需矫正电流分流参数请将这里改为2.5
}

//获取总线电压----------->1.25mV/bit
void GetVoltage(float *Voltage)//mV
{
    *Voltage = INA226_GetVoltage(INA226_ADDR1)*Voltage_LSB;
}

//获取功率----------->25mW/bit
void Get_Power(float *Power)//mW
{
    *Power = (INA226_Get_Power(INA226_ADDR1)*POWER_LSB);
}

//获取电流----------->1mA/bit
void Get_Shunt_Current(float *Current)//mA
{
    *Current = (INA226_GetShunt_Current(INA226_ADDR1)* CURRENT_LSB);
}

//获取功率= 总线电压 * 电流
void get_power()//W
{
    GetVoltage(&ina226_data.voltageVal);			//mV
    Get_Shunt_voltage(&ina226_data.Shunt_voltage);	//uV
    Get_Shunt_Current(&ina226_data.Shunt_Current);	//mA
    Get_Power(&ina226_data.Power);					//mW
    ina226_data.Power_Val = ina226_data.voltageVal*0.001f * ina226_data.Shunt_Current*0.001f; //mV*mA
}


//不设置报警，舍弃
/*
u8 INA226_AlertAddr()
{
	u8 temp;
	IIC_Start();

	IIC_Send_Byte(INA226_GETALADDR);
	IIC_Wait_Ack();

	temp = IIC_Read_Byte(1);

	IIC_Stop();
	return temp;
}
*/
