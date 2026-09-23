#include "HC_SR04.h"
#include "stm32f10x.h"
#include "SysTick.h"

extern uint16_t  mscount = 0;

void HC_SR04init(void)
{
	                        //time = ARR*PSC /72 000 000    目前定时器是配置1us
    GPIO_InitTypeDef GPIOhc_sro4init;
	  TIM_TimeBaseInitTypeDef TIM_hc_sr04InitStruct;
	  NVIC_InitTypeDef HC_SR04Nvictime_init;
	
 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	  //结构体配置 (需要放在前面)   //gpio.h
	
	  //Trig PB11  //输出引脚
	  GPIOhc_sro4init.GPIO_Mode  =GPIO_Mode_Out_PP; //推挽输出
	  GPIOhc_sro4init.GPIO_Pin   =GPIO_Pin_11;
	  GPIOhc_sro4init.GPIO_Speed =GPIO_Speed_50MHz;
	  GPIO_Init(GPIOB,&GPIOhc_sro4init);

    //Echo  PB10  //接收引脚
    GPIOhc_sro4init.GPIO_Mode  =GPIO_Mode_IN_FLOATING; //浮空输出
	  GPIOhc_sro4init.GPIO_Pin   =GPIO_Pin_10;
	  GPIO_Init(GPIOB,&GPIOhc_sro4init);

    TIM_hc_sr04InitStruct.TIM_ClockDivision=TIM_CKD_DIV1;  //不分频
    TIM_hc_sr04InitStruct.TIM_CounterMode=  TIM_CounterMode_Up; //向上计数
    TIM_hc_sr04InitStruct.TIM_Period= 1000-1;  //ARR(99+1)
    TIM_hc_sr04InitStruct.TIM_Prescaler=72-1;  //PSC(71+1)
	
    TIM_TimeBaseInit(TIM4, &TIM_hc_sr04InitStruct);
	  //配置定时器中断线
	  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);  //第二个位标志中断线为更新中断
	   //失能定时器
     TIM_Cmd(TIM4, DISABLE);
	  
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);   //配置中断组为中断组1   misc.h
				

	  HC_SR04Nvictime_init.NVIC_IRQChannel       =TIM4_IRQn;       //定时器4   设置中断通道  stm32f10x.h
		HC_SR04Nvictime_init.NVIC_IRQChannelCmd    =ENABLE;                   //控制是否使能
		HC_SR04Nvictime_init.NVIC_IRQChannelPreemptionPriority  =0;          //设置抢占优先级
		HC_SR04Nvictime_init.NVIC_IRQChannelSubPriority   =0;             //设置子优先级
		
		NVIC_Init(&HC_SR04Nvictime_init);
	 
	
}
//使能定时器
void open_tim4(void)
{
    TIM_SetCounter(TIM4, 0);
	  mscount=0;
    TIM_Cmd(TIM4, ENABLE);
     

}
//失能定时器
void Close_tim4(void)
{
    TIM_Cmd(TIM4, DISABLE);


}
void TIM4_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM4, TIM_IT_Update)  !=RESET  )
		{
	       TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
            mscount++;
				
		}

}


//获取定时器计数器的数值
int getEcho_time(void)
{
    uint32_t t=0;
	  t= mscount*1000;
    t+= TIM_GetCounter(TIM4);
    TIM4->CNT =0;
	  ms_delay(50);
	
   return t;
} 
//获得超声波测距距离
float Getlength(void)
{
    int i=0;
    uint16_t t=0;
	  float length =0;
	  float sum=0;
	
     while(i != 5)
		 {
		    TRIG_Send(1);   //PB11 置1
			   ms_delay(20);
         TRIG_Send(0);		 
         while(ECHO_Reci == 0);		
			 
				 open_tim4();
					i=i+1;				
        while(ECHO_Reci == 1);		
			 
			   // Close_tim4();
					t=getEcho_time();
					length=((float)t/58.0);
					sum=sum+length;
				
		 }
		  length=sum/5.0;
		  return length;
}




