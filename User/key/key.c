#include "key.h"
#include "stm32f10x.h"
void Key_Init(void)
{
	//初始化按键外设
	GPIO_InitTypeDef key_inistruct;//初始化按键结构体
	//初始化按键时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);//打开APB2下的GPIOA C时钟
	
	key_inistruct.GPIO_Pin =GPIO_Pin_0;//初始化a0引脚
	//key_inistruct.GPIO_Speed = GPIO_Speed_2MHz;
	key_inistruct.GPIO_Mode = GPIO_Mode_IPU;//初始化A0为上拉输入模式
	GPIO_Init(GPIOA,&key_inistruct );//初始化A0结构体
	 
		key_inistruct.GPIO_Pin =GPIO_Pin_13;
	key_inistruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOC,&key_inistruct );
	 
	
}

