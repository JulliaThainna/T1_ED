#ifndef lista_H_
#define lista_H_

#include <stdbool.h>

/*Estrutura com todas as caracteristicas do retangulo*/
typedef struct{
    float w, h, x, y;
    char corb[22], corp[22];
    bool trac;
}Retangulo;

/*Estrutura com todas as caracteristicas do circulo*/
typedef struct{
    float r, x, y;
    char corb[22], corp[22];
}Circulo;

/*Estrutura com todas as caracteristicas do texto*/
typedef struct{
    char *texto;
    char corb[22], corp[22];
    float x, y;
}Texto;

/*Estrutura com todas as caracteristicas da linha*/
typedef struct{
    float x1, y1, x2, y2;
    char corp[10];
}Linha;

/*Union que agrupa os variados tipos de elementos, foi utilizado uma union, pois, um elemento pode ser so e
somente um retangulo ou um circulo ou um texto ou uma linha, entao, assim economiza-se memoria, ja que so e usada a informacao 
relativa ao elemento atual*/
typedef union{
    Retangulo ret;
    Circulo crl;
    Texto texto;
    Linha linha;
}Info;

/*Estrutura da lista encadeada
Atributos: int id - id lido do arquivo .geo (> 0)
           char tipo - tipo lido do arquivo .geo (r, c, t, l)
           Info *fig - ponteiro de tipo 'Info' que aponta para os atributos da union Info dependendo do seu tipo
           struct no *prox - aponta pra propria estrutura fazendo referencia a ela mesma, apontando para o proximo 
           elemento*/
typedef struct no{
    int id;
    char tipo;
    Info *fig;

    struct no *prox;
}No;

/*Adiciona o primeiro ou novos elementos na lista
Parametros: No *inicio - inicio da lista
            int id - id do elemento lido do arquivo .geo (geo: > 0 | qry: <= 0)
            int tipo - tipo do elemento lido do arquivo .geo ou do arquivo .qry (r, c, t, l)*/
No *adicionaElemento(No *inicio, int id, char tipo);

/*Busca elementos ja existentes na lista
Parametros: No *inicio - inicio da lista
            int id - id do elemento lido do arquivo .geo ou do arquivo .qry (geo: > 0 | qry: <= 0)*/
No *buscaElemento(No *inicio, int id);

/*Imprime os elementos existentes na lista
Parametros: No *inicio - inicio da lista*/
No *imprimeLista(No *inicio);

/*Deleta toda a lista
Parametros: No *inicio - inicio da lista*/
No *deletaLista(No *inicio);

/*As proximas quatro funcoes servem para determinar o atributo Info *fig e para qual tipo de elemento 
e estrutura ele vai apontar*/
/*Parametros: No *inicio - inicio da lista
              int id - id do retangulo lido do arquivo .geo ou gerada pro o? do arquivo .qry (geo: > 0 | qry: <= 0)
              float w - width do retangulo lido do arquivo .geo  ou gerada pro o? do arquivo .qry
              float h - high do retangulo lido do arquivo .geo ou gerada pro o? do arquivo .qry
              float x - coordernada x do retangulo lido do arquivo .geo ou gerada pro o? do arquivo .qry
              float y - coordenada y do retangulo lido do arquivo .geo ou gerada pro o? do arquivo .qry
              char corb[] - cor da borda do retangulo lido do arquivo .geo ou gerada pro o? do arquivo .qry
              char corp[] - cor do preenchimento do retangulo lido do arquivo .geo ou gerada pro o? do arquivo .qry*/
No *adicionaRetangulo(No *inicio, int id, float w, float h, float x, float y, char corb[], char corp[]);

/*Parametros: No *inicio - inicio da lista
              int id - id do circulo lido do arquivo .geo ou gerada pro i? do arquivo .qry (geo: > 0 | qry: <= 0)
              float r - raio do circulo lido do arquivo .geo  ou gerada pro i? do arquivo .qry
              float x - coordernada x do circulo lido do arquivo .geo ou gerada pro i? do arquivo .qry
              float y - coordenada y do circulo lido do arquivo .geo ou gerada pro i? do arquivo .qry
              char corb[] - cor da borda do circulo lido do arquivo .geo ou gerada pro i? do arquivo .qry
              char corp[] - cor do preenchimento do circulo lido do arquivo .geo ou gerada pro i? do arquivo .qry*/
No *adicionaCirculo(No *inicio, int id, float r, float x, float y, char corb[], char corp[]);

/*Parametros: No *inicio - inicio da lista
              int id - id do texto lido do arquivo .geo (> 0)
              float x - coordernada x do texto lido do arquivo .geo
              float y - coordenada y do texto lido do arquivo .geo
              char corb[] - cor da borda do texto lido do arquivo .geo
              char corp[] - cor do preenchimento do texto lido do arquivo .geo
              int size - tamanho do texto que esta no .geo, definido dentro do comandoGeo */
No *adicionaTexto(No *inicio, int id, float x, float y, char texto[], char corb[], char corp[], int size);

/*Parametros: No *inicio - inicio da lista
              int id - id da linha definido pelo geraCoordenadas do i? do .qry 
              float x1 - coordenada x inicial definida pelo geraCoordenadas do i? do .qry 
              float y1 - coordenada y inicial definida pelo geraCoordenadas do i? do .qry 
              float x2 - coordernada x final definida pelo geraCoordenadas do i? do .qry 
              float y2 - coordenada y final definida pelo geraCoordenadas do i? do .qry 
              char corp[] - cor do preenchimento da linha definido pelo geraCoordenadas do i? do .qry*/
No *adicionaLinha(No *inicio, int id, float x1, float y1, float x2, float y2, char corp[]);

/*Deleta o elemento j
Parametros: No *inicio - inicio da lista
            int j - id do elemento j lido do arquivo .qry (> 0)*/
No *deletaElementoj(No *inicio, int j);

/*Deleta os elemento de j ate k (incluindo os mesmos)
Parametros: No *inicio - inicio da lista
            int j - id do elemento j lido do arquivo .qry (> 0)
            int k - id do elemento k lido do arquivo .qry* (> 0)*/
No *deletaElementojk(No *inicio, int j, int k);

#endif
