#include <stdio.h>
#include <stdlib.h>

#include "trataString.h"


char *criaArqSaida(char arqGeo[], char dirSaida[], char tipoArqE[], char tipoArqS[]){
    FILE *arq = NULL;
    char *pathSaida = NULL;

    printf("\n\t\tCRIANDO ARQUIVO .%s . . . ", tipoArqS);
    pathSaida = trataStringTipo(dirSaida, arqGeo, tipoArqE, tipoArqS); 
    printf("\n\t\t > Arquivo .%s: %s", tipoArqS, pathSaida);
    arq = fopen(pathSaida, "w");
    if(arq == NULL){
        printf("\nErro inesperado! Nao foi possivel criar arquivo .%s.",tipoArqS);
        printf("\n---------------------------------------------------\n");
        exit(1);
    }  
    printf("\n\tArquivo .%s criado com sucesso!", tipoArqS);
    fclose(arq);

    return pathSaida;
}
