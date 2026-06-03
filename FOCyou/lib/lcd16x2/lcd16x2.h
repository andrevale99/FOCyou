#ifndef LCD16X2_H
#define LCD16X2_H

#include <stm32f411xe.h>

#include <stdint.h>

#define WRITE 1
#define CMD 0

#define CLEAR_DISPLAY 0x01
#define RETURN_HOME 0x02
#define SECOND_LINE 0xC0

#define ENTRY_MODE_SET 0x04
#define INCREMENT (ENTRY_MODE_SET | 0x02)     // I
#define DECREMENT (ENTRY_MODE_SET | 0x00)     // D
#define SHIFT_DISPLAY (ENTRY_MODE_SET | 0x01) // S

#define DISPLAY_CONTROL 0x08
#define DISPLAY_OFF (DISPLAY_CONTROL | 0x00)  // D
#define DISPLAY_ON (DISPLAY_CONTROL | 0x04)   // D
#define CURSOR_ON (DISPLAY_CONTROL | 0x02)    // C
#define BLINK_CURSOR (DISPLAY_CONTROL | 0x01) // B

#define CURSOR_SHIFT 0x10
#define DISPLAY_SHIFT (CURSOR_SHIFT | 0x08) // S
#define CURSOR_MOVE (CURSOR_SHIFT | 0x00)   // C
#define SHIFT_RIGHT (CURSOR_SHIFT | 0x04)   // R
#define SHIFT_LEFT (CURSOR_SHIFT | 0x00)    // L

#define FUNCTION_SET 0x20
#define BITS_8 (FUNCTION_SET | 0x00)    // DL
#define BITS_4 (FUNCTION_SET | 0x01)    // DL
#define LINES_1 (FUNCTION_SET | 0x00)   // N
#define LINES_2 (FUNCTION_SET | 0x08)   // N
#define FONT_5x8 (FUNCTION_SET | 0x00)  // F
#define FONT_5x10 (FUNCTION_SET | 0x04) // F

#define SET_DDRAM 0x80

typedef struct
{
    void (*write)(uint8_t);
} lcd16x2_pin_t;

typedef struct
{
    lcd16x2_pin_t d4;
    lcd16x2_pin_t d5;
    lcd16x2_pin_t d6;
    lcd16x2_pin_t d7;

    lcd16x2_pin_t en;
    lcd16x2_pin_t rs;

    void (*delay_ms)(uint32_t);
} lcd16x2_handle;

/**
 * @brief Inicializa o display LCD 16x2 no modo de comunicação de 4 bits.
 *
 * Esta função executa a sequência de inicialização necessária para
 * configurar o controlador LCD compatível com HD44780 em modo de 4 bits.
 * Também configura o número de linhas, limpa o display, habilita o cursor
 * piscante e define o modo de incremento automático do cursor.
 *
 * @param handle Ponteiro para a estrutura de controle do LCD.
 *
 * @return int8_t
 * @retval 0 Inicialização realizada com sucesso.
 * @retval -1 Ponteiro para função de atraso (`delay_ms`) inválido,
 * ou handle vazio.
 */
int8_t lcd16x2_init_4bits(const lcd16x2_handle *);

/**
 * @brief Envia um comando para o display LCD.
 *
 * A função transmite um comando de 8 bits ao LCD utilizando
 * comunicação em modo de 4 bits. O byte é dividido em dois nibbles:
 * primeiro os 4 bits mais significativos e depois os 4 bits menos
 * significativos.
 *
 * @param handle Ponteiro para a estrutura de controle do LCD.
 * @param cmd Comando de 8 bits a ser enviado ao display.
 */
void lcd16x2_send_cmd(const lcd16x2_handle *, uint8_t );

/**
 * @brief Envia um dado para o display LCD.
 *
 * Esta função envia um byte de dados ao LCD no modo de 4 bits.
 * Geralmente é utilizada para transmitir caracteres ASCII que serão
 * exibidos no display.
 *
 * @param handle Ponteiro para a estrutura de controle do LCD.
 * @param data Dado de 8 bits a ser enviado ao display.
 */
void lcd16x2_send_data(const lcd16x2_handle *, uint8_t );

/**
 * @brief Escreve uma sequência de caracteres no display LCD.
 *
 * A função envia uma string caractere por caractere ao display,
 * utilizando a função de transmissão de dados.
 *
 * @param handle Ponteiro para a estrutura de controle do LCD.
 * @param str Ponteiro para a string a ser escrita.
 * @param size Quantidade de caracteres que serão enviados.
 */
void lcd16x2_write_string(const lcd16x2_handle *, const char *sr, uint8_t );

#endif