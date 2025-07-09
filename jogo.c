#include <xc.h>
#include <stdint.h>
#include "nxlcd.h"
#include <stdio.h>
#include <string.h>
#include "jogo.h"
#include "menu.h"

unsigned char seta_baixo[8] = {
	0b00000,
	0b00100,
	0b00100,
	0b00100,
	0b10101,
	0b01110,
	0b00100,
	0b00000
};

unsigned char alvo[8] = {
	0b00000,
	0b00000,
	0b01110,
	0b10001,
	0b10101,
	0b10001,
	0b01110,
	0b00000
};

void LoadCustomChar(unsigned char location, unsigned char *charmap) {
    location &= 0x07; 
    SetCGRamAddr(location << 3);  // Each char takes 8 bytes

    for (int i = 0; i < 8; i++) {
        while (BusyXLCD());
        WriteDataXLCD(charmap[i]);
    }

    // Restore DDRAM access after writing
    while (BusyXLCD());
    SetDDRamAddr(0x00);  // Move cursor back to start or desired position
}

void criaSetaAlvo() {
    LoadCustomChar(0, seta_baixo);
    LoadCustomChar(1, seta_baixo);
    LoadCustomChar(2, alvo);
    SetDDRamAddr(0x00);  
}

uint8_t deslocaAlvo(uint8_t pos) {
    limpaLinha(2);
    if(pos == 0){
        escreveLCD(2, printAlvo, 0);
    }else if(pos == 15){
        escreveLCD(2, printAlvo, 15);
        return 0;
    }else{
        escreveLCD(2, printAlvo, pos);
    }
    while(BusyXLCD());
    return pos + 1;
}

void menuIniciar(){
	limpaLCD();
    escreveLCD(1, "Aperte quando", 0);
    escreveLCD(1, printAlvo, 14);
    escreveLCD(2, "chegar em", 0);
    escreveLCD(2, printSeta, 10);
    
}

void iniciarJogo(){
    limpaLCD();
    escreveLCD(1,"Comecando", 3);
    escreveLCD(2,"3..", 0);
    __delay_ms(300);
    escreveLCD(2,"2..", 3);
    __delay_ms(300);
    escreveLCD(2,"1..", 6);
    __delay_ms(300);
    limpaLinha(2);
     escreveLCD(2,"INICIADO", 3);
    __delay_ms(100);
    jogo();
}

void jogo(){
    CCP2CON = 0x0A;
    T1CONbits.TMR1ON = 1;
    TMR1H = 0x00;       
    TMR1L = 0x00;
    limpaLCD();
    
    escreveLCD(1, " ", 0);
    escreveLCD(1, printSeta, 7);
    escreveLCD(2, printAlvo, 0);
}