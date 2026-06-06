#include <stdio.h>

#include <stm32f411xe.h>

#include <arm_math.h>

#include "macros.h"
#include "init_rcc.h"
#include "init_systick.h"
#include "init_lcd16x2.h"
#include "init_inversor.h"

#include "lcd16x2.h"
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

const inversor_t inv = {
    .timer = TIM1,
    .periodo = 624,
    .prescale = 1,

    .a.fase = 500,
    .b.fase = 0,
    .c.fase = 0,
};

foc_transform_t foc = {0};

int main(void)
{
    
    init_rcc();
    init_systick();

    init_periferico_lcd16x2();
    init_periferico_inversor();
    
    
    lcd16x2_init_4bits(&lcd);
    lcd16x2_send_cmd(&lcd, DISPLAY_ON | CURSOR_ON);

    inversor_init(&inv);

    char buffer[16];

    int size = sprintf(buffer, "SW:%ldkHz", inversor_frequencia_chaveamento(&inv,SystemCoreClock));
    lcd16x2_write_string(&lcd, buffer, size);

    while (1)
    {

    }

    return 0;
}