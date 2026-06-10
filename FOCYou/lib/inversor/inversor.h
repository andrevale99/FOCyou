#ifndef INVERSOR_H
#define INVERSOR_H

#include <stm32f411xe.h>

#include "timer.h"

typedef struct
{
    const timer_inversor_t *invTimer;
}inversor_t;

/**
 * @brief Atualiza o ciclo de trabalho dos três canais PWM do inversor.
 *
 * Configura os registradores de comparação (CCR1, CCR2 e CCR3) do timer
 * associado ao inversor, definindo o ciclo de trabalho das fases A, B e C.
 *
 * Caso algum valor de duty cycle seja maior ou igual ao valor de auto-reload
 * (ARR) configurado, ele será limitado automaticamente para
 * (ARR - 1), evitando que o valor ultrapasse a faixa válida do contador.
 *
 * @param[in,out] inv_t Ponteiro para a estrutura do inversor.
 * @param[in] duty_a Valor de comparação para a fase A (CCR1).
 * @param[in] duty_b Valor de comparação para a fase B (CCR2).
 * @param[in] duty_c Valor de comparação para a fase C (CCR3).
 *
 * @retval 0  Operação realizada com sucesso.
 * @retval -1 Ponteiro para a estrutura do inversor inválido (NULL).
 *
 * @note Quando os registradores de preload dos canais PWM estiverem
 * habilitados (OCxPE = 1), os valores escritos nos registradores CCRx
 * serão transferidos para os registradores ativos apenas no próximo
 * evento de atualização (Update Event).
 *
 * @warning Esta função assume que o membro invTimer da estrutura
 *          @p inv_t foi previamente inicializado e contém ponteiros válidos.
 */
uint8_t inversor_set_duty(inversor_t *inv_t,
                          uint32_t duty_a,
                          uint32_t duty_b,
                          uint32_t duty_c);

#endif