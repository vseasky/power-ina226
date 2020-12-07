#ifndef _BSP_CAN_H
#define _BSP_CAN_H
#include "sys.h"	
							    
#define CAN_Tx_Msg 0X0301										 							 				    
void mx_can_init(void);
void can_send_msg(s16 mt1,s16 mt2,s16 mt3,s16 mt4);						//发送数据
u8 Can_Receive_Msg(u8 *buf);							//接收数据
#endif
