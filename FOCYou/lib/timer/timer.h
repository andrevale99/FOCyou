#ifndef timer_h
#define timer_h

#include <stdint.h>

#include <stm32f411xe.h>

typedef struct
{
    TIM_TypeDef *const advTimer;
    const uint32_t prescale;
    const uint32_t autoreload;
}timer_inversor_t;

/**
 * @brief Inicializa e configura um timer avançado para acionamento de inversor trifásico.
 *
 * Configura o temporizador em modo PWM centralizado (center-aligned mode 3),
 * habilita os três canais PWM e suas saídas complementares, configura o
 * dead-time, carrega os valores iniciais dos registradores de comparação
 * (CCR1, CCR2 e CCR3) e inicia a contagem do temporizador.
 *
 * A função também executa uma rotina de inicialização fornecida pelo usuário,
 * normalmente utilizada para configurar os pinos GPIO associados ao timer.
 *
 * @param[in] inv Ponteiro para a estrutura contendo os parâmetros de
 *                configuração do timer do inversor.
 * @param[in] init_func Função de inicialização dos recursos externos
 *                      necessários ao timer (ex.: configuração de GPIOs).
 *
 * @retval 0  Inicialização realizada com sucesso.
 * @retval -1 Ponteiro para a função de inicialização inválido (NULL).
 * @retval -2 Ponteiro para a estrutura de configuração inválido (NULL).
 */
int8_t timer_inversor_init(const timer_inversor_t *inv, void (*init_func)(void));

/**
 * @brief Obtém a frequência de saída do PWM do inversor.
 *
 * Calcula a frequência efetiva do PWM considerando o clock do sistema,
 * o prescaler (PSC) e o valor de auto-reload (ARR) do temporizador
 * configurado em modo center-aligned (contagem ascendente e descendente).
 *
 * A frequência retornada é expressa em kHz.
 *
 * Fórmula utilizada:
 * @f[
 * f_{PWM} = \frac{f_{CLK}}
 *                {2 \cdot (PSC + 1) \cdot (ARR + 1)}
 * @f]
 *
 * O valor retornado corresponde a:
 * @f[
 * f_{PWM(kHz)} = \frac{f_{PWM}}{1000}
 * @f]
 *
 * @param[in] inv Ponteiro para a estrutura de configuração do timer.
 *
 * @return Frequência do PWM em kHz.
 */
uint32_t timer_get_frequency_inversor(const timer_inversor_t *inv);

#endif