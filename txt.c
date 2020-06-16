#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "txt.h"
#include "lista.h"
#include "trataString.h"

void escreveTexto(char pathSaida[], char comando[], char corb[], char corp[], int j, 
                int k, float x, float y, bool retorno){
    FILE *arqTxt = NULL;

    arqTxt = fopen(pathSaida, "a+");
    if (arqTxt == NULL){
        printf("\nErro inesperado! Nao foi possivel criar arquivo .txt.");
        exit(1);
    }

    fprintf(arqTxt, "COMANDO: %s    |   ", comando);
    if(strcmp(comando, "o?") == 0){
        fprintf(arqTxt, "PARAMETROS: J->%d  K->%d\n", j, k);
        //retorno
    }
    else if (strcmp(comando, "i?") == 0){
        fprintf(arqTxt, "PARAMETROS: J->%d     X->%f     Y->%f\n", j, x, y);
        //retorno
    }
    else if (strcmp(comando, "pnt") == 0){
        fprintf(arqTxt, "PARAMETROS: J->%d  Cor da borda->%s  Cor preenchimento->%s\n", j, corb, corp);
        //retorno
    }
    else if (strcmp(comando, "pnt*") == 0){
        fprintf(arqTxt, "PARAMETROS: J->%d  K->%d   Cor da borda->%s  Cor preenchimento->%s\n", j, k, corb, corp);
        //retorno
    }
    else if (strcmp(comando, "delf") == 0){
        fprintf(arqTxt, "PARAMETROS: J->%d\n", j);
        //retorno
    }
    else if (strcmp(comando, "delf*") == 0){
        fprintf(arqTxt, "PARAMETROS: J->%d  K->%d\n", j, k);
        //retorno
    }
}