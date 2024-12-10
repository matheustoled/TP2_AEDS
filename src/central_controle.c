#include <stdio.h>
#include <stdlib.h>

#include "headers/central_controle.h"

//funcao verificadora de pesos
void somar_pesos(RochaMineral temp[], int tam_combinacao_atual, RochaMineral *rochas_validas){
    float peso_total = 0;
    for(int i = 0; i < tam_combinacao_atual; i++){
        peso_total += temp[i].peso;
    }
    printf("PESO TOTAL: %f\n", peso_total);
    printf("\n");
    if(peso_total<=40){
        for(int j = 0; j < tam_combinacao_atual; j++){
            rochas_validas[j] = temp[j];
            printf("PESO ROCHA VALIDA: %f\nVALOR ROCHA VALIDA %d\n", rochas_validas[j].peso, rochas_validas[j].valor);
            printf("\n");
        }
    } else{
        printf("Combinacao Invalida\n");
    }
}

void soma_valores(RochaMineral *rochas_validas, int qnt_combinacoes_validas){
    int total_valores = 0;
    int melhor_valor = 0;
    for(int j = 0; j<qnt_combinacoes_validas; j++){
        total_valores += rochas_validas[j].valor;
        if(total_valores>melhor_valor){
            melhor_valor = total_valores;
        }
    }
    // for(int i = 0; i<qnt_combinacoes_validas; i++){
    //     printf("------------------------------------------\n");
    //     printf("MELHOR VALOR: %d\n", melhor_valor);
    //     printf("PESO DAS ROCHAS VALIDAS: %f\n", rochas_validas[i].peso);
    //     printf("VALORES DAS ROCHAS VALIDAS: %d\n", rochas_validas[i].valor);
    //     printf("------------------------------------------\n");
    // }
}

//função para gerar combinações
void gerarCombinacoes(RochaMineral array_elementos_combinacao[], 
                      int tam_total_array, 
                      int tam_combinacao_atual, 
                      int index_combinacao_atual, 
                      RochaMineral temp[], 
                      int i, 
                      RochaMineral *rochas_validas,
                      int qnt_combinacoes_validas) {
    if (index_combinacao_atual == tam_combinacao_atual) {
        //quando a combinação estiver completa imprime
        printf("====================\n");
        printf("Combinacao:\n");
        for (int j = 0; j < tam_combinacao_atual; j++) {
            somar_pesos(temp, tam_combinacao_atual, rochas_validas);
            soma_valores(rochas_validas, qnt_combinacoes_validas);
            for (int i = 0; i < tam_combinacao_atual; i++) {
                printf("%d", rochas_validas[i].valor);
            }
            printf("====================\n");
        }
        printf("\n");
        return;
    }

    if (i >= tam_total_array) {
        return;
    }

    temp[index_combinacao_atual] = array_elementos_combinacao[i];
    //inclui o próximo elemento na combinação
    gerarCombinacoes(array_elementos_combinacao, tam_total_array, tam_combinacao_atual, index_combinacao_atual + 1, temp, i + 1, rochas_validas, qnt_combinacoes_validas);
    //não incluir o próximo elemento na combinação
    gerarCombinacoes(array_elementos_combinacao, tam_total_array, tam_combinacao_atual, index_combinacao_atual, temp, i + 1, rochas_validas, qnt_combinacoes_validas);
}

//gerar todas as combinações de tamanhos diferentes
void gerarTodasCombinacoes(RochaMineral array_elementos_combinacao[], int tam_total_array, RochaMineral *rochas_validas, int qnt_combinacoes_validas) {
    for (int tam_combinacao_atual = 1; tam_combinacao_atual <= tam_total_array; tam_combinacao_atual++) {
        RochaMineral temp[tam_combinacao_atual];
        gerarCombinacoes(array_elementos_combinacao, tam_total_array, tam_combinacao_atual, 0, temp, 0, rochas_validas, qnt_combinacoes_validas);
    }
}

//funcao para ler arquivo
int LerArquivo(const char *nome_arquivo, RochaMineral rochas[]) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo\n");
        return 0;
    }

    int quantidade;
    fscanf(arquivo, "%d", &quantidade); //le a quantidade de rochas

    for (int i = 0; i < quantidade; i++) {
        fscanf(arquivo, "%f %d", &rochas[i].peso, &rochas[i].valor); //le peso e valor
    }

    fclose(arquivo);
    return quantidade;
}
