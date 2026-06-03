#include <stm32f411xe.h>

#include "init_systick.h"
#include "init_lcd16x2.h"
#include "init_inversor.h"
#include "init_rcc.h"

#include "lcd16x2.h"
#include "inversor.h"

const lcd16x2_handle handlelcd16x2 = {
    .d4.write = write_d4,
    .d5.write = write_d5,
    .d6.write = write_d6,
    .d7.write = write_d7,

    .en.write = write_en,
    .rs.write = write_rs,

    .delay_ms = delay_ms,
};

const inversor_t inversor = {
    .timer = TIM1,
    .periodo = 1249,
    .prescale = 1,

    .a.fase = 500,
    .b.fase = 0,
    .c.fase = 0,
};

int main(void)
{
    
    init_systick();
    init_rcc();

    init_periferico_lcd16x2();
    init_periferico_inversor();
    
    
    lcd16x2_init_4bits(&handlelcd16x2);
    inversor_init(&inversor);


    while (1)
    {

    }

    return 0;
}