#include <stdio.h>
#include <stdlib.h>
#include "headers/Lista_Sondas.h"

void FLVaziaLS(Lista_Sondas *LS){
    LS->pPrimeiro = (CelulaLS*)malloc(sizeof(CelulaLS));
    LS->pUltimo = LS->pPrimeiro;
    LS->pPrimeiro->pProx = NULL;
}

int LEhVaziaLS(Lista_Sondas *LS){
    return(LS->pPrimeiro == LS->pUltimo);
}

int InsereSondaLS(Lista_Sondas *LS, Sonda *s){
    LS->pUltimo->pProx = (CelulaLS*)malloc(sizeof(CelulaLS));
    LS->pUltimo = LS->pUltimo->pProx;
    LS->pUltimo->sonda = *s;
    LS->pUltimo->pProx = NULL;
    return 1;
}

void ImprimeLS(Lista_Sondas *LS) {
    CelulaLS *pAtual = LS->pPrimeiro->pProx;
    int cnt = 1;

    while (pAtual != NULL) {
        printf("Sonda %d:\n", cnt);

        //verifica se o compartimento da sonda tem rochas
        if (LEhVaziaRochaM(&pAtual->sonda.CompSonda)) {
            printf("Compartimento vazio\n");
        } else {
            ImprimeListaRochaM(&pAtual->sonda.CompSonda);
        }

        pAtual = pAtual->pProx;
        cnt++;
    }
}