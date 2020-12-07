#ifndef _INA226_TASK_H
#define _INA226_TASK_H

#include "bsp_protocol.h"

#define INA226_USART_ID  0X0002

#define INA226_CAN_CMD 		//使能输出模式
#define INA226_UART_CMD 	//使能输出模式


typedef struct
{
	uint16_t flags;
	float rx_data[2];
	uint16_t ctr_id;
}ina226_ctr;

typedef struct
{
	ina226_ctr ctr_t;

}ina226_task_t;

void info_task_creat(void);
void uart_task_creat(void);
void info_task(void *pvParameters);
void uart_task(void *pvParameters);
void ina226_can_send(void);
void ina226_uart_send(void);
#endif
