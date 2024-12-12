#include <stdio.h>
#include <stdlib.h>

#include "headers/central_controle.h"

//funcao verificadora de pesos
void selecao_combinacoes_validas(RochaMineral temp[], int tam_combinacao_atual, RochaMineral *combinacoes_validas, int *qnt_combinacoes_validas){
    float peso_total = 0;
    int total_valores = 0;
    for(int i = 0; i < tam_combinacao_atual; i++){
        peso_total += temp[i].peso;
    }
    for(int j = 0; j< tam_combinacao_atual; j++){
        total_valores += temp[j].valor;
    }
    printf("PESO TOTAL: %f\n", peso_total);

    if(peso_total<=40){
        for(int i = 0; i<tam_combinacao_atual; i++){
            combinacoes_validas[*qnt_combinacoes_validas].id[i] = (int)temp[i].id;
        }
        combinacoes_validas[*qnt_combinacoes_validas].peso = peso_total;
        combinacoes_validas[*qnt_combinacoes_validas].valor = total_valores;
        printf("PESO ROCHA VALIDA: %f\nVALOR ROCHA VALIDA %d\n", combinacoes_validas[*qnt_combinacoes_validas].peso, combinacoes_validas[*qnt_combinacoes_validas].valor);
        printf("\n");
        *qnt_combinacoes_validas += 1;
    } else{
        printf("Combinacao Invalida\n");
    }
}

//função para gerar combinações
void gerarCombinacoes(RochaMineral array_elementos_combinacao[], 
                      int tam_total_array, 
                      int tam_combinacao_atual, 
                      int index_combinacao_atual, 
                      RochaMineral temp[], 
                      int i, 
                      RochaMineral *combinacoes_validas,
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
void gerarTodasCombinacoes(RochaMineral array_elementos_combinacao[], int tam_total_array, RochaMineral *combinacoes_validas, int *qnt_combinacoes_validas) {
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

void distribuicao_rochas(RochaMineral *combinacoes_validas, int qnt_combinacoes_validas) {
    printf("iniciou\n");
    Compartimento comp_sonda1, comp_sonda2, comp_sonda3;
    FListaRochaM(&comp_sonda1, 40); // Inicializa compartimento da sonda 1
    FListaRochaM(&comp_sonda2, 40); // Inicializa compartimento da sonda 2
    FListaRochaM(&comp_sonda3, 40); // Inicializa compartimento da sonda 3
    int remocao = 0;
    int ids_para_remover[]

    int combinacoes_usadas[qnt_combinacoes_validas];
    for (int i = 0; i < qnt_combinacoes_validas; i++) {
        combinacoes_usadas[i] = 0; // Inicializa o array para rastrear combinações já usadas
    }

    Compartimento *sondas[] = {&comp_sonda1, &comp_sonda2, &comp_sonda3};

    for (int sonda_idx = 0; sonda_idx < 3; sonda_idx++) {
        int melhor_comb_idx = -1;
        double melhor_valor = 0;

        // Encontrar a melhor combinação para a sonda atual
        for (int i = 0; i < qnt_combinacoes_validas; i++) {
            if (combinacoes_usadas[i]) {
                continue; // Pula combinações já usadas
            }

            if (combinacoes_validas[i].peso <= 40 && combinacoes_validas[i].valor > melhor_valor) {
                melhor_comb_idx = i;
                melhor_valor = combinacoes_validas[i].valor;
            }
        }

        if (melhor_comb_idx != -1) {
            // Inserir a melhor combinação na sonda
            InsereRochaM(sondas[sonda_idx], &combinacoes_validas[melhor_comb_idx], 40);
            while(remocao!=1){
                printf("entrou no while... aq fudeu\n");
                for(int i = 0; i<qnt_combinacoes_validas; i++){
                    printf("entrou no segundo for e combinacoes_validas ta certo\n");
                    int qnt_ids = sizeof(combinacoes_validas[i].id)/sizeof(combinacoes_validas[i].id[0]);
                    for(int j = 0; j<qnt_ids; j++){
                        printf("teste\n");
                        if(combinacoes_validas[i].id[j] == comp_sonda1.pPrimeiro->pProx->rocha.id[j]){
                            remocao = 1;
                            printf("teste\n");
                            
                        } else {
                            remocao = 0;
                        }
                    }
                }
            }
        } else {
            printf("Nenhuma combinacao valida encontrada para a sonda %d.\n", sonda_idx + 1);
        }
    }

    // Imprime os resultados para as sondas
    printf("Conteudo da Sonda 1:\n");
    ImprimeListaRochaM(&comp_sonda1);
    printf("Conteudo da Sonda 2:\n");
    ImprimeListaRochaM(&comp_sonda2);
    printf("Conteudo da Sonda 3:\n");
    ImprimeListaRochaM(&comp_sonda3);
}
