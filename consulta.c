#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<time.h>

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
        if(!qry) {
          printf("\nErro inesperado! Nao foi possivel abrir o arquivo. Arquivo "
                 "inexistente.");
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
    int j = 0, k = 0, i = 0;
    float x, y;
    char comando[6], corb[22], corp[22];

    FILE *qrySaida = NULL;
    printf("\n\t\tABRINDO ARQUIVO .txt . . . ");
    printf("\n\t\t > Arquivo .txt: %s", pathSaida);
    qrySaida = fopen(pathSaida, "a+");
    if(!qrySaida){
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
            printf("\n\n\t\tVERIFICANDO SOBREPOSIÇÃO . . .");
            retorno = sobrepoe(inicio, j, k, retorno);
            escreveTexto(inicio, qrySaida, comando, corb, corp, j, k, x, y, retorno);
            inicio = adicionaElemento(inicio, i*-1, 'r');
            if(retorno == 1){
               geraCoordenadas(inicio, j, k, x, y, comando, retorno, i*-1);
            }
            else if(retorno == 0){
                geraCoordenadas(inicio, j, k, x, y, comando, retorno, i*-1);
            }
        }
        else if(strcmp(comando, "i?") == 0){
            fscanf(qry, "%d %f %f", &j, &x, &y);
            printf("\n\n\t\tVERIFICANDO SE O PONTO X,Y É INTERNO . . .");
            retorno = ponto(inicio, j, x, y, retorno);
            escreveTexto(inicio, qrySaida, comando, corb, corp, j, k, x, y, retorno);
            inicio = adicionaElemento(inicio, i*-1, 'c');
            i++;
            inicio = adicionaElemento(inicio, i*-1, 'l');
            if(retorno == 1){
                geraCoordenadas(inicio, j, k, x, y, comando, retorno, i*-1);
            }
            else if(retorno == 0){
                geraCoordenadas(inicio, j, k, x, y, comando, retorno, i*-1);
            }
        }
        else if(strcmp(comando, "pnt") == 0){
            fscanf(qry, "%d %s %s", &j, corb, corp);
            printf("\n\n\t\tMUDANDO COR . . .");
            retorno = mudaCorj(inicio, j, corb, corp);
            escreveTexto(inicio, qrySaida, comando, corb, corp, j, k, x, y, retorno);
        }
        else if(strcmp(comando, "pnt*") == 0){
            fscanf(qry, "%d %d %s %s", &j, &k, corb, corp);
            printf("\n\n\t\tMUDANDO CORES . . .");
            retorno = mudaCorjk(inicio, j, k, corb, corp);
            escreveTexto(inicio, qrySaida, comando, corb, corp, j, k, x, y, retorno);
        }
        else if(strcmp(comando, "delf") == 0){
            fscanf(qry, "%d", &j);
            printf("\n\n\t\tDELETANDO ELEMENTO . . .");
            escreveTexto(inicio, qrySaida, comando, corb, corp, j, k, x, y, retorno);
            inicio = deletaElementoj(inicio, j);
            
        }
        else if(strcmp(comando, "delf*") == 0){
            fscanf(qry, "%d %d", &j, &k);
            printf("\n\n\t\tDELETANDO ELEMENTOS. . .");
            escreveTexto(inicio, qrySaida, comando, corb, corp, j, k, x, y, retorno);
            inicio = deletaElementojk(inicio, j, k);
        }
        
        i++;
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
    if(auxJ == NULL){
        printf("\n\tNao foi possivel encontrar o elemento J. ID: %d!", j);
        return -2;
    }
    No *auxK = buscaElemento(inicio, k); //móvel (px e py)
    if(auxK == NULL){
        printf("\n\tNao foi possivel encontrar o elemento K. ID: %d!", k);
        return -2;
    }

    if(auxJ->tipo == 'c' && auxK->tipo == 'c'){ //circulo e circulo
        float deltaX = auxJ->fig->crl.x - auxK->fig->crl.x;
        float deltaY = auxJ->fig->crl.y - auxK->fig->crl.y;
        if(deltaX * deltaX + deltaY * deltaY <= (auxJ->fig->crl.r + auxK->fig->crl.r) * 
            (auxJ->fig->crl.r + auxK->fig->crl.r)){        
            dentro = 1; 
            printf("\n\tOs circulos %d e %d se sobrepoem!", j, k);
        }
        else{
            printf("\n\tOs circulos %d e %d nao se sobrepoem!", j, k);
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
        if(x <= px && px <= x + w){
            if(y <= py && py <= y + h){
                dentro = 1;
            }
        }

        px += auxK->fig->ret.w;
        if(x <= px && px <= x + w){
            if(y <= py && py <= y + h){
                dentro = 1;
            }
        }

        py += auxK->fig->ret.h; //px = x+w  py = y+h
        px = auxK->fig->ret.x;
        if(x <= px && px <= x + w){
            if(y <= py && py <= y + h){
                dentro = 1;
            }
        }

        px += auxK->fig->ret.w; //py = y+h  px = x
        if(x <= px && px <= x + w){
            if(y <= py && py <= y + h){
                dentro = 1;
            }
        }

        if(dentro == 1){
            printf("\n\tOs retangulos %d e %d se sobrepoem!", j, k);
        }
        else{
            printf("\n\tOs retangulos %d e %d nao se sobrepoem!", j, k);
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
            if(auxJ->tipo == 'c'){
                printf("\n\tO circulo %d e o retangulo %d se sobrepoem!", j, k);
            }
            else{
                printf("\n\tO circulo %d e o retangulo %d se sobrepoem!", k, j);
            }
        }  
        else{
            if(auxJ->tipo == 'c'){
                printf("\n\tO circulo %d e o retangulo %d nao se sobrepoem!", j, k);
            }
            else{
                printf("\n\tO circulo %d e o retangulo %d nao se sobrepoem!", k, j);
            }
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
    if(aux == NULL){
        printf("\n\tNao foi possivel encontrar o elemento J. ID: %d!", j);
        return -2;
    }

    if(aux->tipo == 'c'){ //circulo
        //distancia de x = aux->fig->crl.x - x
        //distancia de y = aux->fig->crl.y - y
        //d^2 = dX^2 + dY^2
        //condição: d < r, d^2 < r^2
        //ou seja, dx^2 + dy^2 < r^2
        printf("\n\tO ponto %f,%f", x,y);
        x = aux->fig->crl.x - x;
        y = aux->fig->crl.y - y;
        if(x * x + y * y < aux->fig->crl.r * aux->fig->crl.r){
            interno = 1;
            printf(" esta dentro do circulo %d!", j);
        }
        else{
            printf(" esta fora do circulo %d!", j);
        }
    }

    else if(aux->tipo == 'r'){ //retangulo
        //x < px < x+w
        //y < py < y+h
        printf("\n\tO ponto %f,%f", x,y);
        if ((aux->fig->ret.x < x && x < aux->fig->ret.x + aux->fig->ret.w) && 
            (aux->fig->ret.y < y && y < aux->fig->ret.y + aux->fig->ret.h)){
            interno = 1;
            printf(" esta dentro do retangulo %d!", j);
        }
        else{
            printf(" esta fora do retangulo %d!", j);
        }
    }

    else if(aux->tipo == 't'){ //texto
        interno = -1;
        printf("\n\tNao e possivel verificar um ponto no tipo texto!");
        
    }

    return interno;
}

int mudaCorj(No *inicio, int j, char corb[], char corp[]){ //pnt
    No *aux = buscaElemento(inicio, j);
    if(aux == NULL){
        printf("\n\tNao foi possivel encontrar o elemento J. ID: %d!", j);
        return -2;
    }

    if(aux->tipo == 'c'){
        printf("\n\tCor da borda antes: %s | ", aux->fig->crl.corb);
        strcpy(aux->fig->crl.corb, corb);
        printf("Cor da borda depois: %s", aux->fig->crl.corb);
        printf("\n\tCor do preenchimento antes: %s | ", aux->fig->crl.corp);
        strcpy(aux->fig->crl.corp, corp);
        printf("Cor do preenchimento depois: %s\n", aux->fig->crl.corp);
    }

    else if(aux->tipo == 'r'){
        printf("\n\tCor da borda antes: %s | ", aux->fig->ret.corb);
        strcpy(aux->fig->ret.corb, corb);
        printf("Cor da borda depois: %s", aux->fig->ret.corb);
        printf("\n\tCor do preenchimento antes: %s | ", aux->fig->ret.corp);
        strcpy(aux->fig->ret.corp, corp);
        printf("Cor do preenchimento depois: %s\n", aux->fig->ret.corp);
    }

    else if(aux->tipo == 't'){
        printf("\n\tCor da borda antes: %s | ", aux->fig->texto.corb);
        strcpy(aux->fig->texto.corb, corb);
        printf("Cor da borda depois: %s", aux->fig->texto.corb);
        printf("\n\tCor do preenchimento antes: %s | ", aux->fig->texto.corp);
        strcpy(aux->fig->texto.corp, corp);
        printf("Cor do preenchimento depois: %s\n", aux->fig->texto.corp);
    }
    
    return 1;
}

int mudaCorjk(No *inicio, int j, int k, char corb[], char corp[]){ //pnt*
    No *auxJ = buscaElemento(inicio, j);
    if(auxJ == NULL){
        printf("\n\tNao foi possivel encontrar o elemento J. ID: %d!", j);
        return -2;
    }
    No *auxK = buscaElemento(inicio, k);
    if(auxK == NULL){
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
        maior = auxK->id;
        menor = auxJ->id;
    }

    for(int i = menor; i <= maior; i++){
        mudaCorj(inicio, i, corb, corp);
    }

    return 1;
}

No *geraCoordenadas(No *inicio, int j, int k, float x, float y, char comando[], int retorno, int id){
    No *auxJ = buscaElemento(inicio, j);
    float xMeio, yMeio;
    float xR, yR, wR, hR;
 
    if(strcmp(comando, "i?") == 0){
        if(auxJ->tipo == 'r'){
            xMeio = (auxJ->fig->ret.x + auxJ->fig->ret.w)/2;
            yMeio = (auxJ->fig->ret.y + auxJ->fig->ret.h)/2;
        }
        else{
            xMeio = auxJ->fig->crl.x;
            yMeio = auxJ->fig->crl.y;
        }

        if(retorno == 1){
            inicio = adicionaCirculo(inicio, id+1, 2, x, y, "none", "blue");
            inicio = adicionaLinha(inicio, id, xMeio, yMeio, x, y, "blue");
        }
        else{
            inicio = adicionaCirculo(inicio, id+1, 2, xMeio, yMeio, "none", "magenta");
            inicio = adicionaLinha(inicio, id, xMeio, yMeio, x, y, "magenta");
        }
    }

    else if(strcmp(comando, "o?") == 0){
        No *auxK = buscaElemento(inicio, k);
        if(auxJ->tipo == 'r' && auxK->tipo == 'r'){
            xR = MIN(auxJ->fig->ret.x, auxK->fig->ret.x);
            yR = MIN(auxJ->fig->ret.y, auxK->fig->ret.y);
            wR = auxK->fig->ret.x + auxK->fig->ret.w + auxJ->fig->ret.x + auxJ->fig->ret.w;
            hR = auxK->fig->ret.y + auxK->fig->ret.h + auxJ->fig->ret.y + auxJ->fig->ret.h;
        }

        if(auxJ->tipo == 'c' && auxK->tipo == 'c'){
            xR = MIN(auxJ->fig->crl.x, auxK->fig->crl.x);
            yR = MIN(auxJ->fig->crl.y, auxK->fig->crl.y);
            if(xR == auxJ->fig->crl.x){
                xR += auxJ->fig->crl.r;
            }
            else{
                xR += auxK->fig->crl.r;
            }
            
            if(yR == auxJ->fig->crl.y){
                yR += auxJ->fig->crl.r;
            }
            else{
                yR += auxK->fig->crl.r;
            }

            wR = (auxJ->fig->crl.r + auxJ->fig->crl.x) * 2 + (auxK->fig->crl.r + auxK->fig->crl.x);
            hR = (auxJ->fig->crl.r + auxJ->fig->crl.y) * 2 + (auxK->fig->crl.r + auxK->fig->crl.y);
        }
    
        if((auxJ->tipo == 'r' && auxK->tipo == 'c') || (auxJ->tipo == 'c' && auxK->tipo == 'r')){
            No *ret = NULL;
            No *crl = NULL;
            float sobraX = 0, sobraY = 0;

            if(auxJ->tipo == 'c'){
                crl = auxJ;
                ret = auxK;
            }
            else{
                crl = auxK;
                ret = auxJ;
            }

            xR = MIN(crl->fig->crl.x, ret->fig->ret.x);
            yR = MIN(crl->fig->crl.y, ret->fig->ret.y);
            if(xR == crl->fig->crl.x){ //se o x circulo estiver em 1o
                xR -= crl->fig->crl.r;
                sobraX = (crl->fig->crl.x + crl->fig->crl.r) - ret->fig->ret.x;
            }
            else{
                sobraX = (crl->fig->crl.x - crl->fig->crl.r) - (ret->fig->ret.x + ret->fig->ret.w);
            }
            wR = ((crl->fig->crl.r * 2) + ret->fig->ret.w) - sobraX;

            if(yR == crl->fig->crl.y){
                yR -= crl->fig->crl.r;
            }
            if(crl->fig->crl.y >= ret->fig->ret.y){
                sobraY = (crl->fig->crl.y - crl->fig->crl.r) - ret->fig->ret.y;
            }
            else{
                sobraY = (crl->fig->crl.y + crl->fig->crl.r) - ret->fig->ret.y;
            }
            hR = ((crl->fig->crl.r * 2) + ret->fig->ret.h) - sobraY;
        }

        if(retorno == 1){
            inicio = adicionaRetangulo(inicio, id, wR, hR, xR, yR, "black", "none");
        }
        else{
            //inicio = adicionaRetangulo(inicio, id, wR, hR, xR, yR, "black", "none");
        }
    }
//<rect x="3.000000" y="3.000000" width="6.000000" height="5.000000" style="fill:black;stroke:black;fill-opacity:0.0;stroke-width:0.02"/>
    return inicio;
}
