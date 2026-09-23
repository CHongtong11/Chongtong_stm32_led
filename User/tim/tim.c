#include "tim.h"
#include "stm32f10x.h"

void tim_config(void)
{
	TIM_TimeBaseInitTypeDef TIMinitStructure;
	NVIC_InitTypeDef NVICinitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIMinitStructure.TIM_ClockDivision	= TIM_CKD_DIV1;
	TIMinitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIMinitStructure.TIM_Period=10000-1;
	TIMinitStructure.TIM_Prescaler=7200-1;
  TIMinitStructure.TIM_RepetitionCounter=0;  
	TIM_TimeBaseInit(TIM2, &TIMinitStructure);
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_1);
	
	NVICinitStructure.NVIC_IRQChannel=TIM2_IRQn;
	NVICinitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVICinitStructure.NVIC_IRQChannelSubPriority=1;
	NVICinitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVICinitStructure);
	
	TIM_Cmd(TIM2, ENABLE);
}




