#ifndef __LED_H
#define __LED_H

#define RCC_APB2ENR (*(volatile unsigned int *)(RCC_BASE + 0x18))
#define GPIOA_CRL   (*(volatile unsigned int *)(GPIOA_BASE + 0x00))
#define GPIOA_ODR   (*(volatile unsigned int *)(GPIOA_BASE + 0x0C))
#define GPIOB_CRL   (*(volatile unsigned int *)(GPIOB_BASE + 0x00))
#define GPIOB_ODR   (*(volatile unsigned int *)(GPIOB_BASE + 0x0C))
#define GPIOC_CRL   (*(volatile unsigned int *)(GPIOC_BASE + 0x00))
#define GPIOC_CRH   (*(volatile unsigned int *)(GPIOC_BASE + 0x04))
#define GPIOC_ODR   (*(volatile unsigned int *)(GPIOC_BASE + 0x0C))

void LED_Init(void);

#endif