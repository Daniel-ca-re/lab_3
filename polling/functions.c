#include "funtions.h"
/// @brief this funtions takes a numbers a gives his decimal components D_{0}*10^0 + D_{1}*10^1 ... it gives 6
/// @param number the number D_{2}D_{1}D_{0}
/// @param numVector [...,D_{2},D_{1},D_{0}]
void NumberUnits(uint16_t number,uint8_t *numVector){
    for(int i=0;i<6;i--){
        numVector[i]=number%10;
        number-=numVector[i];
        number/=10;
    }

}