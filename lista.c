#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista.h"
#include "leitura.h"
#include "svg.h"


No *adicionaElemento(No *inicio, int id, char tipo){
    if(inicio == NULL){
        printf("\n\t\tINICIANDO LISTA . . . \n");
        printf("\n\tADICIONANDO ELEMENTO . . . ");
        inicio = (No*)malloc(sizeof(No));
        if(inicio == NULL){
            printf("\nErro inesperado! Memoria insuficiente para adicionar um novo elemento na lista.");
            exit(1);
        }
        inicio->id = id;
        inicio->tipo = tipo;
        inicio->fig = NULL;
        inicio->prox = NULL;
    }
    else{
        No *aux = inicio;
        printf("\n\tADICIONANDO ELEMENTO . . . ");
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = (No*)malloc(sizeof(No)); //aqui eu aloco a memória pro elemento adicionado
        if(aux->prox == NULL){
            printf("\nErro inesperado! Memoria insuficiente para adicionar um novo elemento na lista.");
            exit(1);
        }
        aux = aux->prox; //aqui eu ando uma vez na lista para acessar o próximo
        aux->id = id;
        aux->tipo = tipo;
        aux->fig = NULL;
        aux->prox = NULL; //o proximo do elemento adicionado aponta pra NULL
    }
    printf("\n\tNovo elemento adicionado com sucesso! ID: %d", id);
    return inicio;
}

No *buscaElemento(No *inicio, int id){
    No *aux = inicio;
    //int iguais = 0;
    while (aux != NULL){
        if (id == aux->id){
            printf("\n\tElemento encontrado com sucesso! ID: %d \n", id);
            return aux;
        }
        aux = aux->prox;
    }

    printf("\n\tNao foi possivel encontrar o elemento! ID: %d \n", id);
    return NULL;
}

No *imprimeLista(No *inicio){ //Enquanto o aux != NULL, printa
    No *aux = inicio;

    printf("\n\t\tIMPRIMINDO LISTA . . . ");
    printf("\n\tINICIO -> ");

    while(aux != NULL){
        if(aux->fig != NULL){
            if(aux->tipo == 'c'){
                printf("\n\t\tcirculo: r: %f  x: %f   y: %f", aux->fig->crl.r, aux->fig->crl.x, aux->fig->crl.y);
            }
            else if(aux->tipo == 'r'){
                printf("\n\t\tret: w: %f  h: %f    x: %f  y: %f", aux->fig->ret.w, aux->fig->ret.h, aux->fig->ret.x, aux->fig->ret.y);
            }
            else if(aux->tipo == 't'){
                printf("\n\t\ttexto: x: %f    y: %f   texto: %s", aux->fig->texto.x, aux->fig->texto.y, aux->fig->texto.texto);
            }
            printf("    ID: %d TIPO: %c -> ", aux->id, aux->tipo);
        }
        aux = aux->prox;
    }

    printf("\n\t-> NULL");
    printf("\n\tLista impressa com sucesso!");

    return inicio;
}

No *deletaLista(No *inicio){
    /*Percorrer a lista, e todo elemento que encontrar apagar, porem tomar cuidado para nao
    perder o proximo.*/
    No *aux;
    printf("\n\t\tDELETANDO LISTA . . . ");
    while(inicio != NULL){
        aux = inicio;
        inicio = inicio->prox;
        if(aux->tipo == 't'){
            free(aux->fig->texto.texto); //perguntar
        }
        free(aux->fig);
        free(aux);
    }
    printf("\n\tLista deletada com sucesso!");
    printf("\n\t---------------------------------------------------\n");

    return inicio;
}

No *deletaElemento(No *inicio, int id){
    No *aux = inicio;
    No *ant = NULL;
    if (aux->id == id){
        inicio = aux->prox;
        free(aux);
    }
    while (aux != NULL && aux->prox->id != id){
        aux = aux->prox;
    }
    if (aux == NULL){
        printf("\nElemento não existe ou a lista não foi iniciada");
        return inicio;
    }
    ant = aux;
    aux = aux->prox;
    ant->prox = aux->prox;
    free(aux);
    return inicio;
}

/*No *deletarElemento(No *inicio, int id){
  No *aux = inicio;
  No *ant = NULL;
  while (aux != NULL){
    if (aux->id == id){
      inicio = aux->prox;
      free(aux);
      //return inicio;
    }
    else if (aux->prox->id == id){
      ant = aux;
      aux = aux->prox;
      ant->prox = aux->prox;
      free(aux);
    }
    //else
    aux = aux->prox;
  }
  return inicio;
}/*

Passo inicio da lista e id como parametros.
Declaro uma variavel auxiliar que recebe o inicio da lista (para não perder o inicio)
Declaro uma variavel anterior que recebe NULL
Enquanto o auxiliar for diferente de NULL
    Se o id do auxiliar for igual ao id passado no parametro, quer dizer que o primeiro elemento da lista é o que esta sendo procurado
        o inicio da lista vai receber o proximo elemento da lista
        dou free na variavel auxiliar que era o inicio
    Senao se o id do proximo elemento da lista for igual ao id passado no parametro, quer dizer que o elemento a ser deletado nao é o primeiro da lista
        a variavel anterior recebe a variavel aux
        a variavel auxiliar recebe o proximo elemento da lista
        o proximo do anterior vai receber o proximo do auxiliar
    Para percorrer a lista, faz-se auxiliar recebe o proximo elemento da lista                 





No *adicionaRetangulo(No *inicio, int id, float w, float h, float x, float y, char corb[], char corp[]){
    printf("\n\tBUSCANDO ELEMENTO . . . ");
    No *aux = buscaElemento(inicio, id);
    if(aux == NULL){ 
        printf("\nNao foi possivel encontrar o elemento \"retangulo\". ID: %d!", id); 
        return NULL;
    }

    aux->fig = (Info*)malloc(sizeof(Info));
    if(aux->fig == NULL){
        printf("\nErro inesperado! Memoria insuficiente.");
        exit(1);
    }

    aux->fig->ret.w = w;
    aux->fig->ret.h = h;
    aux->fig->ret.x = x;
    aux->fig->ret.y = y;
    strcpy(aux->fig->ret.corb, corb);
    strcpy(aux->fig->ret.corp, corp);
    return inicio; 
}

No *adicionaCirculo(No *inicio, int id, float r, float x, float y, char corb[], char corp[]){
    printf("\n\tBUSCANDO ELEMENTO . . . ");
    No *aux = buscaElemento(inicio, id);
    if(aux == NULL){ 
        printf("\nNao foi possivel encontrar o elemento \"circulo\". ID: %d!", id);
        return NULL;
    }

    aux->fig = (Info *)malloc(sizeof(Info));
    if(aux->fig == NULL){
        printf("\nErro inesperado! Memoria insuficiente para adicionar um novo elemento \"circulo\".");
        exit(1);
    }

    aux->fig->crl.r = r;
    aux->fig->crl.x = x;
    aux->fig->crl.y = y;
    strcpy(aux->fig->crl.corb, corb);
    strcpy(aux->fig->crl.corp, corp);
    return inicio;
}

No *adicionaTexto(No *inicio, int id, float x, float y, char texto[], char corb[], char corp[], int size){
    printf("\n\tBUSCANDO ELEMENTO . . . ");
    No *aux = buscaElemento(inicio, id);
    if (aux == NULL){ 
        printf("\nElemento \"texto\" nao foi encontrado!");
        return NULL;
    }

    aux->fig = (Info*)malloc(sizeof(Info));
    if (aux->fig == NULL){
        printf("\nErro inesperado! Memoria insuficiente para adicionar um novo elemento \"texto\".");
        exit(1);
    }

    aux->fig->texto.x = x;
    aux->fig->texto.y = y;
    aux->fig->texto.texto = (char*)malloc(sizeof(char) * size);
    if(aux->fig->texto.texto == NULL){
        printf("\nErro inesperado! Memoria insuficiente para salvar caracteres do texto.");
        exit(1);
    }
    strcpy(aux->fig->texto.texto, texto);
    strcpy(aux->fig->texto.corb, corb);
    strcpy(aux->fig->texto.corp, corp);
    return inicio;
}

/*No *adicionaBtracej(No *inicio, int j, int k){
    return inicio;
}*/

/*No *adicionaBcheia(No *inicio, int j, int k){
    return inicio;
}*/

/*No *adicionaPonto(No *inicio, int j, float x, float y){
    return inicio;
}*/

/*No *adicionaLinha(No *inicio, int j, float x, float y){
    return inicio;
}*/


/*No *viewBoxSvg(No *inicio, FILE *arqSvg){
    No *aux = inicio;
    float xMaior = 0, yMaior = 0, h = 0, w = 0, xMin = 0, yMin = 0, wTot = 0, hTot = 0;
    while (aux != NULL){
        if (aux->fig != NULL){
            if (aux->tipo == 'c'){ //circulo
                float rMaior = 0;
                if (aux->fig->crl.x > xMaior){
                    xMaior = aux->fig->crl.x;
                }
                if (aux->fig->crl.y > yMaior){
                    yMaior = aux->fig->crl.y;
                }
                if (aux->fig->crl.r > rMaior){
                    rMaior = aux->fig->crl.r;
                }
                w = xMaior + rMaior + 1;
                h = yMaior + rMaior + 1;
                
                if(aux->fig->crl.x <= aux->fig->crl.r){
                    printf("\naqui no 1");
                    xMin = - aux->fig->crl.r - 1;
                    w = w - xMin;
                }
                if (aux->fig->crl.y <= aux->fig->crl.r){
                    printf("\naqui no 2");
                    yMin = - aux->fig->crl.r - 1;
                    h = h - yMin;
                }

                if (aux->fig->crl.x < 0){
                    printf("\naqui no 3");
                    xMin = aux->fig->crl.x - 5;
                    //w = w + aux->fig->crl.r + 1;
                    w = w -xMin;
                }
                if (aux->fig->ret.y < 0){
                    printf("\naqui no 4");
                    yMin = aux->fig->crl.y - 5;
                    //h = h + aux->fig->crl.r + 1;
                    h = h - yMin;
                }

            }
    
            else if (aux->tipo == 'r'){ //retangulo
                float hMaior = 0, wMaior = 0;
                if (aux->fig->ret.x > xMaior){
                    xMaior = aux->fig->ret.x;
                }
                if (aux->fig->ret.y > yMaior){
                    yMaior = aux->fig->ret.y;
                }
                if (aux->fig->ret.h > hMaior){
                    hMaior = aux->fig->ret.h;
                }
                if (aux->fig->ret.w > wMaior){
                    wMaior = aux->fig->ret.w;
                }
                w = wMaior + xMaior + 1;
                h = hMaior + yMaior + 1;

                if(aux->fig->ret.x < 0){
                    if(xMin > aux->fig->ret.x){
                        xMin = aux->fig->ret.x - 5;
                        w = w - xMin;
                    }
                }
                if (aux->fig->ret.y < 0){
                    if(yMin > aux->fig->ret.y){
                        yMin = aux->fig->ret.y - 5;
                        h = h - yMin;
                    }
                }
            }

            // else if (aux->tipo == 't'){ //texto
            //     if (aux->fig->texto.x > minX){
            //         minX = aux->fig->texto.x;
            //     }
            //     if (aux->fig->texto.y > minY){
            //         minY = aux->fig->texto.y;
            //     }
            //     minX /= 2;
            //     minY /= 2;
            //     height = -10;
            // }
    
            if(wTot < w){
                wTot = w;
            }
            if(hTot < h){
                hTot = h;
            }
        }
        aux = aux->prox;
    }
    fprintf(arqSvg, "<svg viewBox=\" %f %f %f %f\">", xMin, yMin, wTot, hTot);
    return inicio;
}*/