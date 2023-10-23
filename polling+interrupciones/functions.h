/**
 * @file functions.h
 * @brief Encabezado de funciones para controlar un display de 7 segmentos y manejar interrupciones.
 */
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

/**
 * @brief Esta función toma un número y descompone sus dígitos decimales, es decir, D_{0}*10^0 + D_{1}*10^1 + D_{2}*10^2...
 * @param number El número D_{2}D_{1}D_{0}.
 * @param numVector Un vector que almacenará los dígitos decimales del número [D_{2}, D_{1}, D_{0}].
 */
void NumberUnits(uint64_t number,uint8_t *numVector);

/**
 * @brief Esta función enciende los LEDs de un display de 7 segmentos para representar un número.
 * @param number El número D_{2}D_{1}D_{0}.
 * @param segment_pins Pines asociados al display de 7 segmentos.
 */
void PrintNumber(uint8_t number, uint8_t *lcdpins);

/**
 * @brief Manejador de interrupción por flanco de subida.
 *
 * Esta función se llama cuando se produce un flanco de subida en la entrada.
 * Incrementa el contador de flancos de subida.
 */
void interrupt_handler();
