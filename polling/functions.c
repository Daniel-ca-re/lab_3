#include "functions.h"

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

/// @brief this funtions takes a numbers a gives his decimal components D_{0}*10^0 + D_{1}*10^1 ... it gives 6
/// @param number the number D_{2}D_{1}D_{0}
/// @param numVector [...,D_{2},D_{1},D_{0}]
void NumberUnits(uint64_t number, uint8_t *numVector){
    for(int i = 5; i >= 0; i--){
        numVector[i]=number%10;
        number-=numVector[i];
        number/=10;
    }
}

/// @brief this funtions turns on the the leds of a 7seg to represent a number
/// @param number the number D_{2}D_{1}D_{0}
/// @param segment_pins pins asosiated to the 7seg
void PrintNumber(uint8_t number, uint8_t *segment_pins){
    for(int i=6;i>=0;i--){
        if(segmentos[number] & (1UL << i))
            gpio_put(segment_pins[6-i], 1);
        else
            gpio_put(segment_pins[6-i], 0);
    }
}
