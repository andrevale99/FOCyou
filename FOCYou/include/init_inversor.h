#ifndef INIT_INVERSOR_H
#define INIT_INVERSOR_H

#include "libmcu.h"

#define INVERSOR_UH_GPIO 8
#define INVERSOR_VH_GPIO 9
#define INVERSOR_WH_GPIO 10

#define INVERSOR_UL_GPIO 13
#define INVERSOR_VL_GPIO 14
#define INVERSOR_WL_GPIO 15

static inline void gpio_af1(GPIO_TypeDef *gpio, uint32_t pin)
{
    gpio->MODER &= ~(0x3UL << (pin * 2));
    gpio->MODER |=  (0x2UL << (pin * 2));

    gpio->OSPEEDR &= ~(0x3UL << (pin * 2));
    gpio->OSPEEDR |=  (0x3UL << (pin * 2));

    gpio->PUPDR &= ~(0x3UL << (pin * 2));
    gpio->PUPDR |= (0x2UL << (pin * 2));

    gpio->AFR[pin >> 3] &= ~(0xFUL << ((pin & 0x7) * 4));
    gpio->AFR[pin >> 3] |=  (0x1UL << ((pin & 0x7) * 4));
}

void init_periferico_inversor(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

    RCC->AHB1ENR |=
        RCC_AHB1ENR_GPIOAEN |
        RCC_AHB1ENR_GPIOBEN;

    TIM1->CR1   = 0;
    TIM1->CCER  = 0;
    TIM1->CCMR1 = 0;
    TIM1->CCMR2 = 0;
    TIM1->BDTR  = 0;

    /* CH1, CH2, CH3 */
    gpio_af1(GPIOA, INVERSOR_UH_GPIO); // PA8
    gpio_af1(GPIOA, INVERSOR_VH_GPIO); // PA9
    gpio_af1(GPIOA, INVERSOR_WH_GPIO); // PA10

    /* CH1N, CH2N, CH3N */
    gpio_af1(GPIOB, INVERSOR_UL_GPIO); // PB13
    gpio_af1(GPIOB, INVERSOR_VL_GPIO); // PB14
    gpio_af1(GPIOB, INVERSOR_WL_GPIO); // PB15
}

#endif