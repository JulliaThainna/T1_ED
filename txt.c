#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "txt.h"
#include "lista.h"
#include "trataString.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

No *escreveTexto(No *inicio, char pathSaida[], char comando[], char corb[], char corp[], int j, int k, float x, float y, int retorno){
    FILE *qrySaida = NULL;
    qrySaida = fopen(pathSaida, "a+");
    if (!qrySaida){
        printf("\nErro inesperado! Nao foi possivel abrir o arquivo. Arquivo inexistente.");
        exit(1);
    }

    char *frase = NULL;
    frase = (char *)malloc(50 * sizeof(char));

    fprintf(qrySaida, "COMANDO: %s    |   ", comando);

    if(strcmp(comando, "o?") == 0){
        fprintf(qrySaida, "\n\tPARAMETROS: J->%d  K->%d\n", j, k);
        inicio = retornaInfo(inicio, qrySaida, comando, j, k);
        if (retorno == 1){
            frase = "se sobrepoem!";
        }
        else if (retorno == 0){
            frase = "nao se sobrepoem!";
        }
        else{
            frase = "Impossivel verificar sobreposição em tipo texto!";
        }
        fprintf(qrySaida, "%s", frase);
        fprintf(qrySaida,"\n\t---------------------------------------------------\n");
    }

    else if (strcmp(comando, "i?") == 0){
        fprintf(qrySaida, "\n\tPARAMETROS: J->%d     X->%f     Y->%f\n", j, x, y);
        inicio = retornaInfo(inicio, qrySaida, comando, j, k);
        if (retorno == 1){
            strcpy(frase, "O ponto x,y esta dentro de j!");
        }
        else if (retorno == 0){
            strcpy(frase, "O ponto x,y esta fora de j!");
        }
        else{
            strcpy(frase, "Impossivel verificar ponto em tipo texto!");
        }
        fprintf(qrySaida, "%s", frase);
        fprintf(qrySaida, "\n\t---------------------------------------------------\n");
    }

    else if (strcmp(comando, "pnt") == 0){
        fprintf(qrySaida, "PARAMETROS: J->%d  Cor da borda->%s  Cor preenchimento->%s\n", j, corb, corp);
        //retorno
        fprintf(qrySaida, "\n\t---------------------------------------------------\n");
    }

    else if (strcmp(comando, "pnt*") == 0){
        fprintf(qrySaida, "PARAMETROS: J->%d  K->%d   Cor da borda->%s  Cor preenchimento->%s\n", j, k, corb, corp);
        //retorno
        fprintf(qrySaida, "\n\t---------------------------------------------------\n");
    }

    else if (strcmp(comando, "delf") == 0){
        fprintf(qrySaida, "PARAMETROS: J->%d\n", j);
        inicio = retornaInfo(inicio, qrySaida, comando, j, k);
        fprintf(qrySaida, "\n\t---------------------------------------------------\n");
    }

    else if (strcmp(comando, "delf*") == 0){
        fprintf(qrySaida, "PARAMETROS: J->%d  K->%d\n", j, k);
        //retorno
        fprintf(qrySaida, "\n\t---------------------------------------------------\n");
    }

    free(frase);

    return inicio;
}

No *retornaInfo(No *inicio, FILE *qrySaida, char comando[], int j, int k){
    char tipoJ[10], tipoK[10], tipoI[10];

    if(strcmp(comando, "o?") == 0){
        No *auxJ = buscaElemento(inicio, j);
        No *auxK = buscaElemento(inicio, k);
        if(auxJ->tipo == 'c'){
            strcpy(tipoJ, "CIRCULO");
        }
        else if(auxJ->tipo == 'r'){
            strcpy(tipoJ, "RETANGULO");
        }

        if(auxK->tipo == 'c'){
            strcpy(tipoK, "CIRCULO");
        }
        else if(auxK->tipo == 'r'){
            strcpy(tipoK, "RETANGULO");
        }
        fprintf(qrySaida, "\n\tJ-> FORMA: %s K-> FORMA: %s ", tipoJ, tipoK);
    }

    else if(strcmp(comando, "i?") == 0){
        No *auxJ = buscaElemento(inicio, j);
        if (auxJ->tipo == 'c'){
            strcpy(tipoJ, "CIRCULO");
        }
        else if (auxJ->tipo == 'r'){
            strcpy(tipoJ, "RETANGULO");
        }
        fprintf(qrySaida, "\n\tJ-> FORMA: %s\n", tipoJ);
    }
    
    else if(strcmp(comando, "pnt") == 0){
        No *auxJ = buscaElemento(inicio, j);
        if (auxJ->tipo == 'c'){
            strcpy(tipoJ, "CIRCULO");
            fprintf(qrySaida, "\n\tJ-> FORMA: %s   X: %f   Y: %f\n", tipoJ, auxJ->fig->crl.x, auxJ->fig->crl.y);
        }
        else if (auxJ->tipo == 'r'){
            strcpy(tipoJ, "RETANGULO");
            fprintf(qrySaida, "\n\tJ-> FORMA: %s   X: %f   Y: %f\n", tipoJ, auxJ->fig->ret.x, auxJ->fig->ret.y);
        }
        else if(auxJ->tipo == 't'){
            strcpy(tipoJ, "TEXTO");
            fprintf(qrySaida, "\n\tJ-> FORMA: %s   X: %f   Y: %f\n", tipoJ, auxJ->fig->texto.x, auxJ->fig->texto.y);
        }

    }

    else if(strcmp(comando, "pnt*") == 0){
        No *auxJ = buscaElemento(inicio, j);
        if (auxJ == NULL){
            printf("\nNao foi possivel encontrar o elemento. ID: %d!", j);
        }
        No *auxK = buscaElemento(inicio, k);
        if (auxK == NULL){
            printf("\nNao foi possivel encontrar o elemento. ID: %d!", k);
        }

        for(int i = MIN(j, k); i < MAX(j, k); i++){
            No *auxI = buscaElemento(inicio, i);
            if (auxI == NULL){
                printf("\nNao foi possivel encontrar o elemento. ID: %d!", i);
            }
            if (auxI->tipo == 'c'){
                strcpy(tipoI, "CIRCULO");
                fprintf(qrySaida, "\n\tJ-> FORMA: %s   X: %f   Y: %f\n", tipoI, auxI->fig->crl.x, auxI->fig->crl.y);
            }
            else if (auxI->tipo == 'r'){
                strcpy(tipoI, "RETANGULO");
                fprintf(qrySaida, "\n\tJ-> FORMA: %s   X: %f   Y: %f\n", tipoI, auxI->fig->ret.x, auxI->fig->ret.y);
            }
            else if (auxI->tipo == 't'){
                strcpy(tipoI, "TEXTO");
                fprintf(qrySaida, "\n\tJ-> FORMA: %s   X: %f   Y: %f\n", tipoI, auxI->fig->texto.x, auxI->fig->texto.y);
            }
        }
    }

    else if(strcmp(comando, "delf") == 0){
        No *auxJ = buscaElemento(inicio, j);
        if (auxJ->tipo == 'c'){
            strcpy(tipoJ, "CIRCULO");
            fprintf(qrySaida, "\n\tJ-> FORMA: %s   Raio: %f   X: %f   Y: %f   Cor da Borda: %s   Cor de Preenchimento: %s", tipoJ, auxJ->fig->crl.r, auxJ->fig->crl.x, auxJ->fig->crl.y, auxJ->fig->crl.corb, auxJ->fig->crl.corp);
        }
        else if (auxJ->tipo == 'r'){
            strcpy(tipoJ, "RETANGULO");
            fprintf(qrySaida, "\n\tJ-> FORMA: %s   X: %f   Y: %f   ALTURA: %f   LARGURA: %f   Cor da Borda: %s   Cor de Preenchimento: %s", tipoJ, auxJ->fig->ret.x, auxJ->fig->ret.y, auxJ->fig->ret.h, auxJ->fig->ret.w, auxJ->fig->ret.corb, auxJ->fig->ret.corp);
        }
        else if (auxJ->tipo == 't'){
            strcpy(tipoJ, "TEXTO");
            fprintf(qrySaida, "\n\tJ-> FORMA: %s   TEXTO: %s   X: %f   Y: %f   Cor da Borda: %s   Cor de Preenchimento: %s", tipoJ, auxJ->fig->texto.texto, auxJ->fig->texto.x, auxJ->fig->texto.y, auxJ->fig->texto.corb, auxJ->fig->texto.corp);
        }
    }
    
    else if(strcmp(comando, "delf*") == 0){
        No *auxJ = buscaElemento(inicio, j);
        if (auxJ == NULL){
            printf("\nNao foi possivel encontrar o elemento. ID: %d!", j);
        }
        No *auxK = buscaElemento(inicio, k);
        if (auxK == NULL){
            printf("\nNao foi possivel encontrar o elemento. ID: %d!", k);
        }

        for (int i = MIN(j, k); i < MAX(j, k); i++){
            No *auxI = buscaElemento(inicio, i);
            if (auxI == NULL){
                printf("\nNao foi possivel encontrar o elemento. ID: %d!", i);
            }
            if (auxJ->tipo == 'c'){
                strcpy(tipoI, "CIRCULO");
                fprintf(qrySaida, "\n\tJ-> FORMA: %s   Raio: %f   X: %f   Y: %f   Cor da Borda: %s   Cor de Preenchimento: %s", tipoJ, auxI->fig->crl.r, auxI->fig->crl.x, auxI->fig->crl.y, auxI->fig->crl.corb, auxI->fig->crl.corp);
            }
            else if (auxJ->tipo == 'r'){
                strcpy(tipoI, "RETANGULO");
                fprintf(qrySaida, "\n\tJ-> FORMA: %s   X: %f   Y: %f   ALTURA: %f   LARGURA: %f   Cor da Borda: %s   Cor de Preenchimento: %s", tipoI, auxI->fig->ret.x, auxI->fig->ret.y, auxI->fig->ret.h, auxI->fig->ret.w, auxI->fig->ret.corb, auxI->fig->ret.corp);
            }
            else if (auxJ->tipo == 't'){
                strcpy(tipoI, "TEXTO");
                fprintf(qrySaida, "\n\tJ-> FORMA: %s   TEXTO: %s   X: %f   Y: %f   Cor da Borda: %s   Cor de Preenchimento: %s", tipoI, auxI->fig->texto.texto, auxI->fig->texto.x, auxI->fig->texto.y, auxI->fig->texto.corb, auxI->fig->texto.corp);
            }
        }
    }

    return inicio;
}
