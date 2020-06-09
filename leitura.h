#ifndef leitura_H_
#define leitura_H_

#include "lista.h"
//Registros
No *abreGeo(char dirEntrada[], char arqGeo[], char pathEntrada[], char nomeGeo[], No *inicio);
No *comandoGeo(FILE *geo, No *inicio, char pathEntrada[]);
#endif