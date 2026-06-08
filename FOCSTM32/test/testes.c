#include <stdio.h>
#include <stdint.h>

uint32_t inversor_frequencia_chaveamento(uint32_t sisClockHz, uint32_t psc, uint32_t arr)
{
    return (sisClockHz / ((psc +1)*(arr+1)));
}

int main(int argc, char **argv)
{
    printf("%d\n", inversor_frequencia_chaveamento(25000000,1,1249));

    return 0;
}