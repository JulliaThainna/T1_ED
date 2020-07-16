#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista.h"
#include "leitura.h"
#include "svg.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))


No *adicionaElemento(No *inicio, int id, char tipo){
    if(inicio == NULL){
        printf("\n\t\tINICIANDO LISTA . . . \n");
        printf("\n\tADICIONANDO ELEMENTO . . . ");
        inicio = (No*)malloc(sizeof(No));
        if(inicio == NULL){
            printf("\nErro inesperado! Memoria insuficiente para adicionar um novo elemento na lista.");
            printf("\n---------------------------------------------------\n");
            exit(1);
        }

        inicio->id = id;
        inicio->tipo = tipo;
        inicio->fig = NULL;
        inicio->prox = NULL;
    }

    else{
        No *aux = inicio;
        if(buscaElemento(aux, id) != NULL){
            printf("\nERRO! Existe um elemento com o mesmo id na lista. ID: %d", id);
            printf("\n---------------------------------------------------\n");
            exit(1);
        }

        printf("\n\tADICIONANDO ELEMENTO . . . ");
        while(aux->prox != NULL){
            aux = aux->prox;
        }

        aux->prox = (No*)malloc(sizeof(No)); //aqui eu aloco a memoria pro elemento adicionado
        if(aux->prox == NULL){
            printf("\nErro inesperado! Memoria insuficiente para adicionar um novo elemento na lista.");
            printf("\n---------------------------------------------------\n");
            exit(1);
        }

        aux = aux->prox; //aqui eu ando uma vez na lista para acessar o proximo
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
    while(aux != NULL){
        if(id == aux->id){
            return aux;
        }
        aux = aux->prox;
    }

    return NULL;
}

No *imprimeLista(No *inicio){
    No *aux = inicio;

    printf("\n\t\tIMPRIMINDO LISTA . . . ");
    printf("\n\tINICIO -> ");

    while(aux != NULL){
        if(aux->fig != NULL){
            if(aux != inicio){
                printf("\t       -> ");
            }

            if(aux->tipo == 'c'){
                printf("Tipo: Circulo| r:%f| x:%f| y:%f", aux->fig->crl.r, aux->fig->crl.x, aux->fig->crl.y);
            }

            else if(aux->tipo == 'r'){
                printf("Tipo: Retangulo| w:%f| h:%f| x:%f| y:%f", aux->fig->ret.w, aux->fig->ret.h, aux->fig->ret.x, aux->fig->ret.y);
            }

            else if(aux->tipo == 't'){
                printf("Tipo: Texto| x:%f| y:%f| texto:%s", aux->fig->texto.x, aux->fig->texto.y, aux->fig->texto.texto);
            }

            else{
                printf("Tipo: Linha| x1:%f| y1:%f| x2:%f| y2:%f", aux->fig->linha.x1, aux->fig->linha.y1, aux->fig->linha.x2, aux->fig->linha.y2);
            }

            printf("| ID: %d -> ", aux->id);
        }
        if(aux->prox == NULL){
            printf("NULL");
        }
        printf("\n");


        aux = aux->prox;
    }

    printf("\n\tLista impressa com sucesso!");

    return inicio;
}

No *deletaLista(No *inicio){    //Percorrer a lista, e todo elemento que encontrar apagar, porem tomar cuidado para nao perder o proximo
    No *aux = NULL;

    printf("\n\t\tDELETANDO LISTA . . . ");
    while(inicio != NULL){
        aux = inicio;
        inicio = inicio->prox;
        if(aux->tipo == 't'){
            free(aux->fig->texto.texto);
        }
        free(aux->fig); //ficha
        free(aux);  //folha
    }

    printf("\n\tLista deletada com sucesso!");
    printf("\n\t---------------------------------------------------\n");

    return inicio;
}


No *adicionaRetangulo(No *inicio, int id, float w, float h, float x, float y, char corb[], char corp[]){
    No *aux = buscaElemento(inicio, id);
    if(aux == NULL){ 
        printf("\nNao foi possivel encontrar o elemento \"retangulo\". ID: %d!", id);
        printf("\n---------------------------------------------------\n"); 
        return inicio;
    }

    aux->fig = (Info*)malloc(sizeof(Info));
    if(aux->fig == NULL){
        printf("\nErro inesperado! Memoria insuficiente.");
        printf("\n---------------------------------------------------\n");
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
    No *aux = buscaElemento(inicio, id);
    if(aux == NULL){ 
        printf("\nNao foi possivel encontrar o elemento \"circulo\". ID: %d!", id);
        return inicio;
    }

    aux->fig = (Info *)malloc(sizeof(Info));
    if(aux->fig == NULL){
        printf("\nErro inesperado! Memoria insuficiente para adicionar um novo elemento \"circulo\".");
        printf("\n---------------------------------------------------\n");
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
    No *aux = buscaElemento(inicio, id);
    if(aux == NULL){ 
        printf("\nElemento \"texto\" nao foi encontrado!");
        return inicio;
    }

    aux->fig = (Info*)malloc(sizeof(Info));
    if(aux->fig == NULL){
        printf("\nErro inesperado! Memoria insuficiente para adicionar um novo elemento \"texto\".");
        printf("\n---------------------------------------------------\n");
        exit(1);
    }

    aux->fig->texto.x = x;
    aux->fig->texto.y = y;
    aux->fig->texto.texto = (char*)malloc(sizeof(char) * size);
    if(aux->fig->texto.texto == NULL){
        printf("\nErro inesperado! Memoria insuficiente para salvar caracteres do texto.");
        printf("\n---------------------------------------------------\n");
        exit(1);
    }
    strcpy(aux->fig->texto.texto, texto);
    strcpy(aux->fig->texto.corb, corb);
    strcpy(aux->fig->texto.corp, corp);

    return inicio;
}

No *adicionaLinha(No *inicio, int id, float x1, float y1, float x2, float y2, char corp[]){
    No *aux = buscaElemento(inicio, id);
    if(aux == NULL){ 
        printf("\nElemento \"texto\" nao foi encontrado!");
        printf("\n---------------------------------------------------\n");
        return inicio;
    }
    
    aux->fig = (Info*)malloc(sizeof(Info));
    if(aux->fig == NULL){
        printf("\nErro inesperado! Memoria insuficiente.");
        printf("\n---------------------------------------------------\n");
        exit(1);
    }

    aux->fig->linha.x1 = x1;
    aux->fig->linha.y1 = y1;
    aux->fig->linha.x2 = x2;
    aux->fig->linha.y2 = y2;
    strcpy(aux->fig->linha.corp, corp);

    return inicio;
}


No *deletaElementoj(No *inicio, int j){
    No *aux = inicio;
    No *ant = NULL;
    if(aux->id == j){
        inicio = aux->prox;
        if(aux->tipo == 't'){
            free(aux->fig->texto.texto);
        }
        free(aux->fig);
        free(aux);
        printf("\n\tElemento J deletado com sucesso! ID: %d", j);
        return inicio;
    }

    while(aux != NULL && aux->id != j){
        ant = aux;
        aux = aux->prox;
        if(aux->prox == NULL){
            printf("\n\tNao foi possivel encontrar o elemento J! ID: %d", j);
            return inicio;
        }
    }

    if(aux == NULL){
        printf("\n\tLista nao foi iniciada");
        return inicio;
    }

    ant->prox = aux->prox;
    if(aux->tipo == 't'){
        free(aux->fig->texto.texto);
    }
    free(aux->fig);
    free(aux);
    printf("\n\tElemento deletado com sucesso! ID: %d", j);
    
    return inicio;
}

No *deletaElementojk(No *inicio, int j, int k){
    No *auxJ = buscaElemento(inicio, j);
    if(auxJ == NULL){
        printf("\n\tNao foi possivel encontrar o elemento J. ID: %d!", j);
        return inicio;
    }
    No *auxK = buscaElemento(inicio, k);
    if(auxK == NULL){
        printf("\n\tNao foi possivel encontrar o elemento K. ID: %d!", k);
        return inicio;
    }

    for(int i = MIN(j,k); i <= MAX(j,k); i++){
        deletaElementoj(inicio, i);
    }
    
    return inicio;
}

/*
No *deletarElemento(No *inicio, int id){
  No *aux = inicio;
  No *ant = NULL;
  while(aux != NULL){
    if(aux->id == id){
      inicio = aux->prox;
      free(aux);
      //return inicio;
    }
    else if(aux->prox->id == id){
      ant = aux;
      aux = aux->prox;
      ant->prox = aux->prox;
      free(aux);
    }
    //else
    aux = aux->prox;
  }
  return inicio;
}

Passo inicio da lista e id como parametros.
Declaro uma variavel auxiliar que recebe o inicio da lista (para nao perder o inicio)
Declaro uma variavel anterior que recebe NULL
Enquanto o auxiliar for diferente de NULL
    Se o id do auxiliar for igual ao id passado no parametro, quer dizer que o primeiro elemento da lista e o que esta sendo procurado
        o inicio da lista vai receber o proximo elemento da lista
        dou free na variavel auxiliar que era o inicio
    Senao se o id do proximo elemento da lista for igual ao id passado no parametro, quer dizer que o elemento a ser deletado nao e o primeiro da lista
        a variavel anterior recebe a variavel aux
        a variavel auxiliar recebe o proximo elemento da lista
        o proximo do anterior vai receber o proximo do auxiliar
    Para percorrer a lista, faz-se auxiliar recebe o proximo elemento da lista    (aqui problema)              
*/
