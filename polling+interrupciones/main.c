/**
 * @file main.c
 * @brief Programa principal para el control de un display de 7 segmentos y manejo de interrupciones.
 */

#include "pico/stdlib.h"
#include "functions.h"
#include "hardware/sync.h"

#define signal 1

/**
 * @brief Contador de flancos de subida.
 */
uint64_t cnt = 0;

/**
 * @brief Indicador para actualizar los displays.
 */
bool flagdisp = 0;

/**
 * @brief Indicador para actualizar la frecuencia cada segundo.
 */
bool flag1seg = 0;

/**
 * @brief Callback para el temporizador que actualiza los displays.
 *
 * @param t Puntero al temporizador.
 * @return Verdadero para repetir el temporizador.
 */
bool repeating_timer_callback1(struct repeating_timer *t) {

    flagdisp = 1;

    return true;
}

/**
 * @brief Callback para el temporizador que actualiza la frecuencia cada segundo.
 *
 * @param t Puntero al temporizador.
 * @return Verdadero para repetir el temporizador.
 */
bool repeating_timer_callback2(struct repeating_timer *t) {

    flag1seg = 1;

    return true;
}

void main(){

    /// Constantes de los display
    uint8_t segment_pins[7] = {12, 11, 19, 20, 21, 10, 22};
    uint8_t display_pins[6] = {16, 17, 18, 15, 14, 13};
    uint8_t frequency_vector[6] = {0, 0, 0, 0, 0, 0};

    uint8_t display_on = 0;

    /// Inicialización de los puertos GPIO
    gpio_init(signal);
    gpio_set_dir(signal, GPIO_IN);
    gpio_set_pulls(signal, false, true);
    gpio_set_irq_enabled_with_callback(signal, GPIO_IRQ_EDGE_RISE, true, &interrupt_handler);
    irq_set_enabled(PIO0_IRQ_0, true);

    for(int i=0;i<7;i++){
        gpio_init(segment_pins[i]);
        gpio_set_dir(segment_pins[i], GPIO_OUT);
    }

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

        /// Actualiza los displays
        if(flagdisp){

            gpio_put(display_pins[display_on++], 0);
            display_on=display_on%6;
            PrintNumber(frequency_vector[display_on], segment_pins);
            gpio_put(display_pins[display_on], 1);
            
            flagdisp = 0;
        }

        /// Actualiza la frecuencia cada segundo
        if(flag1seg){
            NumberUnits(cnt,frequency_vector);
            cnt = 0;
            
            flag1seg = 0;
        }

        // Modo de espera para ahorrar energía
        __wfi();

    };

}
