/**
 * @file functions.c
 * @brief Implementación de las funciones para el control de un display de 7 segmentos y manejo de interrupciones.
 */

#include "functions.h"

/**
 * @brief Contador de flancos de subida.
 */
extern uint64_t cnt;

/**
 * @brief Vector de segmentos para representar números en el display de 7 segmentos.
 */
uint8_t segmentos[10] = {
    0b00000001,
    0b01001111,
    0b00010010,
    0b00000110,
    0b01001100,
    0b00100100,
    0b00100000,
    0b00001111,
    0b00000000,
    0b00000100
};


void NumberUnits(uint64_t number, uint8_t *numVector){
    for(int i = 5; i >= 0; i--){
        numVector[i]=number%10;
        number-=numVector[i];
        number/=10;
    }
}


void PrintNumber(uint8_t number, uint8_t *segment_pins){
    for(int i=6;i>=0;i--){
        if(segmentos[number] & (1UL << i))
            gpio_put(segment_pins[6-i], 1);
        else
            gpio_put(segment_pins[6-i], 0);
    }
}

void interrupt_handler() {
    // Maneja la interrupcion por flanco de subida aqui
    cnt++;
}
