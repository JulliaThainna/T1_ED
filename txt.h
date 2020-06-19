#ifndef txt_H_
#define txt_H_

#include "lista.h"

No *escreveTexto(No *inicio, char pathSaida[], char comando[], char corb[], char corp[], int j, int k, float x, float y, int retorno);

    No *retornaInfo(No * inicio, FILE * qry, char comando[], int j, int k);

#endif
