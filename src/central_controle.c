#include <stdio.h>
#include <stdlib.h>

#include "headers/central_controle.h"

//funcao verificadora de pesos
void selecao_combinacoes_validas(RochaMineral temp[], int tam_combinacao_atual, CombinacaoValida *combinacoes_validas, int *qnt_combinacoes_validas){
    float peso_total = 0;
    int total_valores = 0;

    for (int i = 0; i < tam_combinacao_atual; i++) {
        peso_total += temp[i].peso;
        total_valores += temp[i].valor;
    }
    //TODO: printf("PESO TOTAL: %f\n", peso_total);

    if(peso_total<=40){
        combinacoes_validas[*qnt_combinacoes_validas].peso = peso_total;
        combinacoes_validas[*qnt_combinacoes_validas].valor = total_valores;
        //TODO: printf("PESO ROCHA VALIDA: %f\nVALOR ROCHA VALIDA %d\n", combinacoes_validas[*qnt_combinacoes_validas].peso, combinacoes_validas[*qnt_combinacoes_validas].valor);
        //TODO: printf("\n");
        *qnt_combinacoes_validas += 1;
    } else{
        //TODO: printf("Combinacao Invalida\n");
    }
}

//função para gerar combinações
void gerarCombinacoes(RochaMineral array_elementos_combinacao[], 
                      int tam_total_array, 
                      int tam_combinacao_atual, 
                      int index_combinacao_atual, 
                      RochaMineral temp[], 
                      int i, 
                      CombinacaoValida *combinacoes_validas,
                      int *qnt_combinacoes_validas) {
    if (index_combinacao_atual == tam_combinacao_atual) {
        //quando a combinação estiver completa imprime
        printf("====================\n");
        printf("Combinacao:\n");
        selecao_combinacoes_validas(temp, tam_combinacao_atual, combinacoes_validas, qnt_combinacoes_validas);
        printf("\n");
        return;
    }

    if (i >= tam_total_array) {
        return;
    }

    temp[index_combinacao_atual] = array_elementos_combinacao[i];
    //inclui o próximo elemento na combinação
    gerarCombinacoes(array_elementos_combinacao, tam_total_array, tam_combinacao_atual, index_combinacao_atual + 1, temp, i + 1, combinacoes_validas, qnt_combinacoes_validas);
    //não incluir o próximo elemento na combinação
    gerarCombinacoes(array_elementos_combinacao, tam_total_array, tam_combinacao_atual, index_combinacao_atual, temp, i + 1, combinacoes_validas, qnt_combinacoes_validas);
}

//gerar todas as combinações de tamanhos diferentes
void gerarTodasCombinacoes(RochaMineral array_elementos_combinacao[], int tam_total_array, CombinacaoValida *combinacoes_validas, int *qnt_combinacoes_validas) {
    for (int tam_combinacao_atual = 1; tam_combinacao_atual <= tam_total_array; tam_combinacao_atual++) {
        RochaMineral temp[tam_combinacao_atual];
        gerarCombinacoes(array_elementos_combinacao, tam_total_array, tam_combinacao_atual, 0, temp, 0, combinacoes_validas, qnt_combinacoes_validas);
    }
}

//funcao para ler arquivo
int LerArquivo(char *nome_arquivo, RochaMineral rochas[]) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo\n");
        return 0;
    }

    int quantidade;
    fscanf(arquivo, "%d", &quantidade); //le a quantidade de rochas

    for (int i = 0; i < quantidade; i++) {
        preencher_rocha_mineral(arquivo, i, rochas);
    }

    fclose(arquivo);
    return quantidade;
}

// Função para ordenar as rochas por valor (ordem decrescente)
int compara_valor(const void *a, const void *b) {
    RochaMineral *rocha_a = (RochaMineral*)a;
    RochaMineral *rocha_b = (RochaMineral*)b;
    
    // Ordena de forma decrescente com base no valor
    if (rocha_a->valor < rocha_b->valor) {
        return 1;
    } else if (rocha_a->valor > rocha_b->valor) {
        return -1;
    }
    return 0;
}

void distribuicao_rochas(RochaMineral *combinacoes_validas, int qnt_combinacoes_validas) {
    Compartimento comp_sonda1, comp_sonda2, comp_sonda3;
    FListaRochaM(&comp_sonda1, 40); // Inicializa compartimento da sonda 1
    FListaRochaM(&comp_sonda2, 40); // Inicializa compartimento da sonda 2
    FListaRochaM(&comp_sonda3, 40); // Inicializa compartimento da sonda 3

    // Ordena as rochas por valor (decrescente)
    qsort(combinacoes_validas, qnt_combinacoes_validas, sizeof(RochaMineral), compara_valor);

    int i;
    for (i = 0; i < qnt_combinacoes_validas; i++) {
        // Tente adicionar rochas às sondas, verificando o peso máximo e priorizando o valor
        if (!InsereRochaM(&comp_sonda1, &combinacoes_validas[i], 40)) {
            if (!InsereRochaM(&comp_sonda2, &combinacoes_validas[i], 40)) {
                if (!InsereRochaM(&comp_sonda3, &combinacoes_validas[i], 40)) {
                    printf("Nao foi possivel inserir a rocha de valor %d e peso %.2f em nenhuma sonda.\n", combinacoes_validas[i].valor, combinacoes_validas[i].peso);
                }
            }
        }
    }

    // Imprime os resultados para as sondas
    printf("Conteúdo da Sonda 1:\n");
    ImprimeListaRochaM(&comp_sonda1);
    printf("Conteúdo da Sonda 2:\n");
    ImprimeListaRochaM(&comp_sonda2);
    printf("Conteúdo da Sonda 3:\n");
    ImprimeListaRochaM(&comp_sonda3);
}
