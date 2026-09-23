#define RCC_APB2ENR (*(volatile unsigned int *)(RCC_BASE + 0x18))
#define GPIOA_CRL   (*(volatile unsigned int *)(GPIOA_BASE + 0x00))
#define GPIOA_ODR   (*(volatile unsigned int *)(GPIOA_BASE + 0x0C))
#define GPIOB_CRL   (*(volatile unsigned int *)(GPIOB_BASE + 0x00))
#define GPIOB_ODR   (*(volatile unsigned int *)(GPIOB_BASE + 0x0C))
#define GPIOC_CRL   (*(volatile unsigned int *)(GPIOC_BASE + 0x00))
#define GPIOC_CRH   (*(volatile unsigned int *)(GPIOC_BASE + 0x04))
#define GPIOC_ODR   (*(volatile unsigned int *)(GPIOC_BASE + 0x0C))
#include "stm32f10x.h"
#include "main.h"
#include "led.h"
#include "usart.h"
#include "tim.h"
#include "SysTick.h"
#include "oled.h"

void Ms_delay(unsigned int ms)
{
	
    unsigned int i,j;
    for(i=0;i<ms;i++)
        for(j=0;j<14400;j++);
}
int  main()
{
		LED_Init();
	
	

	
	while(1)  // 死循环，程序会一直循环执行里面的流水灯逻辑
{
    //PA1亮
    GPIOA_ODR &= ~(1<<1);  // 1<<1：把1左移1位，二进制 0b10；~按位取反；&= 按位与，把PA1引脚置0，LED点亮
    Ms_delay(1000);        // 延时1000ms，也就是1秒，保持当前灯亮1s
    GPIOA_ODR |=  (1<<1);  // |= 按位或，把PA1引脚置1，LED熄灭

    //PB0亮
    GPIOB_ODR &= ~(1<<0);  // 1<<0 二进制0b1，PB0引脚置0，LED点亮
    Ms_delay(1000);        // 保持PB0灯亮1秒
    GPIOB_ODR |=  (1<<0);  // PB0引脚置1，LED熄灭

    //PC15亮
    GPIOC_ODR &= ~(1<<15);  // PC1引脚置0，LED点亮
    Ms_delay(1000);        // 保持PC15灯亮1秒
    GPIOC_ODR |=  (1<<15);  // PC1引脚置1，LED熄灭

    //PC13板载灯亮
    GPIOC_ODR &= ~(1<<13); // 1左移13位，PC13引脚置0，板载LED点亮
    Ms_delay(1000);        // PC13灯亮1秒
    GPIOC_ODR |=  (1<<13); // PC13引脚置1，板载LED熄灭
}
	
	
}	
	
	
	
	

