#include "bsp_led.h" 
	 
//初始化PF9和PF10为输出口.并使能这两个口的时钟		    
//LED IO初始化
void mx_led_init(void)
{    
	GPIO_InitTypeDef	GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	/*初始化GPIOB 5*/
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);

	GPIO_SetBits(GPIOB,GPIO_Pin_0);
}






