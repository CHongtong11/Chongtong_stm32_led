#include "exti.h"
#include "stm32f10x.h"

void exti_init(void)
{
	
	GPIO_InitTypeDef key_inistruct;
	EXTI_InitTypeDef	exti_init;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	key_inistruct.GPIO_Pin =GPIO_Pin_1;
	key_inistruct.GPIO_Speed = GPIO_Speed_10MHz;
	key_inistruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOA,&key_inistruct );
	
	exti_init.EXTI_Line = EXTI_Line1;
	exti_init.EXTI_Mode = EXTI_Mode_Interrupt;
	exti_init.EXTI_Trigger
	exti_init.EXTI_LineCmd
	
	
	
}
