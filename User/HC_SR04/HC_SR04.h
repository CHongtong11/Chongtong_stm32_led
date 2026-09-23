
#include "stm32f10x.h"

void HC_SR04init(void);
void Open_tim4(void);
void Close_tim4(void);
int GetEcho_time(void);
float Getlength (void);



#define ECHO_Reci			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10) 
#define TRIG_Send(a)	if(a)\
											GPIO_SetBits(GPIOB,GPIO_Pin_11);\
											else\
											GPIO_ResetBits(GPIOB,GPIO_Pin_11);








