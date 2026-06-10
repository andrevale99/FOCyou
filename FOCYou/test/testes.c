#include <stdio.h>
#include <stdint.h>

typedef struct
{
    int *const ptr;
    const uint32_t prescale;
    const uint32_t autoreload;
} timer_inversor_t;

uint32_t inversor_frequencia_chaveamento(uint32_t sisClockHz, uint32_t psc, uint32_t arr)
{
    return (sisClockHz / ((psc + 1) * (arr + 1)));
}

int main(int argc, char **argv)
{
    printf("%d\n", inversor_frequencia_chaveamento(25000000, 1, 1249));

    int x = 999;
    int y = 456;

    timer_inversor_t inv = {
        .ptr = &x,
        .autoreload = 639,
        .prescale = 1,
    };

    return 0;
}