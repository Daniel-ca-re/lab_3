#include "pico/stdlib.h"
#include "functions.h"

#define signal 1

uint64_t cnt = 0;

void main(){
    ///constantes de el display
    uint8_t segment_pins[7] = {12, 11, 19, 20, 21, 10, 22};
    uint8_t display_pins[6] = {16, 17, 18, 15, 14, 13};
    uint8_t frequency_vector[6] = {0, 0, 0, 0, 0, 0};


    uint8_t display_on = 0; 

    ///inicializacion de los puertos gpio
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

    ///timers
    uint64_t disp_clock=time_us_64();
    uint64_t num_clock=time_us_64();


    bool state = gpio_get(signal);

    while(1){

        ///actualiza los displays
        if(time_us_64()-disp_clock>3000){

            gpio_put(display_pins[display_on++], 0);
            display_on=display_on%6;
            PrintNumber(frequency_vector[display_on], segment_pins);
            gpio_put(display_pins[display_on], 1);
            disp_clock=time_us_64();

        }

        ///actualiza la frecuencia cada seg
        if(time_us_64()-num_clock>1000000){
            NumberUnits(cnt,frequency_vector);
            cnt = 0;
            num_clock=time_us_64();
        }
    };

}
