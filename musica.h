
#ifndef MUSICA_H
#define	MUSICA_H

#include <xc.h>

    void tocar_musica(const unsigned int* notas, const unsigned int* duracao, unsigned int duty);
    void configPR2(unsigned int nota_hz, unsigned int duty_percent);
    void configPWMinit();
#endif

