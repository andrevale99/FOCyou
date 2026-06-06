#ifndef INVERSOR_H
#define INVERSOR_H

#include <stm32f411xe.h>

typedef struct
{
    uint16_t fase;
}phase_t;

typedef struct
{
    TIM_TypeDef *const timer;

    uint16_t prescale;
    uint16_t periodo;

    uint16_t deadtime;

    phase_t a;
    phase_t b;
    phase_t c;
}inversor_t;

/**
 * @brief Inicializa e configura o temporizador do inversor.
 *
 * Esta função configura o temporizador responsável pela geração dos
 * sinais PWM complementares do inversor. São configurados o prescaler,
 * período, modo PWM, preload do registrador de comparação, tempo morto
 * (dead-time), habilitação das saídas principal e complementar, além do
 * acionamento do temporizador.
 *
 * @param handle Ponteiro para a estrutura de configuração do inversor.
 *
 * @return int8_t
 * @retval 0 Inicialização realizada com sucesso.
 * @retval -1 Ponteiro de configuração inválido.
 */
int8_t inversor_init(const inversor_t *);

/**
 * @brief Calcula a frequência de chaveamento do inversor.
 *
 * A frequência é calculada a partir da frequência do clock do temporizador,
 * do valor do prescaler (PSC) e do registrador de auto-reload (ARR).
 *
 * A expressão utilizada é:
 * @f[
 * f_{sw} = \frac{f_{clk}}{(PSC + 1)(ARR + 1)}
 * @f]
 *
 * O valor retornado é convertido para kHz.
 *
 * @param inv Ponteiro para a estrutura do inversor.
 * @param sisClockHz Frequência do clock do sistema em Hertz.
 *
 * @return uint32_t Frequência de chaveamento em kHz.
 *
 * @note Para temporizadores operando em modo center-aligned (up-down),
 * a frequência efetiva do PWM é metade da obtida pela expressão acima.
 * Nesse caso, o cálculo deve considerar um fator adicional de 2 no divisor.
 */
uint32_t inversor_frequencia_chaveamento(const inversor_t *, uint32_t);

#endif