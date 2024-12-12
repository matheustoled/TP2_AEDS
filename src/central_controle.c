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

    if (peso_total <= 40) {
        CombinacaoValida *nova_comb = &combinacoes_validas[*qnt_combinacoes_validas];
        nova_comb->peso = peso_total;
        nova_comb->valor = total_valores;
        nova_comb->qtd_rochas = tam_combinacao_atual;

        for (int i = 0; i < tam_combinacao_atual; i++) {
            nova_comb->rochas[i] = temp[i];
        }

        (*qnt_combinacoes_validas)++;

        printf("Nova combinacao valida: Peso=%.2f, Valor=%d, Rochas={", peso_total, total_valores);
        for (int i = 0; i < tam_combinacao_atual; i++) {
            printf("(%.2f, %d) ", temp[i].peso, temp[i].valor);
        }
        printf("}\n");
    }
}

    // for(int i = 0; i<qnt_combinacoes_validas; i++){
    //     printf("------------------------------------------\n");
    //     printf("MELHOR VALOR: %d\n", melhor_valor);
    //     printf("PESO DAS ROCHAS VALIDAS: %f\n", combinacoes_validas[i].peso);
    //     printf("VALORES DAS ROCHAS VALIDAS: %d\n", combinacoes_validas[i].valor);
    //     printf("------------------------------------------\n");
    // }

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
        //TODO: printf("====================\n");
        //TODO: printf("Combinacao:\n");
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
        //TODO: printf("Erro ao abrir o arquivo\n");
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

void remover_combinacoes_usadas(CombinacaoValida *combinacoes_validas, int *qnt_combinacoes_validas, RochaMineral *rochas_usadas, int qnt_rochas_usadas) {
    int i = 0;
    while (i < *qnt_combinacoes_validas) {
        int remove_comb = 0;

        for (int j = 0; j < qnt_rochas_usadas; j++) {
            for (int k = 0; k < combinacoes_validas[i].qtd_rochas; k++) {
                if (combinacoes_validas[i].rochas[k].peso == rochas_usadas[j].peso &&
                    combinacoes_validas[i].rochas[k].valor == rochas_usadas[j].valor) {
                    remove_comb = 1;
                    break;
                }
            }
            if (remove_comb) break;
        }

        if (remove_comb) {
            for (int j = i; j < *qnt_combinacoes_validas - 1; j++) {
                combinacoes_validas[j] = combinacoes_validas[j + 1];
            }
            (*qnt_combinacoes_validas)--;
        } else {
            i++;
        }
    }
}

void distribuicao_rochas(CombinacaoValida *combinacoes_validas, int qnt_combinacoes_validas) {
    Compartimento comp_sonda1, comp_sonda2, comp_sonda3;
    FListaRochaM(&comp_sonda1, 40);
    FListaRochaM(&comp_sonda2, 40);
    FListaRochaM(&comp_sonda3, 40);

    Compartimento *sondas[] = {&comp_sonda1, &comp_sonda2, &comp_sonda3};

    RochaMineral rochas_usadas[40];
    int qnt_rochas_usadas = 0;

    for (int sonda_idx = 0; sonda_idx < 3; sonda_idx++) {
        int melhor_comb_idx = -1;
        double melhor_valor = 0;

        for (int i = 0; i < qnt_combinacoes_validas; i++) {
            if (combinacoes_validas[i].peso <= 40 && combinacoes_validas[i].valor > melhor_valor) {
                melhor_comb_idx = i;
                melhor_valor = combinacoes_validas[i].valor;
            }
        }

        if (melhor_comb_idx != -1) {
            CombinacaoValida *melhor_comb = &combinacoes_validas[melhor_comb_idx];
            for (int r = 0; r < melhor_comb->qtd_rochas; r++) {
                rochas_usadas[qnt_rochas_usadas++] = melhor_comb->rochas[r];
            }

            if (!InsereCombinacao(sondas[sonda_idx], combinacoes_validas[melhor_comb_idx].rochas, combinacoes_validas[melhor_comb_idx].qtd_rochas)) {
                printf("Erro ao inserir na sonda %d.\n", sonda_idx + 1);
            }

            remover_combinacoes_usadas(combinacoes_validas, &qnt_combinacoes_validas, rochas_usadas, qnt_rochas_usadas);
        }
    }
    printf("sonda1\n");
    ImprimeListaRochaM(&comp_sonda1);
    printf("sonda2\n");
    ImprimeListaRochaM(&comp_sonda2);
    printf("sonda3\n");
    ImprimeListaRochaM(&comp_sonda3);
}