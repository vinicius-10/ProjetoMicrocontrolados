#ifndef __MENU_SELECT_H
#define __MENU_SELECT_H

#include "xc.h"

void initADCON();

unsigned int getADCON();

unsigned int getMenuOp(unsigned int adValue, unsigned int opCount);

unsigned int getMenuOpADCON(unsigned int opCount);

#endif
