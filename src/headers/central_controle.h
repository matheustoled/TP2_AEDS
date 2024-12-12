#include <stdio.h>
#include <stdlib.h>

#include "lista_sondas.h"

typedef struct {
    float peso;
    int valor;
    RochaMineral rochas[40]; // Rochas que fazem parte da combinação
    int qtd_rochas;          // Quantidade de rochas na combinação
} CombinacaoValida;

void selecao_combinacoes_validas(RochaMineral temp[], int tam_total_array, CombinacaoValida *rochas_validas, int *qnt_combinacoes_validas);
//função para gerar combinações
void gerarCombinacoes(RochaMineral array_elementos_combinacao[], 
                      int tam_total_array, 
                      int tam_combinacao_atual, 
                      int index_combinacao_atual, 
                      RochaMineral temp[], 
                      int i, 
                      CombinacaoValida *rochas_validas,
                      int *qnt_combinacoes_validas);

void remover_rochas_usadas(CombinacaoValida *combinacoes_validas, int *qnt_combinacoes_validas, RochaMineral *rochas_usadas, int qnt_rochas_usadas);

//gerar todas as combinações de tamanhos diferentes
void gerarTodasCombinacoes(RochaMineral array_elementos_combinacao[], int tam_total_array, CombinacaoValida *rochas_validas, int *qnt_combinacoes_validas);

//funcao para ler arquivo
int LerArquivo(char *nome_arquivo, RochaMineral rochas[]);

void distribuicao_rochas(CombinacaoValida *rochas_validas, int qnt_combinacoes_validas);