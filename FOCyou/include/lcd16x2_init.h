#ifndef LCD16X2_INIT
#define LCD16X2_INIT

#include <stm32f411xe.h>

#define LCD_GPIO_D4 0
#define LCD_GPIO_D5 1
#define LCD_GPIO_D6 2
#define LCD_GPIO_D7 3
#define LCD_GPIO_EN 12
#define LCD_GPIO_RS 13

// =================================
// SETUP PARA O LCD16x2
// =================================

void gpio_lcd16x2_setup(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    // Pinos A0,A1,A2 e A3 como output
    GPIOA->MODER |= (0x55);
    GPIOA->OSPEEDR |= (0xAA);

    // Pinos B12 (EN) e B13 (RS)
    GPIOB->MODER |= (0x5 << 24);
    GPIOB->OSPEEDR |= (0xA << 24);
}

void write_d4(uint8_t state)
{
    if (state)
        GPIOA->BSRR |= (1 << LCD_GPIO_D4);
    else
        GPIOA->BSRR |= (1 << (LCD_GPIO_D4 + 16));
}

void write_d5(uint8_t state)
{
    if (state)
        GPIOA->BSRR |= (1 << LCD_GPIO_D5);
    else
        GPIOA->BSRR |= (1 << (LCD_GPIO_D5 + 16));
}

void write_d6(uint8_t state)
{
    if (state)
        GPIOA->BSRR |= (1 << LCD_GPIO_D6);
    else
        GPIOA->BSRR |= (1 << (LCD_GPIO_D6 + 16));
}

void write_d7(uint8_t state)
{
    if (state)
        GPIOA->BSRR |= (1 << LCD_GPIO_D7);
    else
        GPIOA->BSRR |= (1 << (LCD_GPIO_D7 + 16));
}

void write_en(uint8_t state)
{
    if (state)
        GPIOB->BSRR |= (1 << LCD_GPIO_EN); // EN = 1
    else
        GPIOB->BSRR |= (1 << (LCD_GPIO_EN + 16)); // EN = 0
}

void write_rs(uint8_t state)
{
    if (state)
        GPIOB->BSRR |= (1 << LCD_GPIO_RS);
    else
        GPIOB->BSRR |= (1 << (LCD_GPIO_RS + 16));
}


#endif