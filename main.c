#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include "nxlcd.h"
#include "menu.h"
#include "menuSelect.h"
#include "jogo.h"
#include "musica.h"

#pragma config PLLDIV = 5 // PLL para 20MHz
#pragma config CPUDIV = OSC4_PLL6 // PLL desligado
#pragma config FOSC = HS // Fosc = 20MHz; Tcy = 200ns
#pragma config WDT = OFF // Watchdog timer desativado
#pragma config PBADEN = OFF // Pinos do PORTB come?am como digitais
#pragma config LVP = OFF // Desabilita grava??o em baixa tens?o
#pragma config DEBUG = OFF // Habilita debug

#define _XTAL_FREQ 20000000

#define SOL3 196
#define SOL3S 207
#define LA3 220
#define LA3S 233
#define SI3 247
#define DO4 261
#define DO4S 276
#define RE4 293
#define RE4S 310
#define MI4 329
#define FA4 349
#define FA4S 369
#define SOL4 392
#define SOL4S 415
#define LA4 440
#define LA4S 465
#define SI4 493
#define DO5 523
#define RE5 587
#define RE5S 622
#define MI5 659
#define FA5 698
#define FA5S 740
#define SOL5 784
#define SOL5S 830
#define LA5 880
#define LA5S 932
#define SI5 988

#define SMIN 200
#define MIN 100
#define COLC 50
#define SCOLC 25

int btCont = 0;
unsigned long counter = 0;
uint8_t posDiplay = 0;
uint8_t pontuacao = 0;

unsigned int vol = 99;
unsigned int dificuldade = 99;
unsigned int rodadas = 99;
unsigned int rodadaAtual = 1;
unsigned int duty = 6;


const unsigned int notas[] = {DO4, 441, DO4, SOL4, 441, 0};
    
const unsigned int erro[] = {SI3, LA3S, SOL3,441, 0};

const unsigned int vitoria[] = {DO4, MI4, SOL4, DO5,441, 0};

const unsigned int duracao_notas[] = {COLC, COLC, COLC, SMIN, 441, 0};
const unsigned int duracao_erro[] = {60, 60, 60, 441, 0};
const unsigned int duracao_vit[] = {MIN, MIN, MIN, MIN, 441, 0};
    

char string[16];

void finalizar(){
    T1CONbits.TMR1ON = 0;
    CCP2CON = 0x00;
    btCont = 0;
    vol = 99;
    dificuldade = 99;
    rodadas = 99;
    rodadaAtual = 1;
    pontuacao = 0;
    posDiplay = 0;
    menuPrincipal();
    counter = 0;
}

void __interrupt() HighISR(void){
    
//    if(INTCON3bits.INT1IF){
//        INTCON3bits.INT1IF = 0;
//    	finalizar();
//        
//	}
    
	if(INTCON3bits.INT1IF){
    	btCont++;
        
        switch(btCont){
            case 0:
                menuPrincipal();
                break;
            case 4:
                menuIniciar();
                break;
            case 5:
                duty = 10*(vol+1)/2;
                iniciarJogo();
                break;
        }

        if(btCont > 5){
            rodadaAtual++;
            WriteCmdXLCD(0x01);
            if(posDiplay == 8){
                pontuacao++;                
                escreveLCD(1,"Acertou",3);
                tocar_musica(vitoria, duracao_vit, duty);
            }
            else{
                escreveLCD(1,"Errou",5);
                tocar_musica(erro, duracao_vit, duty);
            }
            sprintf(string,"Pontuacao: %d",pontuacao);
            escreveLCD(2,string,2);
            
            if(rodadaAtual <= rodadas){
                posDiplay = 0;
                jogo();
            }
            else{
                limpaLCD();
                escreveLCD(1,"Fim de Jogo",2);
                sprintf(string,"Pontuacao: %d",pontuacao);
                escreveLCD(2,string,2);
                __delay_ms(4000);
                finalizar();
            }
        }
        
       INTCON3bits.INT1IF = 0;
	}
    
    if(PIR2bits.CCP2IF) {
        counter++;
        TMR1H = 0x00;       
        TMR1L = 0x00;
        int timer_mudar = (int)(34.762 * pow(rodadaAtual * dificuldade,-0.479));
        if((counter % timer_mudar) == 0){
            posDiplay = deslocaAlvo(posDiplay);
        }
        
        //sprintf(string,"%d",counter);
        //WriteCmdXLCD(0xC0);
        //putsXLCD(string);
        
        if(counter >= 300000) {
            T1CONbits.TMR1ON = 0;
            counter = 0;
            WriteCmdXLCD(0x01);
            WriteCmdXLCD(0x80);
            putsXLCD("Game Over");
            __delay_ms(1000);
            finalizar();
        }
        PIR2bits.CCP2IF = 0;
    }
}

void main(void) {
    
	initADCON();
    iniciaLCD();
    criaSetaAlvo();
    
	initInterupcao();
	menuPrincipal();
    
    configPWMinit();
    
    
	while(1) {
        switch(btCont){
            case 1:
            	dificuldade = menuDificuldade(dificuldade);
            	break;
           	 
        	case 2:
            	rodadas = menuRodadas(rodadas);
            	break;
           	 
        	case 3:
            	vol = menuVolMusica(vol);
                
            	break;
        }
        
        
	}
}


