#include <stdio.h>
#include <stdlib.h>

#include "lista_sondas.c"

// Função para gerar combinações
void gerarCombinacoes(RochaMineral array_elementos_combinacao[], 
                      int tam_total_array, 
                      int tam_combinacao_atual, 
                      int index_combinacao_atual, 
                      RochaMineral temp[], 
                      int i) {
    if (index_combinacao_atual == tam_combinacao_atual) {
        // Quando a combinação estiver completa, imprimimos
        printf("Combinacao:\n");
        for (int j = 0; j < tam_combinacao_atual; j++) {
            printf("Peso: %.2f, Valor: %d\n", temp[j].peso, temp[j].valor);
        }
        printf("\n");
        return;
    }

    if (i >= tam_total_array) {
        return;  // Paramos se chegarmos ao final do array
    }

    // Colocamos o elemento atual na combinação
    temp[index_combinacao_atual] = array_elementos_combinacao[i];
    
    // Chamada recursiva para incluir o próximo elemento na combinação
    gerarCombinacoes(array_elementos_combinacao, tam_total_array, tam_combinacao_atual, index_combinacao_atual + 1, temp, i + 1);

    // Chamada recursiva para não incluir o próximo elemento na combinação
    gerarCombinacoes(array_elementos_combinacao, tam_total_array, tam_combinacao_atual, index_combinacao_atual, temp, i + 1);
}

// Função para gerar todas as combinações de tamanhos diferentes
void gerarTodasCombinacoes(RochaMineral array_elementos_combinacao[], int tam_total_array) {
    for (int tam_combinacao_atual = 1; tam_combinacao_atual <= tam_total_array; tam_combinacao_atual++) {
        RochaMineral temp[tam_combinacao_atual];
        gerarCombinacoes(array_elementos_combinacao, tam_total_array, tam_combinacao_atual, 0, temp, 0);
    }
}

// Função para carregar as rochas a partir de um arquivo
int LerArquivo(const char *nome_arquivo, RochaMineral rochas[]) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo\n");
        return 0;
    }

    int quantidade;
    fscanf(arquivo, "%d", &quantidade); // Lê a quantidade de rochas

    for (int i = 0; i < quantidade; i++) {
        fscanf(arquivo, "%f %d", &rochas[i].peso, &rochas[i].valor); // Lê peso e valor
    }

    fclose(arquivo);
    return quantidade;
}

int main() {
    // Array para armazenar as rochas
    RochaMineral rochas[100];
    Compartimento comp_rochas1, comp_rochas2, comp_rochas3;
    FListaRochaM(&comp_rochas1, 40);
    FListaRochaM(&comp_rochas2, 40);
    FListaRochaM(&comp_rochas3, 40);
    int quantidade_rochas;

    // Carrega as rochas a partir do arquivo
    quantidade_rochas = LerArquivo("entrada.txt", rochas);

    if (quantidade_rochas == 0) {
        printf("Nenhuma rocha foi carregada.\n");
        return 1;
    }

    // Gera todas as combinações
    printf("Todas as combinacoes:\n");
    gerarTodasCombinacoes(rochas, quantidade_rochas);

    return 0;
}