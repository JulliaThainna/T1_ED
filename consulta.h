#ifndef consulta_H_
#define consulta_H_

#include <stdbool.h>
#include "lista.h"

No *abreQry(No *inicio, char dirEntrada[], char arqQry[]);
No *comandoQry(FILE *qry, No *inicio);
int ponto(No *inicio, int j, float x, float y, int interno);
int sobrepoe(No *inicio, int j, int k, int dentro);
int mudaCorj(No *inicio, int j, char corb[], char corp[]);
int mudaCorjk(No *inicio, int j, int k, char corb[], char corp[]);

#endif
