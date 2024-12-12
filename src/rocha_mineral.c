#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/rocha_mineral.h"

// Inicializar nova rocha
void inicializar_rocha_mineral(RochaMineral *nova_rocha, float novo_peso, int novo_valor){
    set_peso(nova_rocha, novo_peso);
    set_valor(nova_rocha, novo_valor);
}

//gets
float get_peso(RochaMineral *nova_rocha){
    return(nova_rocha->peso);
}
int get_valor(RochaMineral *nova_rocha){
    return(nova_rocha->valor);
}

//sets
void set_peso(RochaMineral *nova_rocha, float novo_peso){
    nova_rocha->peso = novo_peso;
}
void set_valor(RochaMineral *nova_rocha, int novo_valor){
    nova_rocha->valor = novo_valor;
}

void preencher_rocha_mineral(FILE *arquivo, RochaMineral *nova_rocha){
    float peso = 0;
    float valor = 0;

    char entrada_dados[255];

    printf("Insira os dados da rocha: ");
    fgets(entrada_dados, 255, arquivo);  // Lê tudo em uma única linha

    // Remove a quebra de linha, se houver
    size_t len = strlen(entrada_dados);
    if (len > 0 && entrada_dados[len - 1] == '\n') {
        entrada_dados[len - 1] = '\0';
    }

    // Usando strtok para dividir os dados na linha
    char *token = strtok(entrada_dados, " ");
    
    // Lê o peso
    token = strtok(NULL, " ");
    peso = atof(token); //Converte para float

    // Lê o valor da rocha
    valor = atoi(token); //Converte para int

    // Inicializa a rocha mineral com os dados
    inicializar_rocha_mineral(nova_rocha, peso, valor);
}

void imprimir_rocha_mineral(RochaMineral *nova_rocha){

    char categoria_imprimir[255];

    printf("\nPeso: %.2f", nova_rocha->peso);
    printf("\nValor: %d", nova_rocha->valor);
}