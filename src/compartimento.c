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

int InsereCombinacao(Compartimento *LRM, RochaMineral *combinacao, int qtd_rochas) {
    for (int i = 0; i < qtd_rochas; i++) {
        if (!InsereRochaM(LRM, &combinacao[i], 40)) {
            return 0; // Falha ao inserir a combinação
        }
    }
    return 1; // Sucesso
}

int InsereRochaM(Compartimento *LRM, RochaMineral *rocha_validas, int PesoMax) {
    double pesoAtual = PesoAtual(LRM);
    if (pesoAtual + rocha_validas->peso > LRM->pesoMAX) {
        return 0; // Não pode inserir porque o peso ultrapassa o limite
    }

    // Insere a rocha no compartimento
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