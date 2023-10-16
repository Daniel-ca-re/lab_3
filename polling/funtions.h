#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

void NumberUnits(uint64_t number,uint8_t *numVector);
void PrintNumber(uint8_t number, uint8_t *lcdpins);