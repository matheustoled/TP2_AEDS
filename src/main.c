#include <stdio.h>
#include <stdlib.h>

#include "headers/central_controle.h"

int main() {
    //vetor para armazenar as rochas
    RochaMineral rochas[100];
    //compartimentos das sondas
    Compartimento comp_rochas1, comp_rochas2, comp_rochas3;
    FListaRochaM(&comp_rochas1, 40);
    FListaRochaM(&comp_rochas2, 40);
    FListaRochaM(&comp_rochas3, 40);
    int quantidade_rochas;
    int qnt_combinacoes_validas = 0;

    //carrega as rochas a partir do arquivo
    quantidade_rochas = LerArquivo("entrada.txt", rochas);
    //vetor para armazenar as rochas validas
    RochaMineral rochas_validas[quantidade_rochas];

    if (quantidade_rochas == 0) {
        printf("Nenhuma rocha foi carregada.\n");
        return 1;
    }

    //gera todas as combinações
    printf("Todas as combinacoes:\n");
    gerarTodasCombinacoes(rochas, quantidade_rochas, rochas_validas, qnt_combinacoes_validas);
    
    return 0;
}