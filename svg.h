#ifndef svg_H_
#define svg_H_

#include "lista.h"

/*Desenha as figuras tanto do .geo quanto das mudancas do .qry em um .svg
Parametros: No *inicio - inicio da lista
            char pathSaida[] - Arquivo criado pela funcao criaArquivo na main, caminho do .svg*/
void desenhaSvg(No *inicio, char pathSaida[]);

#endif
