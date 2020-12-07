#ifndef _BSP_USART_H
#define _BSP_USART_H
#include "stdio.h"	
#include "stm32f10x.h"

#define USART_REC_LEN  			50  	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
#define USART1_BUOND			115200	//初始化串口1波特率115200	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         		//接收状态标记	
void mx_uart_init(void);
#endif

