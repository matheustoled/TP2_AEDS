#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/SONDA.h"

//Função para iniciar a sonda
void Inicializar(Sonda* sonda, Compartimento *comp)
{
    sonda->CompSonda = *comp;
    FListaRochaM(&sonda->CompSonda, 40);
}