#ifndef consulta_H_
#define consulta_H_

#include <stdbool.h>
#include "lista.h"

/*Funcao que abre o arquivo .qry a partir do caminho que o usuario passou no comando -q
Parametros: No* inicio - inicio da lista
            char dirEntrada[] - o comando "-e" passado pelo usuario como argumento do siguel
            char arqQry[] - o comando "-q" passado pelo usuario como argumento do siguel
            char pathSaida[] - o comando "-o" passado pelo usuario como argumento do siguel*/
void abreQry(No *inicio, char dirEntrada[], char arqQry[], char pathSaida[]);
/*Função que le os comandos do arquivo .qry e a assim, chama as funcoes relativas as consultas desejadas pelo usuario
Parametros: */
void comandoQry(FILE *qry, char pathSaida[], No *inicio);

/*As proximas quatro funcoes sao relativas aos comandos do .qry (o?, i?, pnt, pnt*)
obs: delf e delf* estao no lista.h, pois, decidi organanizar de forma que, as operações voltadas para listas
ficassem no mesmo arquivo*/ 

/*o? - Verifica se a figura j e k estao sobrepostas*/
int sobrepoe(No *inicio, int j, int k, int dentro); 
int ponto(No *inicio, int j, float x, float y, int interno);
int mudaCorj(No *inicio, int j, char corb[], char corp[]);
int mudaCorjk(No *inicio, int j, int k, char corb[], char corp[]);
void geraCoordenadas(No *inicio, int j, int k, float x, float y, char comando[], int retorno, int id);

#endif
