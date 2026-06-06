#ifndef INIT_ADC_H
#define INIT_ADC_H

#include "libmcu.h"

#define ADC_INPUT_1_GPIOA 6
#define ADC_INPUT_2_GPIOA 7

void init_periferico_adc(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    GPIOA->MODER &= ~((0x3 << (ADC_INPUT_1_GPIOA * 2)) |
                      (0x3 << (ADC_INPUT_2_GPIOA * 2)));

    GPIOA->MODER |= (0x3 << (ADC_INPUT_1_GPIOA * 2)) |
                    (0x3 << (ADC_INPUT_2_GPIOA * 2));

    // Resolucao 12 bits, modo SCAN
    ADC1->CR1 &= ~(0x3 << ADC_CR1_RES_Pos);
    ADC1->CR1 |= ADC_CR1_SCAN;

    // dado alinhado para a direita, DMA ativada
    ADC1->CR2 &= ~ADC_CR2_ALIGN;
    ADC1->CR2 &= ~(ADC_CR2_EXTEN | ADC_CR2_EXTSEL);
    ADC1->CR2 |= (1U << ADC_CR2_EXTEN_Pos) | (0x9 << ADC_CR2_EXTSEL_Pos);
    ADC1->CR2 |= ADC_CR2_DMA;
    ADC1->CR2 |= ADC_CR2_DDS;

    ADC1->SMPR2 &= ~(ADC_SMPR2_SMP6 | ADC_SMPR2_SMP7);

    ADC1->SMPR2 |= (0x3U << ADC_SMPR2_SMP6_Pos) | (0x3U << ADC_SMPR2_SMP7_Pos);

    // 1 conversao
    ADC1->SQR1 &= ~(0xF << ADC_SQR1_L_Pos);
    ADC1->SQR1 |= (1 << ADC_SQR1_L_Pos);

    // PA6 e PA7 nas convesoes
    ADC1->SQR3 &= ~(ADC_SQR3_SQ1 | ADC_SQR3_SQ2);
    ADC1->SQR3 |= (6 << ADC_SQR3_SQ1_Pos) | (7 << ADC_SQR3_SQ2_Pos);

    ADC1->CR2 |= ADC_CR2_ADON;
}

#endif