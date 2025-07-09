#include <xc.h>
#include "nxlcd.h"


void initADCON() {
    TRISAbits.TRISA0 = 1;

    ADCON1 = 0b00001110; 
    ADCON0 = 0b00000001; 
    ADCON2 = 0b10010101;
} 

unsigned int getADCON() {
    ADCON0bits.GO_DONE = 1;
    while (ADCON0bits.GO_DONE);
    return((256* ADRESH) + ADRESL);
}

unsigned int getMenuOp(unsigned int adValue, unsigned int opCount) {
        unsigned int opValue = 950 / (opCount - 1);
        unsigned int opTemp = opValue;
        unsigned int selected = 0;
        while(opTemp < adValue) {
            opTemp += opValue;
            selected++;
        }
        return selected;
}

unsigned int getMenuOpADCON(unsigned int opCount) {
        unsigned int opValue = 950 / (opCount - 1);
        unsigned int opTemp = opValue;
        unsigned int selected = 0;
        while(opTemp < getADCON()) {
            opTemp += opValue;
            selected++;
        }
        return selected;
}