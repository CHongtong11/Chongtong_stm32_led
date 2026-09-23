#include "usart.h"
#include "stm32f10x.h"

void usart_init(void)   //串口初始化
{
	    GPIO_InitTypeDef GPIO_initstructure;
	    USART_InitTypeDef USART_initstructure;
	    NVIC_InitTypeDef Nvic_Init;
	    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);   //配置中断组为中断组2   misc.h
	
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);   //配置中断复用时钟
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	

	 	
        //配置PA9 TX	
      GPIO_initstructure.GPIO_Mode   =GPIO_Mode_AF_PP; //推挽输出
			GPIO_initstructure.GPIO_Pin    =GPIO_Pin_9;
			GPIO_initstructure.GPIO_Speed  =GPIO_Speed_50MHz;
			GPIO_Init(GPIOA,&GPIO_initstructure); 

	      //配置PA10 RX
	    GPIO_initstructure.GPIO_Mode   =GPIO_Mode_IN_FLOATING; //浮空输入
			GPIO_initstructure.GPIO_Pin    =GPIO_Pin_10;
			
	    GPIO_Init(GPIOA,&GPIO_initstructure); 
	     
	     //串口1打开
	    USART_initstructure.USART_BaudRate=115200;    //波特率
	    USART_initstructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	    USART_initstructure.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;
			USART_initstructure.USART_Parity=USART_Parity_No;     //校验位
			USART_initstructure.USART_StopBits= USART_StopBits_1;         //停止位
			USART_initstructure.USART_WordLength= USART_WordLength_8b;  //有效字节长度  8位
	    USART_Init(USART1,&USART_initstructure);
      //使能串口1
			USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);   //串口中断配置
			USART_Cmd(USART1,ENABLE);

       
   //配置中断
      
						
		  Nvic_Init.NVIC_IRQChannel       =USART1_IRQn;       //设置中断通道  stm32f10x.h
		  Nvic_Init.NVIC_IRQChannelCmd    =ENABLE;                   //控制是否使能
		  Nvic_Init.NVIC_IRQChannelPreemptionPriority  =1;          //设置抢占优先级
		  Nvic_Init.NVIC_IRQChannelSubPriority   =1;             //设置子优先级
		
		  NVIC_Init(&Nvic_Init);

}


//发送单个字符   调用方法   USARTSendByte(USART1,'o');
void USARTSendByte(USART_TypeDef* USARTx, uint16_t Data){

  USART_SendData(USARTx,Data);
 while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);  //判断是否发送完成
 
}



//发送字符串   //原理字符发送最后一位是\0判断是否最后一位\0就能发送字符串   调用方法   USARTSendStr(USART1,"rqweqw");
void USARTSendStr(USART_TypeDef* USARTx, char *str){

   uint16_t i=0; //无符号整形十六位
  
    do{
			
		USARTSendByte(USARTx, *(str+i));
			i++;
		
		
		}while(*(str+i)!='\0');

   while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET);  //判断是否发送完成

}
  //printf 函数  putchar函数(输出单个字符)  通过重定向  输出数值
int fputc(int ch ,FILE *f){


  USART_SendData(USART1,(uint8_t)ch);
  while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);  //判断是否发送完成

  return (ch);
}
  //scanf()  getchar函数    
int fgetc(FILE *f)
{
	
     while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE)==RESET); //判断是否接收成功

       return (int)USART_ReceiveData(USART1);


}
















