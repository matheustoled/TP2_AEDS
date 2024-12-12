#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "headers/rocha_mineral.h"

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

void preencher_rocha_mineral(FILE *arquivo, int i, RochaMineral *rochas){
    fscanf(arquivo, "%f %d", &rochas[i].peso, &rochas[i].valor);
    *rochas[i].id = rand() % 1000;
}

void imprimir_rocha_mineral(RochaMineral *nova_rocha){

    char categoria_imprimir[255];

    printf("\nPeso: %.2f", nova_rocha->peso);
    printf("\nValor: %d", nova_rocha->valor);
    printf("\nID: %d", nova_rocha->id);
}