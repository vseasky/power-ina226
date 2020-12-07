#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "start_task.h"
#include "bsp_led.h"
#include "delay.h"
#include "bsp_can.h"
#include "bsp_usart.h"
#include "bsp_ina226.h"
RCC_ClocksTypeDef RCC_Clocks;//检验时钟
int main()
{
	RCC_GetClocksFreq(&RCC_Clocks);
	delay_init();
	mx_led_init();
	mx_can_init();
	mx_uart_init();
	mx_iic_init();
	mx_ina226_init();
	create_start_task();	//创建开始任务            
    vTaskStartScheduler();  //开启任务调度
	while(1){}
}
