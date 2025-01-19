#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"

// Definições dos GPIOs
#define LED_VERDE 11
#define LED_AZUL  12
#define LED_VERMELHO 13
#define BUZZER 21

// Configuração da UART
#define UART_ID uart0
#define BAUD_RATE 115200
#define UART_TX_PIN 0
#define UART_RX_PIN 1

// Inicializa os GPIOs
void setup_gpio() {
    gpio_init(LED_VERDE);
    gpio_init(LED_AZUL);
    gpio_init(LED_VERMELHO);
    gpio_init(BUZZER);

    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_set_dir(LED_AZUL, GPIO_OUT);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_set_dir(BUZZER, GPIO_OUT);

    gpio_put(LED_VERDE, 0);
    gpio_put(LED_AZUL, 0);
    gpio_put(LED_VERMELHO, 0);
    gpio_put(BUZZER, 0);
}

// Controla os LEDs
void control_leds(bool verde, bool azul, bool vermelho) {
    gpio_put(LED_VERDE, verde);
    gpio_put(LED_AZUL, azul);
    gpio_put(LED_VERMELHO, vermelho);
}

// Controla o buzzer
void control_buzzer(bool state) {
    gpio_put(BUZZER, state);
}

// Lê comandos da UART e executa as ações correspondentes
void process_commands() {
    char command = uart_getc(UART_ID);

    switch (command) {
        case '1': // LED verde
            control_leds(true, false, false);
            break;
        case '2': // LED azul
            control_leds(false, true, false);
            break;
        case '3': // LED vermelho
            control_leds(false, false, true);
            break;
        case '4': // Todos os LEDs (luz branca)
            control_leds(true, true, true);
            break;
        case '5': // Desligar todos os LEDs
            control_leds(false, false, false);
            break;
        case '6': // Acionar o buzzer por 2 segundos
            control_buzzer(true);
            sleep_ms(2000);
            control_buzzer(false);
            break;
        default:
            printf("Comando inválido!\n");
            break;
    }
}

int main() {
    // Inicialização
    stdio_init_all();

    // Configuração da UART
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    setup_gpio();

    printf("Sistema inicializado. Aguardando comandos...\n");

    // Loop principal
    while (true) {
        if (uart_is_readable(UART_ID)) {
            process_commands();
        }
    }

    return 0;
}
/*
#include <stdio.h>        // Inclua para usar printf
#include "pico/stdlib.h"  // Inclua o SDK padrão do Pico

// Definição dos GPIOs
#define LED_GREEN 11
#define LED_BLUE 12
#define LED_RED 13
#define BUZZER 21

// Funções para controlar os LEDs
void turn_off_leds() {
    gpio_put(LED_GREEN, 0);
    gpio_put(LED_BLUE, 0);
    gpio_put(LED_RED, 0);
}

void control_leds(uint led_gpio) {
    turn_off_leds(); // Desliga todos os LEDs
    gpio_put(led_gpio, 1); // Liga o LED especificado
}

// Função para acionar o buzzer
void activate_buzzer() {
    gpio_put(BUZZER, 1); // Liga o buzzer
    sleep_ms(2000);      // Mantém por 2 segundos
    gpio_put(BUZZER, 0); // Desliga o buzzer
}

int main() {
    // Inicialização dos GPIOs
    gpio_init(LED_GREEN);
    gpio_init(LED_BLUE);
    gpio_init(LED_RED);
    gpio_init(BUZZER);

    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_set_dir(BUZZER, GPIO_OUT);

    // Inicializa a comunicação serial
    stdio_init_all();
    printf("Sistema inicializado. Aguarde comandos...\n");

    // Loop principal aguardando comandos via UART
    while (true) {
        char command;

        // Lê o comando do terminal com timeout
        command = getchar_timeout_us(100000); // Timeout de 100ms

        if (command != PICO_ERROR_TIMEOUT) { // Processa apenas se houver entrada
            switch (command) {
                case 'g': // Ligar LED verde
                    control_leds(LED_GREEN);
                    break;
                case 'b': // Ligar LED azul
                    control_leds(LED_BLUE);
                    break;
                case 'r': // Ligar LED vermelho
                    control_leds(LED_RED);
                    break;
                case 'w': // Ligar todos os LEDs (branco)
                    gpio_put(LED_GREEN, 1);
                    gpio_put(LED_BLUE, 1);
                    gpio_put(LED_RED, 1);
                    break;
                case 'o': // Desligar todos os LEDs
                    turn_off_leds();
                    break;
                case 'z': // Acionar o buzzer
                    activate_buzzer();
                    break;
                case 'q': // Sair
                    printf("Saindo...\n");
                    return 0;
                default:
                    printf("Comando inválido!\n");
            }
        }
    }

    return 0;
}
*/