// @author Izaías Araújo Gomes da Silva

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

// Configurações do Servo
const uint16_t servo_gpio = 22;
const float SERVO_PWM_DIV = 125.0f;    // Divisor de clock para o PWM
const uint16_t SERVO_PWM_WRAP = 20000; // Período de 20ms (50Hz)

// Definições dos pulsos (em µs)
const uint16_t PULSE_HIGH_VAL = 2400;   // para 180°
const uint16_t PULSE_MIDDLE_VAL = 1470;   // para 90°
const uint16_t PULSE_LOW_VAL = 500;       // para 0°


const uint SERVO_WAIT_TIME_MS = 5000; // Atraso de 5ms para movimentos rápidos
const uint SERVO_LOOP_DELAY_MS = 10;  // Atraso de 10ms entre incrementos

// Configurações do LED RGB AZUL
const uint LED_GPIO = 12;
const uint LED_PWM_WRAP = 255;    // Resolução de 8 bits para brilho
const float LED_PWM_DIV = 488.0f; // Aproximadamente 1kHz de frequência para PWM do LED

// Definição da estrutura Servo
// para armazenar as informações do servo
// (pino, slice, canal, pulsos mínimo e máximo)
// e facilitar o controle do servo.
typedef struct
{
    uint16_t gpio;
    uint16_t slice_num;
    uint16_t channel;
    uint16_t pulse_min;
    uint16_t pulse_max;
} Servo;

// Inicializa o servo configurando o pino e o PWM
void servo_init(Servo *servo, uint16_t gpio, uint16_t pulse_min, uint16_t pulse_max)
{
    servo->gpio = gpio;
    servo->pulse_min = pulse_min;
    servo->pulse_max = pulse_max;

    gpio_set_function(gpio, GPIO_FUNC_PWM);
    servo->slice_num = pwm_gpio_to_slice_num(gpio);
    servo->channel = pwm_gpio_to_channel(gpio);
    pwm_set_wrap(servo->slice_num, SERVO_PWM_WRAP);
    pwm_set_clkdiv(servo->slice_num, SERVO_PWM_DIV);
    pwm_set_chan_level(servo->slice_num, servo->channel, 0);
    pwm_set_enabled(servo->slice_num, true);
}

// Função auxiliar para posicionar o servo de 0° a 180° usando a estrutura Servo.
// A conversão é linear: 0° corresponde a pulse_min e 180° a pulse_max.
void servo_set_pos(Servo *servo, int angle)
{
    if (angle < 0)
        angle = 0;
    if (angle > 180)
        angle = 180;
    uint16_t pulse = servo->pulse_min + ((servo->pulse_max - servo->pulse_min) * angle) / 180;
    pwm_set_chan_level(servo->slice_num, servo->channel, pulse);
    printf("Posição: %d° (pulse: %d µs)\n", angle, pulse);
}

int main()
{
    stdio_init_all();

    //  Configuração do PWM para o Servo (GPIO22)
    Servo servo;   

    servo_init(&servo, servo_gpio, PULSE_LOW_VAL, PULSE_HIGH_VAL);

    //  Configuração do PWM para o LED BLUE (GPIO12)
    gpio_set_function(LED_GPIO, GPIO_FUNC_PWM);
    uint16_t led_slice = pwm_gpio_to_slice_num(LED_GPIO);
    uint16_t led_channel = pwm_gpio_to_channel(LED_GPIO);

    pwm_set_wrap(led_slice, LED_PWM_WRAP);
    pwm_set_clkdiv(led_slice, LED_PWM_DIV);
    pwm_set_chan_level(led_slice, led_channel, 0); // Inicia com LED apagado
    pwm_set_enabled(led_slice, true);

    servo_set_pos(&servo, 180);
    sleep_ms(SERVO_WAIT_TIME_MS);
    servo_set_pos(&servo, 90);
    sleep_ms(SERVO_WAIT_TIME_MS);
    servo_set_pos(&servo, 0);
    sleep_ms(SERVO_WAIT_TIME_MS);

    int led_brightness = 0;
    int led_fade_factor = 1; // Fator de incremento/decremento do brilho

    int angle = 0;
    int step = 1;
    while (true)
    {
        servo_set_pos(&servo, angle);

        // Atualiza o brilho do LED para efeito fade
        led_brightness += led_fade_factor;
        led_fade_factor = (led_brightness >= LED_PWM_WRAP) ? -1
                                                           : (led_brightness <= 0 ? 1 : led_fade_factor);
        led_brightness = (led_brightness >= LED_PWM_WRAP) ? LED_PWM_WRAP
                                                          : (led_brightness <= 0 ? 0 : led_brightness);
        pwm_set_chan_level(led_slice, led_channel, led_brightness);
        
        angle += step;
        if (angle >= 180 || angle <= 0)
            step = -step;

        sleep_ms(SERVO_LOOP_DELAY_MS);
    }

    return 0;
}