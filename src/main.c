#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "headers/central_controle.h"

long long combinacao(int n, int k) {
    if (k > n - k) k = n - k; // Usa o menor entre k e (n-k) para reduzir o número de operações
    long long resultado = 1;
    for (int i = 0; i < k; i++) {
        resultado = resultado * (n - i) / (i + 1); // Calcula diretamente o coeficiente binomial
    }
    return resultado;
}

int main() {
    clock_t start, end;
    double cpu_time_used;

    start = clock(); // Início da medição
    //vetor para armazenar as rochas
    RochaMineral rochas[100];
    int quantidade_rochas;
    int qnt_combinacoes_validas = 0;
    int quantidade_combinacoes = 0;

    //carrega as rochas a partir do arquivo
    quantidade_rochas = LerArquivo("entrada.txt", rochas);

    for(int i = 1; i <= quantidade_rochas; i++){
        quantidade_combinacoes += combinacao(quantidade_rochas, i);
    }

    //vetor para armazenar as combinacoes validas
    CombinacaoValida *combinacoes_validas = malloc(quantidade_combinacoes * sizeof(CombinacaoValida));
    if (combinacoes_validas == NULL) {
        printf("Erro ao alocar memoria para combinacoes validas.\n");
    return 1;
    }

    if (quantidade_rochas == 0) {
        printf("Nenhuma rocha foi carregada.\n");
        return 1;
    }

    //gera todas as combinações
    printf("Todas as combinacoes:\n");
    gerarTodasCombinacoes(rochas, quantidade_rochas, combinacoes_validas, &qnt_combinacoes_validas);
    printf("\n\n\n");

    distribuicao_rochas(combinacoes_validas, qnt_combinacoes_validas);
    free(combinacoes_validas);

    end = clock(); // Fim da medição

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; // Tempo em segundos
    printf("Tempo de execucao: %.3f segundos\n", cpu_time_used);
    return 0;
}