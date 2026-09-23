#include "bear.h"
#include "stm32f10x.h"
void Bear_Init(void)
{
	GPIO_InitTypeDef bear_inistruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	bear_inistruct.GPIO_Pin =GPIO_Pin_3;
	bear_inistruct.GPIO_Speed = GPIO_Speed_10MHz;
	bear_inistruct.GPIO_Mode = GPIO_Mode_Out_PP;
	
	 GPIO_Init(GPIOA,&bear_inistruct );
	
	 
	
}

