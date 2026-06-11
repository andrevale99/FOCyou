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

    ADC1->CR1 = 0;
    ADC1->CR1 |= ADC_CR1_SCAN;

    ADC1->CR2 = 0;
    ADC1->CR2 |= ADC_CR2_EXTEN_0;

    ADC1->SQR1 = 0;
    ADC1->SQR2 = 0;
    ADC1->SQR3 = 0;

    ADC1->SQR1 |= (ADC_SQR1_L_0);
    ADC1->SQR3 |= (6 << ADC_SQR3_SQ1_Pos) | ((7 << ADC_SQR3_SQ2_Pos));

    ADC1->SMPR2 = 0; //3 ciclos

    ADC1->CR2 |= ADC_CR2_ADON;
}

#endif