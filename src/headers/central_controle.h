#include <stdio.h>
#include <stdlib.h>

#include "lista_sondas.h"


void selecao_combinacoes_validas(RochaMineral temp[], int tam_combinacao_atual, RochaMineral *combinacoes_validas, int *qnt_combinacoes_validas);
//função para gerar combinações
void gerarCombinacoes(RochaMineral array_elementos_combinacao[], 
                      int tam_total_array, 
                      int tam_combinacao_atual, 
                      int index_combinacao_atual, 
                      RochaMineral temp[], 
                      int i, 
                      RochaMineral *combinacoes_validas,
                      int *qnt_combinacoes_validas
                      );

//gerar todas as combinações de tamanhos diferentes
void gerarTodasCombinacoes(RochaMineral array_elementos_combinacao[], int tam_total_array, RochaMineral *rochas_validas, int *qnt_combinacoes_validas);

//funcao para ler arquivo
int LerArquivo(char *nome_arquivo, RochaMineral rochas[]);

void distribuicao_rochas(RochaMineral *rochas_validas, int qnt_combinacoes_validas);