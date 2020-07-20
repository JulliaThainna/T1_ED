#ifndef leitura_H_
#define leitura_H_

#include "lista.h"

/*Abre o arquivo .geo a partir do caminho que o usuario passou no siguel, e se houver o comando '-e', tratado na funcao
trataStringCaminho
Parametros: No* inicio - inicio da lista
            char dirEntrada[] - o argumento do comando '-e' passado pelo usuario como argumento do siguel
            char arqGeo[] - o argumento do comando '-f' passado pelo usuario como argumento do siguel*/
No *abreGeo(No *inicio, char dirEntrada[], char arqGeo[]);

/*Le os comandos do arquivo .geo e a assim, chama as funcoes relativas aos elementos desejados pelo usuario
Parametros: No *inicio - inicio da lista
            FILE *geo - o caminho do arquivo .geo estabelecido na funcao trataStringCaminho dentro da funcao abreGeo*/
No *comandoGeo(No *inicio, FILE *geo);

#endif
