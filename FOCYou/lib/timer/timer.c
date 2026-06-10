#include "timer.h"

int8_t timer_inversor_init(const timer_inversor_t *inv, void (*init_func)(void))
{
    if (!init_func)
        return -1;

    if (!inv)
        return -2;

    init_func();

    inv->advTimer->PSC = inv->prescale;
    inv->advTimer->ARR = inv->autoreload;

    // center-aligned pwm up-down
    inv->advTimer->CR1 &= ~TIM_CR1_CMS_Msk;
    inv->advTimer->CR1 |= (3 << TIM_CR1_CMS_Pos);

    inv->advTimer->CR1 |= TIM_CR1_ARPE;

    /* CH1 */
    inv->advTimer->CCMR1 |= (6 << TIM_CCMR1_OC1M_Pos);
    inv->advTimer->CCMR1 |= TIM_CCMR1_OC1PE;

    /* CH2 */
    inv->advTimer->CCMR1 |= (6 << TIM_CCMR1_OC2M_Pos);
    inv->advTimer->CCMR1 |= TIM_CCMR1_OC2PE;

    /* CH3 */
    inv->advTimer->CCMR2 |= (6 << TIM_CCMR2_OC3M_Pos);
    inv->advTimer->CCMR2 |= TIM_CCMR2_OC3PE;

    inv->advTimer->CCER |=
        TIM_CCER_CC1E | TIM_CCER_CC1NE |
        TIM_CCER_CC2E | TIM_CCER_CC2NE |
        TIM_CCER_CC3E | TIM_CCER_CC3NE;

    inv->advTimer->BDTR &= ~TIM_BDTR_DTG_Msk;
    inv->advTimer->BDTR |= (130 << TIM_BDTR_DTG_Pos);

    inv->advTimer->CCR1 = inv->compare_a;
    inv->advTimer->CCR2 = inv->compare_b;
    inv->advTimer->CCR3 = inv->compare_c;

    /* Main output enable */
    inv->advTimer->BDTR |= TIM_BDTR_MOE;

    /* Update registers */
    inv->advTimer->EGR |= TIM_EGR_UG;

    /* Start timer */
    inv->advTimer->CR1 |= TIM_CR1_CEN;

    return 0;
}

uint32_t timer_get_frequency_inversor(const timer_inversor_t *inv)
{
    return (SystemCoreClock /
            (2 * (inv->advTimer->PSC + 1) *
             (inv->advTimer->ARR + 1)) /
            1000);
}