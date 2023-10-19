#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"
void NumberUnits(uint64_t number,uint8_t *numVector);
void PrintNumber(uint8_t number, uint8_t *lcdpins);
void interrupt_handler();
void timer_callback_1s();
void timer_callback_5ms();