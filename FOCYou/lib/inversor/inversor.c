#include "inversor.h"

int8_t inversor_set_duty(const inversor_t *inv_t,
                         uint32_t duty_a, uint32_t duty_b, uint32_t duty_c)
{
    if (!inv_t)
        return -1;

    if (duty_a >= inv_t->invTimer->autoreload)
        duty_a = inv_t->invTimer->autoreload - 1;

    if (duty_b >= inv_t->invTimer->autoreload)
        duty_b = inv_t->invTimer->autoreload - 1;

    if (duty_c >= inv_t->invTimer->autoreload)
        duty_c = inv_t->invTimer->autoreload - 1;

    inv_t->invTimer->advTimer->CCR1 = duty_a;
    inv_t->invTimer->advTimer->CCR2 = duty_b;
    inv_t->invTimer->advTimer->CCR3 = duty_c;

    return 0;
}

int8_t inversor_get_duty_percent(const inversor_t *inv_t, phase _phase)
{
    if (!inv_t)
        return -1;

    uint32_t ccr = 0;
    uint32_t arr = inv_t->invTimer->advTimer->ARR;

    switch (_phase)
    {
    case phase_A:
        ccr = inv_t->invTimer->advTimer->CCR1;
        break;

    case phase_B:
        ccr = inv_t->invTimer->advTimer->CCR2;
        break;

    case phase_C:
        ccr = inv_t->invTimer->advTimer->CCR3;
        break;

    default:
        return 0;
    }

    return (uint8_t)((ccr * 100U + arr / 2U) / arr);
}

uint32_t inversor_get_duty(inversor_t *inv_t, phase phase)
{
    if (!inv_t)
        return 0;

    uint32_t ret = 0;

    switch (phase)
    {
    case phase_A:
        ret = inv_t->invTimer->advTimer->CCR1;
        break;

    case phase_B:
        ret = inv_t->invTimer->advTimer->CCR2;
        break;

    case phase_C:
        ret = inv_t->invTimer->advTimer->CCR3;
        break;

    default:
        ret = 0;
        break;
    }

    return ret;
}