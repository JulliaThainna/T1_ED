#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lista.h"
#include "consulta.h"
#include "trataString.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

No *abreQry(No *inicio, char *dirEntrada, char *arqQry){
    FILE *qry = NULL;
    char *pathEntrada = NULL;

    printf("\n\t\tABRINDO ARQUIVO .qry . . . ");
    if(dirEntrada == NULL){
        printf("\n\t\t > Arquivo .svg: %s", arqQry);
        qry = fopen(arqQry, "r");
        if(!qry){
            printf("\nErro inesperado! Nao foi possivel abrir o arquivo. Arquivo inexistente.");
            exit(1);
        }
    }
    else{
        pathEntrada = trataStringCaminho(dirEntrada, arqQry);
        printf("\n\t > Arquivo .qry: %s", pathEntrada);
        qry = fopen(pathEntrada, "r");
        if(!qry){
            printf("\nErro inesperado! Nao foi possivel abrir o arquivo. Diretorio ou arquivo inexistente.");
            exit(1);
        }
    }
    printf("\n\t Arquivo .qry aberto com sucesso!");
    printf("\n\t---------------------------------------------------\n");
    inicio = comandoQry(qry, inicio);
    free(pathEntrada);

    return inicio;
}

No *comandoQry(FILE *qry, No *inicio){
    bool retorno;
    int j = 0, k = 0;
    float x, y;
    char comando[6] = {'\0', '\0', '\0', '\0', '\0', '\0'}, corb[22], corp[22];
    
    while(1){
        retorno = false;
        fscanf(qry, "%s", comando);
        if(feof(qry)){
            break;
        }
        if(strcmp(comando, "o?") == 0){ 
            fscanf(qry, "%d %d", &j, &k);
            retorno = sobrepoe(inicio, j, k, retorno);
            if(retorno == true){
                //adicionaBcheia(inicio, j, k);
            }
            else{
                //adicionaBtracej(inicio, j, k);
            }
        }
        else if(strcmp(comando, "i?") == 0){
            fscanf(qry, "%d %f %f", &j, &x, &y);
            retorno = ponto(inicio, j, x, y, retorno);
            if(retorno == true){
                //adicionaPonto(inicio, j, x, y);
            }
            else{
                //adicionaLinha(inicio, j, x, y);
            }
        }
        else if(strcmp(comando, "pnt") == 0){
            fscanf(qry, "%d %s %s", &j, corb, corp);
            mudaCorj(inicio, j, corb, corp);
        }
        else if(strcmp(comando, "pnt*") == 0){
            fscanf(qry, "%d %d %s %s", &j, &k, corb, corp);
            mudaCorjk(inicio, j, k, corb, corp);
        }
        else if(strcmp(comando, "delf") == 0){
            fscanf(qry, "%d", &j);
            deletaElementoj(inicio, j);
        }
        else if(strcmp(comando, "delf*") == 0){
            fscanf(qry, "%d %d", &j, &k);
            deletaElementojk(inicio, j, k);
        }
    }
    fclose(qry);
    return inicio;
}

bool ponto(No *inicio, int j, float x, float y, bool interno){
    No *aux = NULL;
    aux = buscaElemento(inicio, j);
    if(aux == NULL){
        printf("\n\tNao foi possivel encontrar o elemento! ID: %d \n", j);
        return false;
    }
    if(aux->tipo == 'c'){
        //distancia de x = aux->fig->crl.x - x
        //distancia de y = aux->fig->crl.y - y
        //d^2 = dX^2 + dY^2
        //condição: d < r, d^2 < r^2
        //ou seja, dx^2 + dy^2 < r^2
        x = aux->fig->crl.x - x;
        y = aux->fig->crl.y - y;
        if(x*x + y*y < aux->fig->crl.r * aux->fig->crl.r){
            interno = true;
            printf("\nO ponto está dentro do circulo!");
        }
        else{
            printf("\nO ponto está fora do círculo!");
        }
        
    }

    else if(aux->tipo == 'r'){
        //x < px < x+w
        //y < py < y+h
        if((aux->fig->ret.x < x && x < aux->fig->ret.x + aux->fig->ret.w) && (aux->fig->ret.y < y && y < aux->fig->ret.y + aux->fig->ret.h)){
            interno = true;
            printf("\nO ponto esta dentro do retangulo!");
        }
        else{
            printf("\n O ponto esta fora do retangulo");
        }
    }

    else if(aux->tipo == 't'){
        printf("\nNao e possivel verificar um ponto no tipo texto!");
    }
    return interno;
}

bool sobrepoe(No *inicio, int j, int k, bool dentro){
    /*
    -buscar formas
    -identificar os tipos
    -verificar se existe a sobreposição
    */
    No *auxJ = buscaElemento(inicio, j); //fixo (x e y , x+w e y+h)
    if (auxJ == NULL){
        printf("\nNao foi possivel encontrar o elemento. ID: %d!", j);
        return false;
    }
    No *auxK = buscaElemento(inicio, k); //móvel (px e py)
    if(auxK == NULL){
        printf("\nNao foi possivel encontrar o elemento. ID: %d!", k);
        return false;
    }
    if(auxJ->tipo == 'c' && auxK->tipo == 'c'){ //circulo e circulo
        float deltaX = auxJ->fig->crl.x - auxK->fig->crl.x;
        float deltaY = auxJ->fig->crl.y - auxK->fig->crl.y;
        if (deltaX * deltaX + deltaY * deltaY < (auxJ->fig->crl.r + auxK->fig->crl.r) * (auxJ->fig->crl.r + auxK->fig->crl.r)){        
            dentro = true; 
            printf("\nOs circulos se sobrepoem!");
        }
        else{
            printf("\nOs circulos nao se sobrepoem!");
        }
    }
    /*
        x < px < x+w
        y < py < y+h
        if(x < px && px < x+w){
            if(y < py && py < y+h){
                //codigo
            }
        }
    */

    else if(auxJ->tipo == 'r' && auxK->tipo == 'r'){ //retangulo e retangulo
        //fixo
        float x = auxJ->fig->ret.x;
        float y = auxJ->fig->ret.y;
        float w = auxJ->fig->ret.w;
        float h = auxJ->fig->ret.h;

        //móvel
        float px = auxK->fig->ret.x;
        float py = auxK->fig->ret.y;
        
        //x,y    x+w,y    x,y+h    x+w,y+h

        if(x < px && px < x + w){
            if(y < py && py < y + h){
                dentro = true;
            }
        }

        px += auxK->fig->ret.w;
        if(x < px && px < x + w){
            if(y < py && py < y + h){
                dentro = true;
            }
        }

        py += auxK->fig->ret.h;
        //px = x+w     py = y+h
        px = auxK->fig->ret.x;
        if (x < px && px < x + w){
            if (y < py && py < y + h){
                dentro = true;
            }
        }

        //py = y+h  px = x
        px += auxK->fig->ret.w;
        if (x < px && px < x + w){
            if (y < py && py < y + h){
                dentro = true;
            }
        }

        if(dentro == true){
            printf("\nOs retangulos se sobrepoem!");
        }
        else{
            printf("\nOs retangulos nao se sobrepoem!");
        }
    }

    else if((auxJ->tipo == 'c' && auxK->tipo == 'r') || (auxJ->tipo == 'r' && auxK->tipo == 'c')){
        /*
            1 - Pegar círculo ok
            2 - Pegar retângulo ok
            3 - Achar o Nearest do Retângulo em relação ao raio ok
            4 - Achar a distância do N ao raio do circulo ok
            5 - Fazer a condição d < r ok
        */
        No *ret = NULL;
        No *crl = NULL;
        if(auxJ->tipo == 'c'){
            crl = auxJ;
            ret = auxK;
        }
        else{
            crl = auxK;
            ret = auxJ;
        }
        /*NearestX = Max(RectX, Min(CircleX, RectX + RectWidth));
        NearestY = Max(RectY, Min(CircleY, RectY + RectHeight));*/
    
        float nX = MAX(ret->fig->ret.x, MIN(crl->fig->crl.x, ret->fig->ret.x + ret->fig->ret.w));
        float nY = MAX(ret->fig->ret.y, MIN(crl->fig->crl.y, ret->fig->ret.y + ret->fig->ret.h));
        float deltaX = nX - crl->fig->crl.x;
        float deltaY = nY - crl->fig->crl.y;
        if(deltaX * deltaX + deltaY * deltaY < crl->fig->crl.r * crl->fig->crl.r){
            dentro = true;
            printf("O circulo e o retangulo se sobrepoem!");
        }  
        else{
            printf("Não se sobrepoem");
        }
    }

    return dentro;
}

void mudaCorj(No *inicio, int j, char corb[], char corp[]){
    No *aux = buscaElemento(inicio, j);
    if (aux == NULL){
        printf("\nNao foi possivel encontrar o elemento. ID: %d!", j);
    }
    if(aux->tipo == 'c'){
        strcpy(aux->fig->crl.corb, corb);
        strcpy(aux->fig->crl.corp, corp);
    }
    else if(aux->tipo == 'r'){
        strcpy(aux->fig->ret.corb, corb);
        strcpy(aux->fig->ret.corp, corp);
    }
    else if(aux->tipo == 't'){
        strcpy(aux->fig->texto.corb, corb);
        strcpy(aux->fig->texto.corp, corp);
    }
}

void mudaCorjk(No *inicio, int j, int k, char corb[], char corp[]){
    No *auxJ = buscaElemento(inicio, j);
    if (auxJ == NULL){
        printf("\nNao foi possivel encontrar o elemento. ID: %d!", j);
    }
    No *auxK = buscaElemento(inicio, k);
    if (auxK == NULL){
        printf("\nNao foi possivel encontrar o elemento. ID: %d!", k);
    }
    int menor;
    int maior;
    if(auxJ->id > auxK->id){
        maior = auxJ->id;
        menor = auxK->id;
    }
    else{
        maior = auxJ->id;
        menor = auxJ->id;
    }
    for(int i = menor; i < maior; i++){
        No *auxI = buscaElemento(inicio, i);
        if(auxI == NULL){
            printf("\nNao foi possivel encontrar o elemento. ID: %d!", i);
        }
        if (auxI->tipo == 'c'){
            strcpy(auxJ->fig->crl.corb, corb);
            strcpy(auxJ->fig->crl.corp, corp);
        }
        else if (auxI->tipo == 'r'){
            strcpy(auxJ->fig->ret.corb, corb);
            strcpy(auxJ->fig->ret.corp, corp);
        }
        else if (auxI->tipo == 't'){
            strcpy(auxJ->fig->texto.corb, corb);
            strcpy(auxJ->fig->texto.corp, corp);
        }
    }
}
