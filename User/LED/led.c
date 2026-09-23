#include "led.h"
#include "stm32f10x.h"




#define RCC_APB2ENR (*(volatile unsigned int *)(RCC_BASE + 0x18))
#define GPIOA_CRL   (*(volatile unsigned int *)(GPIOA_BASE + 0x00))
#define GPIOA_ODR   (*(volatile unsigned int *)(GPIOA_BASE + 0x0C))
#define GPIOB_CRL   (*(volatile unsigned int *)(GPIOB_BASE + 0x00))
#define GPIOB_ODR   (*(volatile unsigned int *)(GPIOB_BASE + 0x0C))
#define GPIOC_CRL   (*(volatile unsigned int *)(GPIOC_BASE + 0x00))
#define GPIOC_CRH   (*(volatile unsigned int *)(GPIOC_BASE + 0x04))
#define GPIOC_ODR   (*(volatile unsigned int *)(GPIOC_BASE + 0x0C))

void LED_Init(void)
{
	  
    RCC_APB2ENR |= (1<<2);
    RCC_APB2ENR |= (1<<3);
    RCC_APB2ENR |= (1<<4);

    // PA1 ÍÆÍìÊä³ö 50MHz
    GPIOA_CRL &= ~(0x0F << 4);
    GPIOA_CRL |=  (0x03 << 4);
    GPIOA_ODR |= (1<<1);

    // PB0 ÍÆÍìÊä³ö 50MHz
    GPIOB_CRL &= ~(0x0F << 0);
    GPIOB_CRL |=  (0x03 << 0);
    GPIOB_ODR |= (1<<0);

    // PC15 ÍÆÍìÊä³ö 50MHz
    GPIOC_CRH &= ~(0x0F << 28);
    GPIOC_CRH |=  (0x03 << 28);
    GPIOC_ODR |= (1<<15);

    // PC13 °åÔØLED£¬CRH¼Ä´æÆ÷
    GPIOC_CRH &= ~(0x0F << 20);
    GPIOC_CRH |=  (0x03 << 20);
    GPIOC_ODR |= (1<<13);
}







