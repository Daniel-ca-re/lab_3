#include "funtions.h"
extern uint64_t cnt;
uint8_t segmentos[10] = {
    0b00111111,  // 0
    0b00000110,  // 1
    0b01011011,  // 2
    0b01001111,  // 3
    0b01100110,  // 4
    0b01101101,  // 5
    0b01111101,  // 6
    0b00000111,  // 7
    0b01111111,  // 8
    0b01101111   // 9
};
/// @brief this funtions takes a numbers a gives his decimal components D_{0}*10^0 + D_{1}*10^1 ... it gives 6
/// @param number the number D_{2}D_{1}D_{0}
/// @param numVector [...,D_{2},D_{1},D_{0}]
void NumberUnits(uint64_t number,uint8_t *numVector){
    for(int i=0;i<6;i++){
        numVector[i]=number%10;
        number-=numVector[i];
        number/=10;
    }

}
/// @brief this funtions turns on the the leds of a 7seg to reprenset a number
/// @param number the number D_{2}D_{1}D_{0}
/// @param lcdpins pins asosiated to the 7seg
void PrintNumber(uint8_t number, uint8_t *lcdpins){
    for(int i=0;i<7;i++){
        if(segmentos[number] & (1ULL <<i))
            gpio_put(lcdpins[i], 1);
        else
            gpio_put(lcdpins[i], 0);
    }
}

void interrupt_handler() {
    cnt++;
    // Maneja la interrupción por flanco de subida aquí.
}
