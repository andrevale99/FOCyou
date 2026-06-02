#include <stm32f411xe.h>

#include "systick.h"
#include "lcd16x2.h"
#include "lcd16x2_init.h"

lcd16x2_handle handlelcd16x2 = {
    .d4.write = write_d4,
    .d5.write = write_d5,
    .d6.write = write_d6,
    .d7.write = write_d7,

    .en.write = write_en,
    .rs.write = write_rs,

    .delay_ms = delay_ms,
};

int main(void)
{
    systick_init();
    gpio_lcd16x2_setup();
    lcd16x2_init_4bits(&handlelcd16x2);

    char msg[] = {"teste"};

    while (1)
    {
        lcd16x2_write_string(&handlelcd16x2, msg, 3);
        lcd16x2_send_cmd(&handlelcd16x2, RETURN_HOME);
        delay_ms(1000);
        lcd16x2_send_cmd(&handlelcd16x2, SHIFT_RIGHT);
        delay_ms(1000);
        // lcd16x2_send_cmd(&handlelcd16x2, RETURN_HOME);
        // delay_ms(1000);
    }

    return 0;
}