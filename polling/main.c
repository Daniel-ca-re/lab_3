#include "pico/stdlib.h"
#include "funtions.h"
#define signal 1

void main(){
    ///contantes de el display
    uint8_t lcdpins[7]={2,3,4,5,6,7,8};
    uint8_t lcds[6]={14,13,12,11,10,9};
    uint8_t lcdNumber[6]={0,0,0,0,0,0};
    uint8_t dispEn=0; 
    ///inicializacion de los puetos gpio
    gpio_init(signal);
    gpio_set_dir(signal, GPIO_IN);
    for(int i=0;i<7;i++){
    gpio_init(lcdpins[i]);
    gpio_set_dir(lcdpins[i], GPIO_OUT);
    }
    for(int i=0;i<6;i++){
    gpio_init(lcds[i]);
    gpio_set_dir(lcds[i], GPIO_OUT);
    gpio_put(lcds[i],0);
    }
    ///timers
    uint64_t disp_clock=time_us_64();
    uint64_t num_clock=time_us_64();


    bool state =gpio_get(signal);
    uint64_t cnt = 0;
    bool enable=false;

    while(1){
        ///contador de flancos de subida
        if( state!=gpio_get(signal) ){
            if(state)
                cnt++;
            state=gpio_get(signal);
        }
        ///actualiza los displays
        if(time_us_64()-disp_clock>5000){
            gpio_put(lcds[dispEn++], 0);
            dispEn=dispEn%6;
            if(dispEn==0)
                enable=false;
            if(lcdNumber[dispEn]!=0)
                enable=true;
            PrintNumber(lcdNumber[dispEn], lcdpins,enable);
            gpio_put(lcds[dispEn], 1);
            disp_clock=time_us_64();
        }
        ///actializa la frecuancia cada seg
        if(time_us_64()-num_clock>1000000){
            NumberUnits(cnt,lcdNumber);
            cnt = 0;
            num_clock=time_us_64();
        }
    };

}