#include <xc.h>
#include <stdint.h>
#include "nxlcd.h"
#include <stdio.h>
#include <string.h>
#include "menu.h"

void initInterupcao(){
	INTCONbits.GIEH = 1; // habilita todas as interrup??es do INTCON
    INTCONbits.GIEL = 1; // habilita as baixa prioridade 
    
	INTCONbits.INT0IE = 1; // habilita interrup??o bot?o RB0
	INTCON3bits.INT1IE = 1; // habilita interrup??o bot?o RB1
    
	INTCONbits.INT0IF = 0; // zera flag de interrup??o INT0
	INTCON3bits.INT1IF = 0; // zera flag de interrup??o INT1
    
	INTCON2bits.INTEDG0 = 1;//disparar ao soltar o bot?o
	INTCON2bits.INTEDG1 = 1;//disparar ao soltar o bot?o
    
    PIE1bits.ADIE = 0; //interup??o do conversor ad
    
    CCP2CON = 0x00; //0x0A modo de comparacao apenas
    
    T3CONbits.T3CCP2 = 0;//timer 1 
    T3CONbits.T3CCP1 = 0;//timer 1
    PIE2bits.CCP2IE = 1; //abilita a interup??o
    PIR2bits.CCP2IF = 0; //limpa flag de interup??o
    
    CCPR2H = 0x04; //valor corespondente a 5 000 para tempo de 0,001 s
    CCPR2L = 0xE2;
    
    T1CON = 0b10000000; 
    TMR1H = 0x00;       
    TMR1L = 0x00;
    
    TRISC = 0x00;
    
}

void limpaLCD(){
	WriteCmdXLCD(0x01);
}

void limpaLinha(int linha){
    if(linha == 1){
        WriteCmdXLCD(0x80);
        putsXLCD("                ");
	}
	if(linha == 2){
        WriteCmdXLCD(0xC0);
        putsXLCD("                ");
	}
}

void iniciaLCD(){
    TRISD = 0x00;
    TRISE = 0b11111010;
	OpenXLCD(FOUR_BIT & LINES_5X7); //4 bits + tamanho caracteres
    WriteCmdXLCD(CURSOR_OFF & BLINK_OFF);
    while(BusyXLCD());
    limpaLCD();
}

void escreveLCD(int linha, char msg[17], int cursor){
    SetDDRamAddr(0x00); 
    
	if(linha == 1){
    	WriteCmdXLCD(0x80 + cursor);
    	putsXLCD(msg);
	}
	if(linha == 2){
    	WriteCmdXLCD(0xC0 + cursor);
    	putsXLCD(msg);
	}
}

unsigned int menuVolMusica(unsigned int vol){
    unsigned int op = 0;
    
    op =  getMenuOpADCON(11);
    
    if(op != vol) {
        limpaLCD();
        escreveLCD(1, "Volume: ", 0);
        char buffer[3];
        sprintf(buffer, "%d", op);
        escreveLCD(1, buffer, 8);    
    }
    return op;
}

unsigned int menuRodadas(unsigned int rodadas){
    unsigned int op = 0;
    op =  getMenuOpADCON(7) + 1;
    
    if(op != rodadas) {
        limpaLCD();
        escreveLCD(1,"Tentativas:", 0);
        char buffer[2];
        sprintf(buffer, "%d", op);
        escreveLCD(1, buffer, 12);    
    }
    
    return op;
}

unsigned int menuDificuldade(unsigned int dif){
    unsigned int op = 0;
    op =  getMenuOpADCON(4);
    
    if(dif != op) {
        //limpaLCD();
        escreveLCD(1,"Dificuldade:", 0);
        limpaLinha(2);
        switch(op) {
            case 0:
                escreveLCD(2, "Facil", 0);
                break;
            case 1:
                escreveLCD(2, "Normal", 0);
                break;
            case 2:
                escreveLCD(2, "Medio", 0);
                break;
            case 3:
                escreveLCD(2, "Dificil", 0);
                break;
        }
    }
    return op;
}

void menuPrincipal(){
	limpaLCD();
	escreveLCD(1,"INT1 para", 0);
	escreveLCD(2,"Entrar...", 0);
    
}


