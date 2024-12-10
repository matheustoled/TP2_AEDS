#include <stdio.h>
#include <stdlib.h>

#include "lista_sondas.c"

//função para gerar combinações
void gerarCombinacoes(RochaMineral array_elementos_combinacao[], 
                      int tam_total_array, 
                      int tam_combinacao_atual, 
                      int index_combinacao_atual, 
                      RochaMineral temp[], 
                      int i) {
    if (index_combinacao_atual == tam_combinacao_atual) {
        //quando a combinação estiver completa imprime
        printf("Combinacao:\n");
        for (int j = 0; j < tam_combinacao_atual; j++) {
            printf("Peso: %.2f, Valor: %d\n", temp[j].peso, temp[j].valor);
        }
        printf("\n");
        return;
    }

    if (i >= tam_total_array) {
        return;
    }

    temp[index_combinacao_atual] = array_elementos_combinacao[i];
    //inclui o próximo elemento na combinação
    gerarCombinacoes(array_elementos_combinacao, tam_total_array, tam_combinacao_atual, index_combinacao_atual + 1, temp, i + 1);
    //não incluir o próximo elemento na combinação
    gerarCombinacoes(array_elementos_combinacao, tam_total_array, tam_combinacao_atual, index_combinacao_atual, temp, i + 1);
}

//gerar todas as combinações de tamanhos diferentes
void gerarTodasCombinacoes(RochaMineral array_elementos_combinacao[], int tam_total_array) {
    for (int tam_combinacao_atual = 1; tam_combinacao_atual <= tam_total_array; tam_combinacao_atual++) {
        RochaMineral temp[tam_combinacao_atual];
        gerarCombinacoes(array_elementos_combinacao, tam_total_array, tam_combinacao_atual, 0, temp, 0);
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

int main() {
    //vetor para armazenar as rochas
    RochaMineral rochas[100];
    //compartimentos das sondas
    Compartimento comp_rochas1, comp_rochas2, comp_rochas3;
    FListaRochaM(&comp_rochas1, 40);
    FListaRochaM(&comp_rochas2, 40);
    FListaRochaM(&comp_rochas3, 40);
    int quantidade_rochas;

    //carrega as rochas a partir do arquivo
    quantidade_rochas = LerArquivo("entrada.txt", rochas);

    if (quantidade_rochas == 0) {
        printf("Nenhuma rocha foi carregada.\n");
        return 1;
    }

    //gera todas as combinações
    printf("Todas as combinacoes:\n");
    gerarTodasCombinacoes(rochas, quantidade_rochas);

    return 0;
}