#include <stdio.h>

void gerarCombinacoes(int array_elementos_combinacao[] /*array original com os elementos que queremos combinar*/, 
                      int tam_total_array              /*tamanho total do array*/, 
                      int tam_combinacao_atual         /*tamanho da combinação atual que estamos construindo*/, 
                      int index_combinacao_atual       /*índice na combinação atual que estamos preenchendo*/, 
                      int temp[]                       /*array temporário para armazenar a combinação atual*/, 
                      int i                            /*índice no array original (arr[]) que estamos considerando*/
                      ) {
    if (index_combinacao_atual == tam_combinacao_atual) {
        for (int j = 0; j < tam_combinacao_atual; j++) {
            printf("%d \n", temp[j]);
            printf("index da combinacao atual:%d \n", index_combinacao_atual);
            printf("tamanho da combinacao atual:%d \n", tam_combinacao_atual);
            printf("\n");
        }
        printf("\n");
        return;
    }

    if (i >= tam_total_array) {
        return;
    }

    temp[index_combinacao_atual] = array_elementos_combinacao[i];
    gerarCombinacoes(array_elementos_combinacao, tam_total_array, tam_combinacao_atual, index_combinacao_atual + 1, temp, i + 1);

    gerarCombinacoes(array_elementos_combinacao, tam_total_array, tam_combinacao_atual, index_combinacao_atual, temp, i + 1);
}

void gerarTodasCombinacoes(int array_elementos_combinacao[], int tam_total_array) {
    for (int tam_combinacao_atual = 1; tam_combinacao_atual <= tam_total_array; tam_combinacao_atual++) {
        int temp[tam_combinacao_atual]; 
        gerarCombinacoes(array_elementos_combinacao, tam_total_array, tam_combinacao_atual, 0, temp, 0);
    }
}

int main() {
    int array_elementos_combinacao[] = {1, 2, 3, 4};
    int tam_total_array = sizeof(array_elementos_combinacao) / sizeof(array_elementos_combinacao[0]);

    printf("Todas as combinacoes:\n");
    gerarTodasCombinacoes(array_elementos_combinacao, tam_total_array);

    return 0;
}