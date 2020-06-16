#ifndef consulta_H_
#define consulta_H_

#include <stdbool.h>
#include "lista.h"
No *abreQry(No *inicio, char dirEntrada[], char arqQry[], char pathSaida[]);
No *comandoQry(FILE *qry, No *inicio, char pathSaida[]);
bool ponto(No *inicio, int j, float x, float y, bool interno);
bool sobrepoe(No *inicio, int j, int k, bool dentro);
void mudaCorj(No *inicio, int j, char corb[], char corp[]);
void mudaCorjk(No *inicio, int j, int k, char corb[], char corp[]);

#endif
