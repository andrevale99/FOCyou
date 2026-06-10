#ifndef INVERSOR_H
#define INVERSOR_H

#include <stm32f411xe.h>

#include "timer.h"

typedef struct
{
    const timer_inversor_t *invTimer;
}inversor_t;

void inversor_set_duty(inversor_t *, uint32_t, uint32_t, uint32_t);

#endif