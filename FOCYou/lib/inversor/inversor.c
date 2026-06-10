#include "inversor.h"

int8_t inversor_set_duty(inversor_t *inv_t,
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