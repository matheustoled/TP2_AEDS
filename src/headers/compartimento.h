#ifndef COMPARTIMENTO_H
#define COMPARTIMENTO_H
#include "rocha_mineral.h"

typedef struct CelulaC
{
    RochaMineral rocha;
    struct CelulaC *pProx;
}CelulaC;

typedef struct Compartimento
{
    float pesoMAX;
    CelulaC *pPrimeiro;
    CelulaC *pUltimo;
}Compartimento;

void FListaRochaM(Compartimento *LRM, int pesoMAX);
int LEhVaziaRochaM(Compartimento *LRM);
double PesoAtual(Compartimento *LRM);
int InsereRochaM(Compartimento *LRM, RochaMineral *RochaM, int pesoMAX);
void ImprimeListaRochaM(Compartimento *LRM);

 
#endif //COMPARTIMENTO_H