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

    GPIOA->MODER &= ~((0x3 << (ADC_INPUT_1_GPIOA * 2)) |
                      (0x3 << (ADC_INPUT_2_GPIOA * 2)));

    GPIOA->MODER |= (0x3 << (ADC_INPUT_1_GPIOA * 2)) |
                    (0x3 << (ADC_INPUT_2_GPIOA * 2));

    ADC1->CR1 = 0;
    ADC1->CR1 |= ADC_CR1_SCAN;

    ADC1->CR2 = 0;
    ADC1->CR2 |= ADC_CR2_EXTEN_0;

    ADC1->SQR1 = 0;
    ADC1->SQR2 = 0;
    ADC1->SQR3 = 0;

    ADC1->SQR1 |= (ADC_SQR1_L_0);
    ADC1->SQR3 |= (6 << ADC_SQR3_SQ1_Pos) | ((7 << ADC_SQR3_SQ2_Pos));

    ADC1->SMPR2 = 0;
    ADC1->SMPR2 = (2 << ADC_SMPR2_SMP6_Pos) | ((2 << ADC_SMPR2_SMP6_Pos)); // 28 ciclos

    ADC1->CR2 |= ADC_CR2_DMA;
    ADC1->CR2 |= ADC_CR2_DDS; // DMA após cada sequência

    DMA2_Stream0->CR &= ~DMA_SxCR_EN;

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