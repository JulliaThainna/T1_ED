#ifndef consulta_H_
#define consulta_H_

#include <stdbool.h>
#include "lista.h"


No *abreQry(No *inicio, char dirEntrada[], char arqQry[], char pathSaida[]);
No *comandoQry(FILE *qry, char pathSaida[], No *inicio);
int ponto(No *inicio, int j, float x, float y, int interno);
int sobrepoe(No *inicio, int j, int k, int dentro);
int mudaCorj(No *inicio, int j, char corb[], char corp[]);
int mudaCorjk(No *inicio, int j, int k, char corb[], char corp[]);
No *geraCoordenadas(No *inicio, int j, int k, float x, float y, char comando[], int retorno);

#endif
