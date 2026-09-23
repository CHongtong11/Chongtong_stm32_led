void usart_init(void);
#include "stm32f10x.h"
#include<stdio.h>
void USARTSendByte(USART_TypeDef* USARTx, uint16_t Data);
void USARTSendstr(USART_TypeDef* USARTx, char*str);





