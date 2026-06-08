#include "inversor.h"

int8_t inversor_init(const inversor_t *handle)
{
    if (!handle)
        return -1;

    handle->timer->PSC = handle->prescale;
    handle->timer->ARR = handle->periodo;

    // center-aligned pwm up-down
    handle->timer->CR1 &= ~TIM_CR1_CMS_Msk;
    handle->timer->CR1 |= (3 << TIM_CR1_CMS_Pos);

    handle->timer->CCMR1 |= (6 << TIM_CCMR1_OC1M_Pos);
    handle->timer->CCMR1 |= TIM_CCMR1_OC1PE;

    handle->timer->CCER |= (TIM_CCER_CC1E | TIM_CCER_CC1NE);

    handle->timer->BDTR &= ~TIM_BDTR_DTG_Msk;
    handle->timer->BDTR |= (200 << TIM_BDTR_DTG_Pos);

    handle->timer->CCR1 = handle->a.fase;

    /* Main output enable */
    handle->timer->BDTR |= TIM_BDTR_MOE;

    /* Update registers */
    handle->timer->EGR |= TIM_EGR_UG;

    /* Start timer */
    handle->timer->CR1 |= TIM_CR1_CEN;

    return 0;
}

uint32_t inversor_frequencia_chaveamento(const inversor_t *inv,
                                         uint32_t sisClockHz)
{
    return (sisClockHz /
           (2 * (inv->timer->PSC + 1) *
            (inv->timer->ARR + 1)) /
           1000);
}