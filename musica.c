#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define _XTAL_FREQ 20000000

void configPWMinit(){
    PR2 = 255;
    T2CON = 0b00000110;
    CCP1CON = 0b00001111;
}

void configPR2(unsigned int nota_hz, unsigned int duty_percent){
    unsigned int periodo;
    unsigned int duty;
    unsigned char prescaler = 16;

    PR2 = (int)((5000000 / (4 * nota_hz * prescaler * 2)) - 1);

    duty = (duty_percent * 4 * (PR2 + 1)) / 100;
    CCPR1L = duty >> 2;
    CCP1CONbits.DC1B1 = (duty >> 1) & 0x01;
    CCP1CONbits.DC1B0 = duty & 0x01;

}

void tocar_musica(const unsigned int* notas, const unsigned int* duracao, unsigned int duty){
    unsigned int i = 0;

    while(notas[i] != 0){
        if(notas[i] == 441) {
            configPR2(notas[i], 0);
        }
        else {
            configPR2(notas[i], duty);  
        }
        
        for(int j = 0; j < duracao[i]; j++) {
            __delay_ms(1); 
        }
        i++;
    }
    //configPR2(0,0);
}


