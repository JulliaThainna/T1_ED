#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lista.h"
#include "leitura.h"
#include "consulta.h"
#include "svg.h"

int main(int argc, char *argv[]){

    No *lista = NULL;

    char *dirEntrada = NULL;
    char *arqGeo = NULL;
    char *arqQry = NULL;
    char *dirSaida = NULL;
    char *pathEntrada = NULL;
    char *nomeGeo = NULL;
    char *pathSaida = NULL;
    char *nomeSvg = NULL;
    char *nomeQry = NULL;

    printf("\n\t---------------------------------------------------\n");
    for(int i = 1; argc > i; i++){    
        if(strcmp(argv[i], "-e") == 0){     
            i++;
            printf("\n\t\t> Diretorio de Entrada: %s", argv[i]);
            if(strcmp(argv[i], "-f") == 0){ 
                printf("\nDiretorio nao inserido!");
                exit(1);
            }
            dirEntrada = (char *)malloc((strlen(argv[i]) + 1) * sizeof(char)); 
            if(dirEntrada == NULL){
                printf("\nErro inesperado! Memoria insuficiente para alocar o nome do diretorio de entrada.");
                exit(1);
            }
            strcpy(dirEntrada, argv[i]); 
        }

        else if(strcmp(argv[i], "-f") == 0){        
            i++; 
            printf("\n\t\t> Arquivo .geo: %s", argv[i]);
            if (strcmp(argv[i], "-q") == 0){
                printf("\nArquivo nao inserido!");
                continue;
            }
            arqGeo = (char *)malloc((strlen(argv[i]) + 1) * sizeof(char));
            if(arqGeo == NULL){
                printf("\nErro inesperado! Memoria insuficiente para alocar o nome do arquivo .geo.");
                exit(1);
            }
            strcpy(arqGeo, argv[i]);
        }

        else if(strcmp(argv[i], "-q") == 0){       
            i++;
            printf("\n\t\t> Arquivo .qry: %s", argv[i]);
            if(strcmp(argv[i], "-o") == 0){
                printf("\nArquivo nao inserido!");
                exit(1);
            }
            arqQry = (char *)malloc((strlen(argv[i]) + 1) * sizeof(char));
            if(arqQry == NULL){
                printf("\nErro inesperado! Memoria insuficiente para alocar o nome do arquivo .qry.");
                exit(1);
            }
            strcpy(arqQry, argv[i]);
        }

        else if (strcmp(argv[i], "-o") == 0){     
            i++; 
            printf("\n\t\t> Diretorio de Saida: %s", argv[i]);
            if(argv[i] == NULL){
                printf("\nDiretorio nao inserido!");
                continue;
            }
            dirSaida = (char *)malloc((strlen(argv[i]) + 1) * sizeof(char));
            if(dirSaida == NULL){
                printf("\nErro inesperado! Memoria insuficiente para alocar o nome do diretorio de saida.");
                exit(1);
            }
            strcpy(dirSaida, argv[i]);
        }
    }
    if(arqGeo == NULL || dirSaida == NULL){ 
        printf("\nParametros essenciais nao foram inseridos!");
        exit(1);
    }
    printf("\n\t---------------------------------------------------\n");

    lista = abreGeo(dirEntrada, arqGeo, pathEntrada, nomeGeo, lista);
    printf("\n\t---------------------------------------------------\n");
    //lista = desenhaSvg(lista, arqGeo, dirSaida, pathSaida, nomeSvg);
    printf("\n\t---------------------------------------------------\n");
    //lista = imprimeLista(lista);
    printf("\n\t---------------------------------------------------\n");
    lista = abreQry(lista, dirEntrada, arqQry, pathEntrada, nomeQry);
    printf("\n\t---------------------------------------------------\n");

    //Libera o espaço alocado para as variáveis
    lista = deletaLista(lista);
    free(dirEntrada);
    free(arqGeo);
    free(arqQry);
    free(dirSaida);
    free(pathEntrada);
    free(nomeGeo);
    free(pathSaida);
    free(nomeSvg);
    printf("\n\t\tMemoria desalocada com sucesso!");
    printf("\n\t\tPROCESSO CONCLUIDO COM SUCESSO!\n");
    return 0;
}