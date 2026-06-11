#include <stdio.h>

#include <stm32f411xe.h>

#include <arm_math.h>

#include "init_rcc.h"
#include "init_systick.h"
#include "init_inversor.h"
#include "init_adc.h"

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

timer_inversor_t invTimer =
    {
        .advTimer = TIM1,
        .autoreload = 624,
        .prescale = 1,
};

const inversor_t inv = {
    .invTimer = &invTimer,
};

char buffer[16];

void write_data(void);

int main(void)
{

    init_rcc();
    init_systick();

    lcd16x2_init_4bits(&lcd, init_periferico_lcd16x2);
    lcd16x2_send_cmd(&lcd, DISPLAY_ON | CURSOR_ON);

    timer_inversor_init(&invTimer, init_periferico_inversor);

    init_periferico_adc();

    timer_get_frequency_inversor(&invTimer);
    int size = sprintf(buffer, "%ldkHz", timer_get_frequency_inversor(&invTimer));
    lcd16x2_write_string(&lcd, buffer, size);

    while (1)
    {
        write_data();
        delay_ms(1000);
    }

    return 0;
}

void write_data(void)
{
    int size = 0;

    lcd16x2_send_cmd(&lcd, SET_DDRAM | 0x6);
    size = sprintf(buffer, " %dRPM", 254);
    lcd16x2_write_string(&lcd, buffer, size);

    lcd16x2_send_cmd(&lcd, SECOND_LINE);
    inversor_set_duty(&inv, 550, 624 / 2, 62);
    size = sprintf(buffer, "%d %d %d",
                   inversor_get_duty_percent(&inv, phase_A),
                   inversor_get_duty_percent(&inv, phase_B),
                   inversor_get_duty_percent(&inv, phase_C));
    lcd16x2_write_string(&lcd, buffer, size);

    lcd16x2_send_cmd(&lcd, SECOND_LINE | 0xA);
    lcd16x2_write_string(&lcd, "    ", 4);
    lcd16x2_send_cmd(&lcd, SECOND_LINE | 0xA);
    size = sprintf(buffer, "%ld", ADC1->DR);
    lcd16x2_write_string(&lcd, buffer, size);

    lcd16x2_send_cmd(&lcd, RETURN_HOME);
}