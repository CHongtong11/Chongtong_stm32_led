#include "motor.h"
#include "stm32f10x.h"

void motor_config(void)
{
	GPIO_InitTypeDef GPIO_MotorInir;
	TIM_TimeBaseInitTypeDef TIM_MotorInit;
	TIM_OCInitTypeDef TIMPWM_MotorInit;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_PinRemapConfig( GPIO_PartialRemap_TIM3, ENABLE);

	
	GPIO_MotorInir.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_MotorInir.GPIO_Pin	 = GPIO_Pin_5;
	GPIO_MotorInir.GPIO_Speed=GPIO_Speed_50MHz;
	 GPIO_Init(GPIOB,&GPIO_MotorInir );
	
	TIM_MotorInit.TIM_ClockDivision = TIM_CKD_DIV1;						//设置时钟分割
	TIM_MotorInit.TIM_CounterMode		= TIM_CounterMode_Up;			//向上的模式
	TIM_MotorInit.TIM_Period				= 200-1;									//设置在下一个更新事件装入活动的自动重装载值
	TIM_MotorInit.TIM_Prescaler			= 7200-1;									//时钟频率的预分频值
	TIM_TimeBaseInit(TIM3,&TIM_MotorInit );

	TIMPWM_MotorInit.TIM_OCMode      =  TIM_OCMode_PWM1;					//选择定时器模式
	TIMPWM_MotorInit.TIM_OutputState =  TIM_OutputState_Enable;		//比较输出使能
	TIMPWM_MotorInit.TIM_OCPolarity  =  TIM_OCPolarity_Low;				//选择输出极性
	TIM_OC2Init(TIM3, &TIMPWM_MotorInit);
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_Cmd(TIM3,ENABLE);
	

}





















