#ifndef INIT_RCC_H
#define INIT_RCC_H

#include "libmcu.h"
#include "init_systick.h"

void init_rcc(void)
{
    /* Habilita o oscilador externo */
    RCC->CR |= RCC_CR_HSEON;

    /* Aguarda estabilização do HSE */
    while (!(RCC->CR & RCC_CR_HSERDY))
        ;

    /* Seleciona HSE como clock do sistema */
    RCC->CFGR &= ~RCC_CFGR_SW;
    RCC->CFGR |= RCC_CFGR_SW_HSE;

    /* Aguarda confirmação da troca */
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSE)
        ;

    /* AHB = SYSCLK */
    RCC->CFGR &= ~RCC_CFGR_HPRE;

    /* APB2 = HCLK */
    RCC->CFGR &= ~RCC_CFGR_PPRE2;
}

#endif