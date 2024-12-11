#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "headers/central_controle.h"

// Função para calcular o fatorial
    long long fatorial(int n) {
    long long resultado = 1;
    for (int i = 1; i < n; i++) {  // Loop até n
        resultado *= i;
    }
    return resultado;
    }

    // Função para calcular quantidade de combinações
    long long combinacao(int n, int k) {
    return fatorial(n) / (fatorial(k) * fatorial(n - k));
}

int main() {
    //vetor para armazenar as rochas
    RochaMineral rochas[100];
    int quantidade_rochas;
    int qnt_combinacoes_validas = 0;

    //carrega as rochas a partir do arquivo
    quantidade_rochas = LerArquivo("entrada.txt", rochas);

    //vetor para armazenar as combinacoes validas
    RochaMineral combinacoes_validas[combinacao(quantidade_rochas, 3)];

    if (quantidade_rochas == 0) {
        printf("Nenhuma rocha foi carregada.\n");
        return 1;
    }

    //gera todas as combinações
    printf("Todas as combinacoes:\n");
    gerarTodasCombinacoes(rochas, quantidade_rochas, combinacoes_validas, &qnt_combinacoes_validas);
    printf("\n\n\n");
    //TODO:for (int i = 0; i < qnt_combinacoes_validas; i++) {
    //TODO:    printf("Combinacao: %d\nPeso: %f\nValor: %d\n...\n", i, combinacoes_validas[i].peso, combinacoes_validas[i].valor);
    //TODO:}

    distribuicao_rochas(combinacoes_validas, qnt_combinacoes_validas);
    return 0;
}