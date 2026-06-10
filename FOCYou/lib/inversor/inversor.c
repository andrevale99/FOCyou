#include "inversor.h"

void inversor_set_duty(inversor_t *inv_t,
                       uint32_t duty_a, uint32_t duty_b, uint32_t duty_c)
{
    inv_t->invTimer->advTimer->CCR1 = duty_a;
    inv_t->invTimer->advTimer->CCR2 = duty_b;
    inv_t->invTimer->advTimer->CCR3 = duty_c;
}