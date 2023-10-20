#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"
#include "pico/time.h"
#include <pico/stdlib.h>
#include <pico/time.h>

// Function declarations
void NumberUnits(uint64_t number, uint8_t *numVector);
void PrintNumber(uint8_t number, uint8_t *lcdpins);
void interrupt_handler();
