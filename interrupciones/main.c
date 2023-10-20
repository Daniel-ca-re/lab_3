#include <stdio.h>
#include "pico/stdlib.h"
#include "funtions.h"
#define signal 1

uint64_t cnt = 0;
uint8_t lcdpins[7]={2,3,4,5,6,7,8};
uint8_t lcds[6]={9,10,11,12,13,14};
uint8_t lcdNumber[6]={0,0,0,0,0,0};
bool repeating_timer_callback(struct repeating_timer *t) {
    static uint8_t dispEn=0; 
    static bool enF=false;
    dispEn=dispEn%6;
    if(dispEn==0){
        enF=false;
        NumberUnits(cnt*56,lcdNumber);
        cnt=0;
    }
    if(lcdNumber[dispEn]!=0)
        enF=true;
    gpio_put(lcds[dispEn++], 0);
    PrintNumber(lcdNumber[dispEn], lcdpins);
    gpio_put(lcds[dispEn], 1);
    return true;
}
void main(){
    stdio_init_all();
    ///contantes de el display
    ///timers 

    // Initialize and configure the timer

    // Rest of your code here

    ///inicializacion de los puetos gpio
    gpio_init(signal);
    gpio_set_dir(signal, GPIO_IN);
    gpio_set_pulls(signal, false, true);
    gpio_set_irq_enabled_with_callback(signal, GPIO_IRQ_EDGE_RISE, true, &interrupt_handler);
    irq_set_enabled(PIO0_IRQ_0, true);
    for(int i=0;i<7;i++){
    gpio_init(lcdpins[i]);
    gpio_set_dir(lcdpins[i], GPIO_OUT);
    }
    for(int i=0;i<6;i++){
    gpio_init(lcds[i]);
    gpio_set_dir(lcds[i], GPIO_OUT);
    }
    ///timers
    struct repeating_timer timer;
    add_repeating_timer_ms(3, repeating_timer_callback, NULL, &timer);

while(1){

    ///actualiza los displays
    ///actializa la frecuancia cada seg
};

}
