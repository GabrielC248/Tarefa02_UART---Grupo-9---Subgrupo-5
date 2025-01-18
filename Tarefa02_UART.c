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

