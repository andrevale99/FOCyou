#ifndef INIT_INVERSOR_H
#define INIT_INVERSOR_H

#include "libmcu.h"

#define INVERSOR_UH_GPIO 8
#define INVERSOR_VH_GPIO 9
#define INVERSOR_WH_GPIO 10

#define INVERSOR_UL_GPIO 13
#define INVERSOR_VL_GPIO 14
#define INVERSOR_WL_GPIO 15

void init_periferico_inversor(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN;

    TIM1->CR1 = 0;
    TIM1->CCER = 0;
    TIM1->CCMR1 = 0;
    TIM1->BDTR = 0;

    // A8 alternate function
    GPIOA->MODER &= ~(0x3 << (INVERSOR_UH_GPIO * 2));
    GPIOA->MODER |= (0x2 << (INVERSOR_UH_GPIO * 2));

    GPIOA->OSPEEDR &= ~(0x3 << (INVERSOR_UH_GPIO * 2));
    GPIOA->OSPEEDR |= (0x3 << (INVERSOR_UH_GPIO * 2));

    GPIOA->PUPDR &= ~(0x3 << (INVERSOR_UH_GPIO * 2));
    GPIOA->PUPDR |= (0x2 << (INVERSOR_UH_GPIO * 2));

    GPIOA->AFR[1] &= ~(0xF << ((INVERSOR_UH_GPIO - 8) * 4));
    GPIOA->AFR[1] |= (0x1 << ((INVERSOR_UH_GPIO - 8) * 4));

    // B13 alternate function
    GPIOB->MODER &= ~(0x3 << (INVERSOR_UL_GPIO * 2));
    GPIOB->MODER |= (0x2 << (INVERSOR_UL_GPIO * 2));

    GPIOB->OSPEEDR |= (0x3 << (INVERSOR_UL_GPIO * 2));
    GPIOB->PUPDR &= ~(0x3 << (INVERSOR_UL_GPIO * 2));

    GPIOB->AFR[1] &= ~(0xF << ((INVERSOR_UL_GPIO - 8) * 4));
    GPIOB->AFR[1] |= (0x1 << ((INVERSOR_UL_GPIO - 8) * 4));
}

#endif