#ifndef LISTA_SONDAS_H
#define LISTA_SONDAS_H

#include "SONDA.h"

typedef struct CelulaLS
{
    Sonda sonda;
    struct CelulaLS *pProx;
}CelulaLS;

typedef struct Lista_Sondas
{
    CelulaLS* pPrimeiro;
    CelulaLS* pUltimo;
}Lista_Sondas;

void FLVaziaLS(Lista_Sondas *LS);
int LEhVaziaLS(Lista_Sondas *LS);
int InsereSondaLS(Lista_Sondas *LS, Sonda *s);
int RetiraSondaLS(Lista_Sondas *LS, int id, Sonda s);
void ImprimeLS(Lista_Sondas *LS);

#endif //LISTA_SONDAS_H