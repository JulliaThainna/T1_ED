#ifndef txt_H_
#define txt_H_

#include "lista.h"

/*Escreve o texto no arquivo de saida .txt a partir dos comandos do arquivo .qry
Parametros: No *inicio - inicio da lista
            FILE *qrySaida - caminho do arquivo .txt criado pela funcao criaArquivo dentro da funcao comandoQry
            char comando[] - comando lido dentro do arquivo .qry (o?, i?, pnt, pnt*, delf, delf*)
            char corb[] - cor de borda lida dentro do arquivo .qry (pnt ou pnt*)
            char corp[] - cor do preenchimento lido dentro do arquivo .qry (pnt ou pnt*)
            int j - id do elemento j lido dentro do arquivo .qry (existe em : o?, i?, pnt, pnt*, delf, delf*)
            int k - id do elemento k lido dentro do arquivo .qry (existem em: o?, pnt*, delf*)
            float x - coordenada x lido do arquivo .qry (existe em: i?)
            float y - coordenada y lido do arquivo .qry (existe em: i?)
            int retorno - retorno das funcoes (1 - sobrepoe/interno/nenhum erro | 0 - nao sobrepoe/externo | 
            -1 - tipo texto para funcoes que nao permitem elemento tipo texto (vulgo: o? e i?) | -2 - elemento nao encontrado)*/
int escreveTexto(No *inicio, FILE *arqTxt, char comando[], char corb[], char corp[], int j, int k, float x, float y, int retorno);

#endif
