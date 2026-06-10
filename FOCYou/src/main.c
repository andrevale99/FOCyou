#include <stdio.h>

#include <stm32f411xe.h>

#include <arm_math.h>

#include "init_rcc.h"
#include "init_systick.h"
#include "init_inversor.h"

#include "timer.h"

#include "lcd16x2.h"
#include "init_lcd16x2.h"

#include "inversor.h"

const lcd16x2_handle lcd = {
    .d4.write = write_d4,
    .d5.write = write_d5,
    .d6.write = write_d6,
    .d7.write = write_d7,

    .en.write = write_en,
    .rs.write = write_rs,

    .delay_ms = delay_ms,
};

const timer_inversor_t invTimer =
    {
        .advTimer = TIM1,
        .autoreload = 624,
        .prescale = 1,

        .compare_a = 0,
        .compare_b = 0,
        .compare_c = 0,
};

const inversor_t inv = {
    .invTimer = &invTimer,
};

int main(void)
{

    init_rcc();
    init_systick();

    lcd16x2_init_4bits(&lcd, init_periferico_lcd16x2);
    lcd16x2_send_cmd(&lcd, DISPLAY_ON | CURSOR_ON);

    timer_inversor_init(&invTimer, init_periferico_inversor);

    char buffer[16];
    timer_get_frequency_inversor(&invTimer);
    int size = sprintf(buffer, "SW:%ldkHz", timer_get_frequency_inversor(&invTimer));
    lcd16x2_write_string(&lcd, buffer, size);

    lcd16x2_send_cmd(&lcd, SECOND_LINE);
    inversor_set_duty(&inv, 67, 88, 12);
    size = sprintf(buffer, "%ld %ld %ld", TIM1->CCR1, TIM1->CCR2, TIM1->CCR3);
    lcd16x2_write_string(&lcd, buffer, size);
    lcd16x2_send_cmd(&lcd, RETURN_HOME);

    while (1)
    {
    }

    return 0;
}