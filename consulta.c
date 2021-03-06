#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lista.h"
#include "consulta.h"
#include "trataString.h"
#include "txt.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))


void abreQry(No *inicio, char dirEntrada[], char arqQry[], char pathSaida[]){
    FILE *qry = NULL;
    char *pathEntrada = NULL;

    printf("\n\t\tABRINDO ARQUIVO .qry . . . ");
    if(dirEntrada == NULL){
        printf("\n\t\t > Arquivo .qry: %s", arqQry);
        qry = fopen(arqQry, "r");
    }
    else{
        pathEntrada = trataStringCaminho(dirEntrada, arqQry);
        printf("\n\t > Arquivo .qry: %s", pathEntrada);
        qry = fopen(pathEntrada, "r");
    }
    if(!qry){
        printf("\nErro inesperado! Nao foi possivel abrir o arquivo. Diretorio ou arquivo inexistente.");
        printf("\n---------------------------------------------------\n");
        exit(1);
    }

    printf("\n\t Arquivo .qry aberto com sucesso!");
    printf("\n\t---------------------------------------------------\n");
    comandoQry(inicio, qry, pathSaida);
    fclose(qry);
    free(pathEntrada);

}

void comandoQry(No *inicio, FILE *qry, char pathSaida[]){
    int j = 0, k = 0, i = 0, retorno = 0;
    float x, y;
    char comando[6], corb[22], corp[22];

    printf("\n\t\tABRINDO ARQUIVO .txt . . . ");
    printf("\n\t\t > Arquivo .txt: %s", pathSaida);
    FILE *arqTxt = fopen(pathSaida, "a");
    if(!arqTxt){
        printf("\nErro inesperado! Nao foi possivel abrir o arquivo. Arquivo inexistente.");
        printf("\n---------------------------------------------------\n");
        exit(1);
    }

    printf("\n\tArquivo .txt aberto com sucesso!");
    printf("\n\t---------------------------------------------------\n");

    printf("\n\t\tLENDO ARQUIVO .qry . . . ");
    while(1){
        retorno = 0;
        fscanf(qry, "%s", comando); //vai pra proxima linha automaticamente?

        if(feof(qry)){
            break;
        }

        if(strcmp(comando, "o?") == 0){
            fscanf(qry, "%d %d", &j, &k);
            printf("\n\n\t\tVERIFICANDO SOBREPOSICAO . . .");
            retorno = sobrepoe(inicio, j, k);
            escreveTexto(inicio, arqTxt, comando, corb, corp, j, k, x, y, retorno);
            inicio = adicionaElemento(inicio, i * -1, 'r');

            if(retorno == 1){
                geraCoordenadas(inicio, j, k, x, y, comando, retorno, i * -1);
            }
            else if(retorno == 0){
                geraCoordenadas(inicio, j, k, x, y, comando, retorno, i * -1);
            }
        }

        else if(strcmp(comando, "i?") == 0){
            fscanf(qry, "%d %f %f", &j, &x, &y);
            printf("\n\n\t\tVERIFICANDO SE O PONTO X,Y e INTERNO . . .");
            retorno = ponto(inicio, j, x, y);
            escreveTexto(inicio, arqTxt, comando, corb, corp, j, k, x, y, retorno);
            inicio = adicionaElemento(inicio, i * -1, 'c');
            i++;
            inicio = adicionaElemento(inicio, i * -1, 'l');

            if(retorno == 1){
                geraCoordenadas(inicio, j, k, x, y, comando, retorno, i * -1);
            }
            else if(retorno == 0){
                geraCoordenadas(inicio, j, k, x, y, comando, retorno, i * -1);
            }
        }

        else if(strcmp(comando, "pnt") == 0){
            fscanf(qry, "%d %s %s", &j, corb, corp);
            printf("\n\n\t\tMUDANDO COR . . .");
            retorno = mudaCorj(inicio, j, corb, corp);
            escreveTexto(inicio, arqTxt, comando, corb, corp, j, k, x, y, retorno);
        }

        else if(strcmp(comando, "pnt*") == 0){
            fscanf(qry, "%d %d %s %s", &j, &k, corb, corp);
            printf("\n\n\t\tMUDANDO CORES . . .");
            retorno = mudaCorjk(inicio, j, k, corb, corp);
            escreveTexto(inicio, arqTxt, comando, corb, corp, j, k, x, y, retorno);
        }

        else if(strcmp(comando, "delf") == 0){
            fscanf(qry, "%d", &j);
            printf("\n\n\t\tDELETANDO ELEMENTO . . .");
            escreveTexto(inicio, arqTxt, comando, corb, corp, j, k, x, y, retorno);
            inicio = deletaElementoj(inicio, j);
        }

        else if(strcmp(comando, "delf*") == 0){
            fscanf(qry, "%d %d", &j, &k);
            printf("\n\n\t\tDELETANDO ELEMENTOS. . .");
            escreveTexto(inicio, arqTxt, comando, corb, corp, j, k, x, y, retorno);
            inicio = deletaElementojk(inicio, j, k);
        }

        else{
            printf("\nComando inexistente!\nDigite H para obter lista de comandos");
            printf("\nLinha do erro no arquivo .qry: %d", i);
            printf("\n\t---------------------------------------------------\n");
            exit(1);
        }
        
        i++;
    }
    printf("\n\n\tLeitura do arquivo .qry finalizada com sucesso!");
    fclose(arqTxt);

}


int sobrepoe(No *inicio, int j, int k){ //o?
    /*
        -buscar formas
        -identificar os tipos
        -verificar se existe a sobreposicao
    */
    int dentro = 0;
    No *auxJ = buscaElemento(inicio, j); //fixo (x e y , x + w e y + h)
    if(auxJ == NULL){
        printf("\n\tNao foi possivel encontrar o elemento J. ID: %d!", j);
        return -2;
    }
    No *auxK = buscaElemento(inicio, k); //movel (px e py)
    if(auxK == NULL){
        printf("\n\tNao foi possivel encontrar o elemento K. ID: %d!", k);
        return -2;
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
    if(auxJ->tipo == 'c' && auxK->tipo == 'c'){ //circulo e circulo
        float deltaX = auxJ->fig->crl.x - auxK->fig->crl.x;
        float deltaY = auxJ->fig->crl.y - auxK->fig->crl.y;

        if(deltaX * deltaX + deltaY * deltaY <= (auxJ->fig->crl.r + auxK->fig->crl.r) * (auxJ->fig->crl.r + auxK->fig->crl.r)){
            dentro = 1;
            printf("\n\tOs circulos %d e %d se sobrepoem!", j, k);
        }
        else{
            printf("\n\tOs circulos %d e %d nao se sobrepoem!", j, k);
        }
    }

    else if(auxJ->tipo == 'r' && auxK->tipo == 'r'){ //retangulo e retangulo
        //fixo
        float x = auxJ->fig->ret.x;
        float y = auxJ->fig->ret.y;
        float w = auxJ->fig->ret.w;
        float h = auxJ->fig->ret.h;
        //movel
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
            1 - Pegar circulo ok
            2 - Pegar retangulo ok
            3 - Achar o Nearest do Retangulo em relacao ao raio ok
            4 - Achar a distancia do N ao raio do circulo ok
            5 - Fazer a condicao d < r ok
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

    else if(auxJ->tipo == 't' || auxK->tipo == 't'){ //texto
        printf("\n\tNao e possivel verificar sobreposicoes no tipo texto!");
        return -1;
    }

    return dentro;
}

int ponto(No *inicio, int j, float x, float y){ //i?
    No *aux = NULL;
    aux = buscaElemento(inicio, j);
    if(aux == NULL){
        printf("\n\tNao foi possivel encontrar o elemento J. ID: %d!", j);
        return -2;
    }

    int interno = 0;

    if(aux->tipo == 'c'){ //circulo
        /* 
            distancia de x = aux->fig->crl.x - x
            distancia de y = aux->fig->crl.y - y
            d^2 = dX^2 + dY^2
            condicao: d < r, d^2 < r^2
            ou seja, dx^2 + dy^2 < r^2
        */
        printf("\n\tO ponto %f,%f", x, y);
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
        printf("\n\tO ponto %f,%f", x, y);
        if((aux->fig->ret.x < x && x < aux->fig->ret.x + aux->fig->ret.w) && (aux->fig->ret.y < y && y < aux->fig->ret.y + aux->fig->ret.h)){
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
        printf("\n\tNao foi possivel encontrar o elemento K. ID: %d!", k);
        return -2;
    }

    int menor, maior;
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

void geraCoordenadas(No *inicio, int j, int k, float x, float y, char comando[], int retorno, int id){
    float xMeio, yMeio;
    float xR, yR, wR, hR;
    float sobraX = 0, sobraY = 0;

    No *auxJ = buscaElemento(inicio, j);

    if(strcmp(comando, "i?") == 0){
        if(auxJ->tipo == 'r'){
            xMeio = (auxJ->fig->ret.x + auxJ->fig->ret.w) / 2;
            yMeio = (auxJ->fig->ret.y + auxJ->fig->ret.h) / 2;
        }
        else{
            xMeio = auxJ->fig->crl.x;
            yMeio = auxJ->fig->crl.y;
        }

        if(retorno == 1){
            inicio = adicionaCirculo(inicio, id + 1, 2, x, y, "none", "blue");
            inicio = adicionaLinha(inicio, id, xMeio, yMeio, x, y, "blue");
        }
        else{
            inicio = adicionaCirculo(inicio, id + 1, 2, xMeio, yMeio, "none", "magenta");
            inicio = adicionaLinha(inicio, id, xMeio, yMeio, x, y, "magenta");
        }
    }

    else if(strcmp(comando, "o?") == 0){
        No *auxK = buscaElemento(inicio, k);

        if(auxJ->tipo == 'r' && auxK->tipo == 'r'){ //ret e ret
            No *r1 = NULL;
            No *r2 = NULL;

            //width
            xR = MIN(auxJ->fig->ret.x, auxK->fig->ret.x);
            if(xR == auxJ->fig->ret.x){
                r1 = auxJ;
                r2 = auxK;
            }
            else{
                r1 = auxK;
                r2 = auxJ;
            }

            if(r1->fig->ret.x <= r2->fig->ret.x && r1->fig->ret.x + r1->fig->ret.w >= r2->fig->ret.x + r2->fig->ret.w){
                wR = r1->fig->ret.w;
            }
            else{
                sobraX = abs((r1->fig->ret.x + r1->fig->ret.w) - (r2->fig->ret.x + r2->fig->ret.w));
                if(retorno == 1){
                    wR = MAX(r1->fig->ret.w, r2->fig->ret.w) + sobraX;
                }
                else{
                    wR = r1->fig->ret.w + r2->fig->ret.w + sobraX;
                }
            }

            //high
            yR = MIN(r1->fig->ret.y, r2->fig->ret.y);
            if(yR == auxJ->fig->ret.y){
                r1 = auxJ;
                r2 = auxK;
            }
            else{
                r1 = auxK;
                r2 = auxJ;
            }

            if(r1->fig->ret.y <= r2->fig->ret.y && r1->fig->ret.y + r1->fig->ret.h >= r2->fig->ret.y + r2->fig->ret.h){
                hR = r1->fig->ret.h;
            }
            else{
                sobraY = abs((r1->fig->ret.y + r1->fig->ret.h) - (r2->fig->ret.y + r2->fig->ret.h));
                if(retorno == 1){
                    hR = MAX(r1->fig->ret.h, r2->fig->ret.h) + sobraY;
                }
                else{
                    hR = r1->fig->ret.w + r2->fig->ret.w + sobraY;
                }
            }
        }

        if(auxJ->tipo == 'c' && auxK->tipo == 'c'){
            No *c1 = NULL;
            No *c2 = NULL;

            //width
            xR = MIN(auxJ->fig->crl.x - auxJ->fig->crl.r, auxK->fig->crl.x - auxK->fig->crl.r);
            if(xR == auxJ->fig->crl.x - auxJ->fig->crl.r){
                c1 = auxJ;
                c2 = auxK;
            }
            else{
                c1 = auxK;
                c2 = auxJ;
            }

            if(c1->fig->crl.x + c1->fig->crl.r >= c2->fig->crl.x + c2->fig->crl.r && c1->fig->crl.x - c1->fig->crl.r <= c2->fig->crl.x - c2->fig->crl.r){
                wR = c1->fig->crl.r * 2;
            }
            else{
                sobraX = abs((c1->fig->crl.x + c1->fig->crl.r) - (c2->fig->crl.x - c2->fig->crl.r));
                if(retorno == 1){
                    wR = MAX(c1->fig->crl.r, c2->fig->crl.r) * 2 + sobraX;
                }
                else{
                    wR = c1->fig->crl.r * 2 + c2->fig->crl.r * 2 + sobraX;
                }
            }

            //high
            yR = MIN(auxJ->fig->crl.y - auxJ->fig->crl.r, auxK->fig->crl.y - auxK->fig->crl.r);
            if(yR == auxJ->fig->crl.y - auxJ->fig->crl.r){
                c1 = auxJ;
                c2 = auxK;
            }
            else{
                c1 = auxK;
                c2 = auxJ;
            }

            if(c1->fig->crl.y + c1->fig->crl.r >= c2->fig->crl.y + c2->fig->crl.r && c1->fig->crl.y - c1->fig->crl.r <= c2->fig->crl.y - c2->fig->crl.r){
                hR = c1->fig->crl.r * 2;
            }
            else{
                sobraY = abs((c1->fig->crl.y + c1->fig->crl.r) - (c2->fig->crl.y - c2->fig->crl.r));
                if(retorno == 1){
                    hR = MAX(c1->fig->crl.r, c2->fig->crl.r) * 2 + sobraY;
                }
                else{
                    hR = c1->fig->crl.r * 2 + c2->fig->crl.r * 2 + sobraY;
                }
            }
        }

        if((auxJ->tipo == 'r' && auxK->tipo == 'c') || (auxJ->tipo == 'c' && auxK->tipo == 'r')){
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

            //width
            xR = MIN(crl->fig->crl.x - crl->fig->crl.r, ret->fig->ret.x);   //Ve qual x,y comeca o retangulo a ser desenhado
            if(xR == crl->fig->crl.x - crl->fig->crl.r){    //se o x circulo estiver em 1o no x
                if(crl->fig->crl.x - crl->fig->crl.r < ret->fig->ret.x && crl->fig->crl.x + crl->fig->crl.r > ret->fig->ret.x + ret->fig->ret.w){
                    wR = crl->fig->crl.x * 2;
                }
                else{
                    sobraX = abs((crl->fig->crl.x - crl->fig->crl.r) - ret->fig->ret.x);
                    wR = ret->fig->ret.w + sobraX;
                }
            }
            else{
                if(crl->fig->crl.x + crl->fig->crl.r <= ret->fig->ret.x + ret->fig->ret.w && crl->fig->crl.x - crl->fig->crl.r >= ret->fig->ret.x){
                    sobraX = 0;
                }
                else{
                    sobraX = (crl->fig->crl.x + crl->fig->crl.r) - (ret->fig->ret.x + ret->fig->ret.w);
                }
                wR = ret->fig->ret.w + sobraX;
            }
            
            //high
            yR = MIN(crl->fig->crl.y - crl->fig->crl.r, ret->fig->ret.y);
            if(yR == crl->fig->crl.y - crl->fig->crl.r){    //se o circulo e o primeiro no y
                if(crl->fig->crl.y - crl->fig->crl.r < ret->fig->ret.y && crl->fig->crl.y + crl->fig->crl.r > ret->fig->ret.y + ret->fig->ret.h){
                    hR = crl->fig->crl.y * 2;
                }
                else{
                    sobraY = abs((crl->fig->crl.y - crl->fig->crl.r) - ret->fig->ret.y);
                    hR = ret->fig->ret.h + sobraY;
                }
            }
            else{
                if(crl->fig->crl.y + crl->fig->crl.r <= ret->fig->ret.y + ret->fig->ret.h && crl->fig->crl.y - crl->fig->crl.r >= ret->fig->ret.y){
                    sobraY = 0;
                }
                else{
                    sobraY = (crl->fig->crl.y + crl->fig->crl.r) - (ret->fig->ret.y + ret->fig->ret.h);
                }
                hR = ret->fig->ret.h + sobraY;
            }
        }

        inicio = adicionaRetangulo(inicio, id, wR, hR, xR, yR, "none", "black");
        auxJ = buscaElemento(inicio, id);
        if(retorno == 1){
            auxJ->fig->ret.trac = 0;
        }
        else{
            auxJ->fig->ret.trac = 1;
        }
    }
}
