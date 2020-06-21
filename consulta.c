#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lista.h"
#include "consulta.h"
#include "trataString.h"
#include "txt.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y)) 

No *abreQry(No *inicio, char dirEntrada[], char arqQry[], char pathSaida[]){
    FILE *qry = NULL;
    char *pathEntrada = NULL;

    printf("\n\t\tABRINDO ARQUIVO .qry . . . ");
    if(dirEntrada == NULL){
        printf("\n\t\t > Arquivo .qry: %s", arqQry);
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
    inicio = comandoQry(qry, pathSaida, inicio);

    fclose(qry);
    free(pathEntrada);
    return inicio;
}

No *comandoQry(FILE *qry, char pathSaida[], No *inicio){
    int retorno;
    int j = 0, k = 0;
    float x, y;
    char comando[6], corb[22], corp[22];

    FILE *qrySaida = NULL;
    printf("\n\t\tABRINDO ARQUIVO .txt . . . ");
    printf("\n\t\t > Arquivo .txt: %s", pathSaida);
    qrySaida = fopen(pathSaida, "a+");
    if (!qrySaida){
        printf("\nErro inesperado! Nao foi possivel abrir o arquivo. Arquivo inexistente.");
        exit(1);
    }
    printf("\n\tArquivo .txt aberto com sucesso!");
    printf("\n\t---------------------------------------------------\n");

    while(1){
        retorno = 0;
        fscanf(qry, "%s", comando); //vai pra proxima linha automaticamente?
        if(feof(qry)){
            break;
        }
        if(strcmp(comando, "o?") == 0){ 
            fscanf(qry, "%d %d", &j, &k);
            retorno = sobrepoe(inicio, j, k, retorno);
            escreveTexto(inicio, qrySaida, comando, corb, corp, j, k, x, y, retorno);

            if(retorno == 1){
                //adicionaBcheia(inicio, j, k);
            }
            else if(retorno == 0){
                //adicionaBtracej(inicio, j, k);
            }
            else{
                //
            }
        }
        else if(strcmp(comando, "i?") == 0){
            fscanf(qry, "%d %f %f", &j, &x, &y);
            retorno = ponto(inicio, j, x, y, retorno);
            escreveTexto(inicio, qrySaida, comando, corb, corp, j, k, x, y, retorno);
            if(retorno == 1){
                //adicionaPonto(inicio, j, x, y);
            }
            else if(retorno == 0){
                //adicionaLinha(inicio, j, x, y);
            }
            else{
                //
            }
        }
        else if(strcmp(comando, "pnt") == 0){
            fscanf(qry, "%d %s %s", &j, corb, corp);
            retorno = mudaCorj(inicio, j, corb, corp);
            escreveTexto(inicio, qrySaida, comando, corb, corp, j, k, x, y, retorno);
        }
        else if(strcmp(comando, "pnt*") == 0){
            fscanf(qry, "%d %d %s %s", &j, &k, corb, corp);
            retorno = mudaCorjk(inicio, j, k, corb, corp);
            escreveTexto(inicio, qrySaida, comando, corb, corp, j, k, x, y, retorno);
        }
        else if(strcmp(comando, "delf") == 0){
            fscanf(qry, "%d", &j);
            escreveTexto(inicio, qrySaida, comando, corb, corp, j, k, x, y, retorno);
            inicio = deletaElementoj(inicio, j);
            
        }
        else if(strcmp(comando, "delf*") == 0){
            fscanf(qry, "%d %d", &j, &k);
            inicio = deletaElementojk(inicio, j, k);
            escreveTexto(inicio, qrySaida, comando, corb, corp, j, k, x, y, retorno);
        }
    }

    fclose(qrySaida);
    return inicio;
}


int sobrepoe(No *inicio, int j, int k, int dentro){  //o?
    /*
    -buscar formas
    -identificar os tipos
    -verificar se existe a sobreposição
    */
    No *auxJ = buscaElemento(inicio, j); //fixo (x e y , x+w e y+h)
    if (auxJ == NULL){
        printf("\n\tNao foi possivel encontrar o elemento J. ID: %d!", j);
    }
    No *auxK = buscaElemento(inicio, k); //móvel (px e py)
    if(auxK == NULL){
        printf("\n\tNao foi possivel encontrar o elemento K. ID: %d!", k);
    }

    if(auxJ->tipo == 'c' && auxK->tipo == 'c'){ //circulo e circulo
        float deltaX = auxJ->fig->crl.x - auxK->fig->crl.x;
        float deltaY = auxJ->fig->crl.y - auxK->fig->crl.y;
        if (deltaX * deltaX + deltaY * deltaY < (auxJ->fig->crl.r + auxK->fig->crl.r) * 
            (auxJ->fig->crl.r + auxK->fig->crl.r)){        
            dentro = 1; 
            printf("\n\tOs circulos se sobrepoem!");
        }
        else{
            printf("\n\tOs circulos nao se sobrepoem!");
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
                dentro = 1;
            }
        }

        px += auxK->fig->ret.w;
        if(x < px && px < x + w){
            if(y < py && py < y + h){
                dentro = 1;
            }
        }

        py += auxK->fig->ret.h; //px = x+w  py = y+h
        px = auxK->fig->ret.x;
        if (x < px && px < x + w){
            if (y < py && py < y + h){
                dentro = 1;
            }
        }

        px += auxK->fig->ret.w; //py = y+h  px = x
        if (x < px && px < x + w){
            if (y < py && py < y + h){
                dentro = 1;
            }
        }

        if(dentro == 1){
            printf("\n\tOs retangulos se sobrepoem!");
        }
        else{
            printf("\n\tOs retangulos nao se sobrepoem!");
        }
    }

    else if((auxJ->tipo == 'c' && auxK->tipo == 'r') || (auxJ->tipo == 'r' && auxK->tipo == 'c')){ //retangulo e circulo e vice-versa
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
            dentro = 1;
            printf("\n\tO circulo e o retangulo se sobrepoem!");
        }  
        else{
            printf("\n\tO circulo e o retangulo nao se sobrepoem!");
        }
    }

    else if (auxJ->tipo == 't' || auxK->tipo == 't'){ //texto
        printf("\n\tNao e possivel verificar sobreposições no tipo texto!");
        return -1;
    }
    
    return dentro;
}

int ponto(No *inicio, int j, float x, float y, int interno){ //i?
    No *aux = NULL;
    aux = buscaElemento(inicio, j);
    if (aux == NULL){
        printf("\n\tNao foi possivel encontrar o elemento J. ID: %d!", j);
        return -2;
    }

    if (aux->tipo == 'c'){ //circulo
        //distancia de x = aux->fig->crl.x - x
        //distancia de y = aux->fig->crl.y - y
        //d^2 = dX^2 + dY^2
        //condição: d < r, d^2 < r^2
        //ou seja, dx^2 + dy^2 < r^2
        x = aux->fig->crl.x - x;
        y = aux->fig->crl.y - y;
        if (x * x + y * y < aux->fig->crl.r * aux->fig->crl.r){
            interno = 1;
            printf("\n\tO ponto está dentro do circulo!");
        }
        else{
            printf("\n\tO ponto está fora do circulo!");
        }
    }

    else if (aux->tipo == 'r'){ //retangulo
        //x < px < x+w
        //y < py < y+h
        if ((aux->fig->ret.x < x && x < aux->fig->ret.x + aux->fig->ret.w) && 
            (aux->fig->ret.y < y && y < aux->fig->ret.y + aux->fig->ret.h)){
            interno = 1;
            printf("\n\tO ponto esta dentro do retangulo!");
        }
        else{
            printf("\n\tO ponto esta fora do retangulo!");
        }
    }

    else if (aux->tipo == 't'){ //texto
        interno = -1;
        printf("\n\tNao e possivel verificar um ponto no tipo texto!");
        
    }
    
    return interno;
}

int mudaCorj(No *inicio, int j, char corb[], char corp[]){ //pnt
    No *aux = buscaElemento(inicio, j);
    if (aux == NULL){
        printf("\n\tNao foi possivel encontrar o elemento J. ID: %d!", j);
        return -2;
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
    
    return 1;
}

int mudaCorjk(No *inicio, int j, int k, char corb[], char corp[]){ //pnt*
    No *auxJ = buscaElemento(inicio, j);
    if (auxJ == NULL){
        printf("\n\tNao foi possivel encontrar o elemento J. ID: %d!", j);
        return -2;
    }
    No *auxK = buscaElemento(inicio, k);
    if (auxK == NULL){
        return -2;
        printf("\n\tNao foi possivel encontrar o elemento K. ID: %d!", k);
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
        mudaCorj(inicio, i, corb, corp);
    }

    return 1;
}
