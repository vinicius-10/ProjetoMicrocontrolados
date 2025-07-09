
#ifndef JOGO_H
#define	JOGO_H

#include <xc.h>

    char printAlvo[2] = {2, '\0'};
    char printSeta[2] = {1, '\0'};

    uint8_t deslocaAlvo(uint8_t pos);
    void LoadCustomChar(unsigned char location, unsigned char *charmap);
    void criaSetaAlvo();
    void menuIniciar();
    void iniciarJogo();
#endif

