#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h>
#include "menuSelect.h"

    void limpaLCD();
    void iniciaLCD();
    void escreveLCD(int linha, char msg[], int cursor);
    unsigned int menuVolMusica(unsigned int vol);
    unsigned int menuRodadas(unsigned int rodadas);
    unsigned int menuDificuldade(unsigned int dif);
    void menuPrincipal();
    void initInterupcao();
    void limpaLinha(int linha);
    void jogo();
#endif