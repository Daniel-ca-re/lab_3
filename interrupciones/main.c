/**
 * @file main.c
 * @brief Programa principal para el control de un display de 7 segmentos y manejo de interrupciones.
 */

#include "pico/stdlib.h"
#include "functions.h"
#include "hardware/sync.h"

#define signal 1

/**
 * @brief Número de flancos de subida contados.
 */
uint64_t cnt = 0;

/**
 * @brief Constantes de configuración del display de 7 segmentos.
 */
uint8_t segment_pins[7] = {12, 11, 19, 20, 21, 10, 22};
uint8_t display_pins[6] = {16, 17, 18, 15, 14, 13};
uint8_t frequency_vector[6] = {0, 0, 0, 0, 0, 0};

/**
 * @brief Callback del temporizador para actualizar el display.
 *
 * Esta función se llama periódicamente para actualizar el display de 7 segmentos.
 * Rota los dígitos que se muestran en el display y actualiza la visualización.
 *
 * @param t Puntero al temporizador.
 * @return Devuelve "true" para indicar que el temporizador debe seguir funcionando.
 */
bool repeating_timer_callback1(struct repeating_timer *t) {

    static uint8_t display_on = 0; 
    
    gpio_put(display_pins[display_on++], 0);
    display_on=display_on%6;
    PrintNumber(frequency_vector[display_on], segment_pins);
    gpio_put(display_pins[display_on], 1);

    return true;
    
}

/**
 * @brief Callback del temporizador para actualizar la frecuencia.
 *
 * Esta función se llama periódicamente para actualizar el vector de frecuencia.
 * Reinicia el contador de flancos de subida y actualiza el vector de frecuencia.
 *
 * @param t Puntero al temporizador.
 * @return Devuelve "true" para indicar que el temporizador debe seguir funcionando.
 */
bool repeating_timer_callback2(struct repeating_timer *t) {

    NumberUnits(cnt, frequency_vector);
    cnt=0;

    return true;
    
}

void main(){
    
    // Inicialización de los puertos GPIO y configuración de interrupciones
    gpio_init(signal);
    gpio_set_dir(signal, GPIO_IN);
    gpio_set_pulls(signal, false, true);
    gpio_set_irq_enabled_with_callback(signal, GPIO_IRQ_EDGE_RISE, true, &interrupt_handler);
    irq_set_enabled(PIO0_IRQ_0, true);

    // Inicialización de pines para el display de 7 segmentos
    for(int i=0;i<7;i++){
        gpio_init(segment_pins[i]);
        gpio_set_dir(segment_pins[i], GPIO_OUT);
    }

    // Inicialización de pines para el display de 6 dígitos
    for(int i=0;i<6;i++){
        gpio_init(display_pins[i]);
        gpio_set_dir(display_pins[i], GPIO_OUT);
    }

    // Creación de temporizadores para actualización del display y la frecuencia
    struct repeating_timer timer1;
    add_repeating_timer_ms(3, repeating_timer_callback1, NULL, &timer1);

    struct repeating_timer timer2;
    add_repeating_timer_ms(1000, repeating_timer_callback2, NULL, &timer2);


    while(1){
        // Modo de espera para ahorrar energía
        __wfi();
    };

}
