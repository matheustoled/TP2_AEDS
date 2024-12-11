#include <stdio.h>
#include <stdlib.h>

#include "headers/compartimento.h"

void FListaRochaM(Compartimento *LRM, int pesoMAX){
    LRM->pPrimeiro = (CelulaC*)malloc(sizeof(CelulaC));
    LRM->pUltimo = LRM->pPrimeiro;
    LRM->pPrimeiro->pProx = NULL;
    LRM->pesoMAX = pesoMAX;
}

int LEhVaziaRochaM(Compartimento *LRM){
    return(LRM->pPrimeiro == LRM->pUltimo);
}

double PesoAtual(Compartimento *LRM){
    double peso = 0;
    if (LEhVaziaRochaM(LRM))
    {
        return 0;
    }

    CelulaC *pAux;
    
    for(pAux = LRM->pPrimeiro->pProx; pAux != NULL; pAux = pAux->pProx)
    {
        peso += (pAux->rocha.peso);
    }
    return peso;
}

int InsereRochaM(Compartimento *LRM, RochaMineral *rocha_validas, int PesoMax) {
    double pesoAtual = PesoAtual(LRM); // Calcula o peso atual das rochas no compartimento
    if (pesoAtual + rocha_validas->peso > PesoMax) {
        return 0; // Não pode inserir porque o peso ultrapassa o limite
    }

    // Se não ultrapassar o peso máximo, insere a rocha
    LRM->pUltimo->pProx = (CelulaC*) malloc(sizeof(CelulaC));
    LRM->pUltimo = LRM->pUltimo->pProx;
    LRM->pUltimo->rocha = *rocha_validas;
    LRM->pUltimo->pProx = NULL;

    return 1;
}

void ImprimeListaRochaM(Compartimento *LRM){
    CelulaC *pAuxI;
    pAuxI = LRM->pPrimeiro->pProx;
    while (pAuxI != NULL)
    {
        printf("Peso: %.2f\n", pAuxI->rocha.peso);
        printf("Valor: %d\n", pAuxI->rocha.valor);
        printf("\n");
        pAuxI = pAuxI->pProx;
    }
}