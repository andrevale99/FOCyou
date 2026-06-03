#ifndef INVERSOR_H
#define INVERSOR_H

#include <stm32f411xe.h>

typedef struct
{
    uint16_t fase;
}phase_t;

typedef struct
{
    TIM_TypeDef *timer;

    uint16_t prescale;
    uint16_t periodo;

    phase_t a;
    phase_t b;
    phase_t c;
}inversor_t;

int8_t inversor_init(const inversor_t *);

#endif