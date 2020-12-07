#include "ina226_task.h"

#include "FreeRTOS.h"
#include "task.h"

#include "bsp_usart.h"
#include "bsp_ina226.h"
#include "bsp_can.h"


#define UART_TASK_PRIO 3
#define UART_TASK_STK_SIZE 128
TaskHandle_t Uart_Task_Handler;

#define INFO_TASK_PRIO 2
#define INFO_TASK_STK_SIZE 128
TaskHandle_t Info_Task_Handler;

ina226_task_t ina226_t;
void info_task_creat(void)
{
	xTaskCreate((TaskFunction_t)info_task,
				(char*         )"info_task",
				(uint16_t      )INFO_TASK_STK_SIZE,
				(void *        )NULL,
				(UBaseType_t   )INFO_TASK_PRIO,
				(TaskHandle_t*)&Info_Task_Handler);
			
}	
void uart_task_creat(void)
{
	xTaskCreate((TaskFunction_t)uart_task,
				(char*         )"uart_task",
				(uint16_t      )UART_TASK_STK_SIZE,
				(void *        )NULL,
				(UBaseType_t   )UART_TASK_PRIO,
				(TaskHandle_t*)&Uart_Task_Handler);
			
}	
void info_task(void *pvParameters)
{
	while(1)
	{
		get_power();
		
#ifdef INA226_CAN_CMD
		ina226_can_send();
#endif

#ifdef INA226_UART_CMD
		ina226_uart_send();
#endif		
		vTaskDelay(10);
	}
}
/*准备添加INA226控制数据，但是没必要了*/
void uart_task(void *pvParameters)
{
	while(1)
	{
		uint16_t id_t = 0;
		id_t =  get_protocol_info
		(USART_RX_BUF,			//接收到的原始数据
		 &USART_RX_STA,			//原始数据指针
		 &ina226_t.ctr_t.flags,	//接收数据的16位寄存器地址
		 ina226_t.ctr_t.rx_data);		//接收的float数据存储地址
		if(id_t!=0)ina226_t.ctr_t.ctr_id=id_t;
		vTaskDelay(10);
	}
}
void ina226_can_send(void)
{
	s16 tx_data[4];
	tx_data[0] = ina226_data.Power;			//功率mW
	tx_data[1] = ina226_data.voltageVal;	//mV
	tx_data[2] = ina226_data.Shunt_Current;	//mA
	tx_data[3] = ina226_data.Shunt_voltage;	//uV
	can_send_msg(tx_data[0],tx_data[1],tx_data[2],tx_data[3]);
}

void ina226_uart_send(void)
{
	static float tx_data[4];
	static uint8_t tx_buf[50];
	static uint16_t tx_buf_len;
	static uint16_t tx_len;
	
	tx_data[0] = ina226_data.Power;			//功率mW
	tx_data[1] = ina226_data.voltageVal;	//mV
	tx_data[2] = ina226_data.Shunt_Current;	//mA
	tx_data[3] = ina226_data.Shunt_voltage;	//uV
	get_protocol_send_data
	(INA226_USART_ID,	 	  		//信号id
	CAL,  //16位寄存器
	&tx_data[0],	  		//待发送的float数据
	4,   			  		//float的数据长度
	&tx_buf[0],		  		//待发送的数据帧
	&tx_buf_len);	  		//待发送的数据帧长度
	for(uint16_t i=0; i<tx_buf_len; i++)
    {
            while((USART1->SR&USART_FLAG_TC)==0);//发送完成
            USART_SendData(USART1,tx_buf[i]);
    }
}