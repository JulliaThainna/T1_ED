#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "txt.h"
#include "lista.h"
#include "trataString.h"


void escreveTexto(No *inicio, FILE *qry, char comando[], char corb[], char corp[], int j, int k, float x, float y, int retorno){
    char *frase = NULL;

    fprintf(qry, "COMANDO: %s    |   ", comando);
    frase = (char *)malloc(50 * sizeof(char));

    if(strcmp(comando, "o?") == 0){
        fprintf(qry, "\n\tPARAMETROS: J->%d  K->%d\n", j, k);
        inicio = retornaInfo(inicio, qry, comando, j, k);
        if (retorno == 1){
            frase = "se sobrepoem!";
        }
        else if (retorno == 0){
            frase = "nao se sobrepoem!";
        }
        else{
            frase = "Impossivel verificar sobreposição em tipo texto!";
        }
        fprintf(qry, "%s", frase);
        fprintf(qry,"\n\t---------------------------------------------------\n");
    }

    else if (strcmp(comando, "i?") == 0){
        fprintf(qry, "\n\tPARAMETROS: J->%d     X->%f     Y->%f\n", j, x, y);
        inicio = retornaInfo(inicio, qry, comando, j, k);
        if (retorno == 1){
            frase = "O ponto x,y esta dentro de j!";
        }
        else if (retorno == 0){
            frase = "O ponto x,y esta fora de j!";
        }
        else{
            frase = "Impossivel verificar ponto em tipo texto!";
        }
        fprintf(qry, "%s", frase);
        fprintf(qry, "\n\t---------------------------------------------------\n");
    }

    else if (strcmp(comando, "pnt") == 0){
        fprintf(qry, "PARAMETROS: J->%d  Cor da borda->%s  Cor preenchimento->%s\n", j, corb, corp);
        //retorno
        fprintf(qry, "\n\t---------------------------------------------------\n");
    }

    else if (strcmp(comando, "pnt*") == 0){
        fprintf(qry, "PARAMETROS: J->%d  K->%d   Cor da borda->%s  Cor preenchimento->%s\n", j, k, corb, corp);
        //retorno
        fprintf(qry, "\n\t---------------------------------------------------\n");
    }

    else if (strcmp(comando, "delf") == 0){
        fprintf(qry, "PARAMETROS: J->%d\n", j);
        inicio = retornaInfo(inicio, qry, comando, j, k);
        fprintf(qry, "\n\t---------------------------------------------------\n");
    }

    else if (strcmp(comando, "delf*") == 0){
        fprintf(qry, "PARAMETROS: J->%d  K->%d\n", j, k);
        //retorno
        fprintf(qry, "\n\t---------------------------------------------------\n");
    }

    fclose(qry);
    free(frase);
}

No *retornaInfo(No *inicio, FILE *qry, char comando[], int j, int k){
    char tipoJ[10], tipoK[10];

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
        fprintf(qry, "\n\tJ-> FORMA: %s K-> FORMA: %s ", tipoJ, tipoK);
    }

    else if(strcmp(comando, "i?") == 0){
        No *auxJ = buscaElemento(inicio, j);
        if (auxJ->tipo == 'c'){
            strcpy(tipoJ, "CIRCULO");
        }
        else if (auxJ->tipo == 'r'){
            strcpy(tipoJ, "RETANGULO");
        }
        fprintf(qry, "\n\tJ-> FORMA: %s\n", tipoJ);
    }
    
    /*else if(strcmp(comando, "pnt") == 0){
        No *auxJ = buscaElemento(inicio, j);      
    }

    else if(strcmp(comando, "pnt*") == 0){
        No *auxJ = buscaElemento(inicio, j);
        No *auxK = buscaElemento(inicio, k);
    }*/
    
    else if(strcmp(comando, "delf") == 0){
        No *auxJ = buscaElemento(inicio, j);
        if (auxJ->tipo == 'c'){
            strcpy(tipoJ, "CIRCULO");
            fprintf(qry, "\n\tJ-> FORMA: %s   Raio: %f   X: %f   Y: %f   Cor da Borda: %s   Cor de Preenchimento: %s", tipoJ, auxJ->fig->crl.r, auxJ->fig->crl.x, auxJ->fig->crl.y, auxJ->fig->crl.corb, auxJ->fig->crl.corp);
        }
        else if (auxJ->tipo == 'r'){
            strcpy(tipoJ, "RETANGULO");
            fprintf(qry, "\n\tJ-> FORMA: %s   X: %f   Y: %f   ALTURA: %f   LARGURA: %f   Cor da Borda: %s   Cor de Preenchimento: %s", tipoJ, auxJ->fig->ret.x, auxJ->fig->ret.y, auxJ->fig->ret.h, auxJ->fig->ret.w, auxJ->fig->ret.corb, auxJ->fig->ret.corp);
        }
        else if (auxJ->tipo == 't'){
            strcpy(tipoJ, "TEXTO");
            fprintf(qry, "\n\tJ-> FORMA: %s   TEXTO: %s   X: %f   Y: %f   Cor da Borda: %s   Cor de Preenchimento: %s", tipoJ, auxJ->fig->texto.texto, auxJ->fig->texto.x, auxJ->fig->texto.y, auxJ->fig->texto.corb, auxJ->fig->texto.corp);
        }
    }
    
    /*else if(strcmp(comando, "delf*") == 0){
        No *auxJ = buscaElemento(inicio, j);
        No *auxK = buscaElemento(inicio, k);
        if (auxJ->tipo == 'c'){
            strcpy(tipoJ, "CIRCULO");
            fprintf(qry, "\n\tJ-> FORMA: %s   Raio: %f   X: %f   Y: %f   Cor da Borda: %s   Cor de Preenchimento: %s", tipoJ, auxJ->fig->crl.r, auxJ->fig->crl.x, auxJ->fig->crl.y, auxJ->fig->crl.corb, auxJ->fig->crl.corp);
        }
        else if (auxJ->tipo == 'r')
        {
            strcpy(tipoJ, "RETANGULO");
            fprintf(qry, "\n\tJ-> FORMA: %s   X: %f   Y: %f   ALTURA: %f   LARGURA: %f   Cor da Borda: %s   Cor de Preenchimento: %s", tipoJ, auxJ->fig->ret.x, auxJ->fig->ret.y, auxJ->fig->ret.h, auxJ->fig->ret.w, auxJ->fig->ret.corb, auxJ->fig->ret.corp);
        }
        else if (auxJ->tipo == 't')
        {
            strcpy(tipoJ, "TEXTO");
            fprintf(qry, "\n\tJ-> FORMA: %s   TEXTO: %s   X: %f   Y: %f   Cor da Borda: %s   Cor de Preenchimento: %s", tipoJ, auxJ->fig->texto.texto, auxJ->fig->texto.x, auxJ->fig->texto.y, auxJ->fig->texto.corb, auxJ->fig->texto.corp);
        }
    }*/

    return inicio;
}
