#ifndef lista_H_
#define lista_H_


typedef struct{
    float w, h, x, y;
    char corb[22], corp[22];
}Retangulo;

typedef struct{
    float r, x, y;
    char corb[22], corp[22];
}Circulo;

typedef struct{
    char *texto;
    char corb[22], corp[22];
    float x, y;
}Texto;

typedef struct{
    float x1, y1, x2, y2;
    char corp[10];
}Linha;

typedef union{
    Retangulo ret;
    Circulo crl;
    Texto texto;
    Linha linha;
}Info;

typedef struct no{
    int id;
    char tipo;
    Info *fig;

    struct no *prox;
}No;


No *adicionaElemento(No *inicio, int id, char tipo);
No *imprimeLista(No *inicio);
No *buscaElemento(No *inicio, int id);
No *deletaLista(No *inicio);

No *adicionaRetangulo(No *inicio, int id, float w, float h, float x, float y, char corb[], char corp[]);
No *adicionaCirculo(No *inicio, int id, float r, float x, float y, char corb[], char corp[]);
No *adicionaTexto(No *inicio, int id, float x, float y, char texto[], char corb[], char corp[], int size);
No *adicionaLinha(No *inicio, int id, float x1, float y1, float x2, float y2, char corp[]);

No *deletaElementoj(No *inicio, int j);
No *deletaElementojk(No *inicio, int j, int k);

//No *viewBoxSvg(No *inicio, FILE *arqSvg);

#endif
