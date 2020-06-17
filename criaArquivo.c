#include <stdio.h>
#include <stdlib.h>

#include "trataString.h"

char *criaArqSaida(char arqGeo[], char dirSaida[], char tipoArqE[], char tipoArqS[]){
    FILE *arq = NULL;
    char *pathSaida = NULL;

    printf("\n\t\tCRIANDO ARQUIVO .%s . . . ", tipoArqS);
    pathSaida = trataStringTipo(dirSaida, arqGeo, tipoArqE, tipoArqS); 
    printf("\n\t> Arquivo .%s: %s", tipoArqS, pathSaida);
    arq = fopen(pathSaida, "w");
    if (arq == NULL){
        printf("\nErro inesperado! Nao foi possivel criar arquivo .%s.",tipoArqS);
        exit(1);
    }
    printf("\n\tArquivo .%s criado com sucesso!", tipoArqS);
    printf("\n\tEXPORTANDO ELEMENTOS PARA O ARQUIVO .%s . . . ", tipoArqS);
    fclose(arq);
    return pathSaida;
}