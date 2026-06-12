#ifndef INIT_ADC_H
#define INIT_ADC_H

#include "libmcu.h"

#define ADC_INPUT_1_GPIOA 6
#define ADC_INPUT_2_GPIOA 7

static volatile uint16_t adc_buffer[2];

void init_periferico_adc(void)
{

    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    GPIOA->MODER &= ~((0x3 << (ADC_INPUT_1_GPIOA * 2)) |
                      (0x3 << (ADC_INPUT_2_GPIOA * 2)));

    GPIOA->MODER |= (0x3 << (ADC_INPUT_1_GPIOA * 2)) |
                    (0x3 << (ADC_INPUT_2_GPIOA * 2));

    ADC1->CR1 = 0;
    ADC1->CR1 |= ADC_CR1_SCAN;

    ADC1->CR2 = 0;
    ADC1->CR2 |= ADC_CR2_EXTEN_0 | (0x7 << ADC_CR2_EXTSEL_Pos);

    ADC1->SQR1 = 0;
    ADC1->SQR2 = 0;
    ADC1->SQR3 = 0;

    ADC1->SQR1 |= (ADC_SQR1_L_0);
    ADC1->SQR3 |= (6 << ADC_SQR3_SQ1_Pos) | ((7 << ADC_SQR3_SQ2_Pos));

    ADC1->SMPR2 = 0;
    ADC1->SMPR2 = (2 << ADC_SMPR2_SMP6_Pos) | ((2 << ADC_SMPR2_SMP7_Pos)); // 28 ciclos

    ADC1->CR2 |= ADC_CR2_DMA;
    ADC1->CR2 |= ADC_CR2_DDS; // DMA após cada sequência

    /* Para garantir estado conhecido */
    TIM3->CR1 = 0;
    TIM3->CR2 = 0;
    TIM3->SMCR = 0;
    TIM3->DIER = 0;
    TIM3->CCER = 0;
    TIM3->CCMR1 = 0;

    /* Período */
    TIM3->PSC = 1;
    TIM3->ARR = 624;

    /* Ponto do compare */
    TIM3->CCR1 = 624 / 2;

    /* Canal 1 como Output Compare */
    TIM3->CCMR1 &= ~TIM_CCMR1_CC1S_Msk;

    /* Toggle on match */
    TIM3->CCMR1 |= (3 << TIM_CCMR1_OC1M_Pos);

    /* Habilita saída do canal */
    TIM3->CCER |= TIM_CCER_CC1E;

    /* Gera update para carregar registradores */
    TIM3->EGR |= TIM_EGR_UG;

    /* Inicia contador */
    TIM3->CR1 |= TIM_CR1_CEN;

    DMA2_Stream0->CR &= ~DMA_SxCR_EN;
    DMA2_Stream0->CR &= ~DMA_SxCR_CHSEL;

    DMA2->LIFCR =
        DMA_LIFCR_CTCIF0 | DMA_LIFCR_CHTIF0 | DMA_LIFCR_CTEIF0 | DMA_LIFCR_CDMEIF0 | DMA_LIFCR_CFEIF0;

    while (DMA2_Stream0->CR & DMA_SxCR_EN)
        ;

    DMA2_Stream0->CR =
        DMA_SxCR_MINC       // incrementa memória
        | DMA_SxCR_CIRC     // modo circular
        | DMA_SxCR_PSIZE_0  // 16 bits
        | DMA_SxCR_MSIZE_0; // 16 bits

    DMA2_Stream0->PAR = (uint32_t)&ADC1->DR;
    DMA2_Stream0->M0AR = (uint32_t)adc_buffer;
    DMA2_Stream0->NDTR = 2;

    DMA2_Stream0->CR |= DMA_SxCR_EN;

    ADC1->CR2 |= ADC_CR2_ADON;
}

uint16_t adc_get_dma0(void)
{
    return adc_buffer[0];
}

uint16_t adc_get_dma1(void)
{
    return adc_buffer[1];
}

#endif