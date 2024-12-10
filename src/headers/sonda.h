#ifndef SONDA_H_INCLUDED
#define SONDA_H_INCLUDED

#include "compartimento.h"

typedef struct Sonda
{
    Compartimento CompSonda;
}Sonda;

//Inicializa sonda
void Inicializar(Sonda* sonda, Compartimento *comp);

#endif // SONDA_H_INCLUDED