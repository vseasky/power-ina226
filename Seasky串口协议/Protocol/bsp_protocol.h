#ifndef _BSP_PROTOCOL_H
#define _BSP_PROTOCOL_H

#include "main.h"

#define PROTOCOL_CMD_ID 0XA5

#define OFFSET_BYTE 8	//出数据段外，其他部分所占字节数

typedef struct
{
    __packed struct
    {
        uint8_t  sof;
        uint16_t data_length;
        uint8_t  crc_check; //帧头CRC校验
    } header;					//数据帧头
    uint16_t cmd_id;	 		//数据ID
    uint16_t frame_tail; 		//帧尾CRC校验
} protocol;

/*更新发送数据帧，并计算发送数据帧长度*/
void get_protocol_send_data
(uint16_t send_id,	 	  //信号id
 uint16_t flags_register, //16位寄存器
 float    *tx_data,		  //待发送的float数据
 uint8_t  float_length,//float的数据长度
 uint8_t  *tx_buf,		  //待发送的数据帧
 uint16_t *tx_buf_len);	  //待发送的数据帧长度

/*接收数据处理*/
uint16_t get_protocol_info
(uint8_t  *rx_buf,			//接收到的原始数据
 uint16_t *rx_pos,			//原始数据指针
 uint16_t *flags_register,	//接收数据的16位寄存器地址
 float    *rx_data);		//接收的float数据存储地址


/*中断函数传值处理*/
void PROTOCOL_RX_IRQ(uint8_t res,uint8_t *rx_buf,uint16_t *rx_buf_pos);
#endif