#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trataString.h"
#include "lista.h"


char *trataStringCaminho(char dirEntrada[], char arqE[]){
    char *nomeArqE = NULL;
    char *pathEntrada = NULL;

    if(dirEntrada[strlen(dirEntrada) - 1] == '/' && arqE[0] == '/'){
        pathEntrada = (char *)malloc(((strlen(dirEntrada) + strlen(arqE)) + 1) * sizeof(char));
        nomeArqE = (char *)malloc(strlen(arqE) + 1);
        if(pathEntrada == NULL || nomeArqE == NULL){
            printf("\nErro inesperado! Memoria insuficiente para salvar o caminho do arquivo .geo.");
            printf("\n---------------------------------------------------\n");
            exit(1);
        }

        strncpy(pathEntrada, dirEntrada, strlen(dirEntrada) + 1);
        memcpy(nomeArqE, arqE + 1, strlen(arqE));
        strcat(pathEntrada, nomeArqE);
    }

    else if(dirEntrada[strlen(dirEntrada) - 1] != '/' && arqE[0] != '/' && arqE[0] != '.'){
        pathEntrada = (char *)malloc(((strlen(dirEntrada) + strlen(arqE)) + 3) * sizeof(char));
        if(pathEntrada == NULL){
            printf("\nErro inesperado! Memoria insuficiente para salvar o caminho do arquivo .geo.");
            printf("\n---------------------------------------------------\n");
            exit(1);
        }

        strncpy(pathEntrada, dirEntrada, strlen(dirEntrada) + 1);
        strcat(pathEntrada, "/");
        strcat(pathEntrada, arqE);
    }

    else if((dirEntrada[strlen(dirEntrada) - 1] != '/' && arqE[0] == '/') || (dirEntrada[strlen(dirEntrada) - 1] == '/' && arqE[0] != '/' && arqE[0] != '.')){
        pathEntrada = (char *)malloc((strlen(dirEntrada) + strlen(arqE) + 2) * sizeof(char));
        if(pathEntrada == NULL){
            printf("\nErro inesperado! Memoria insuficiente para salvar o caminho do arquivo .geo.");
            printf("\n---------------------------------------------------\n");
            exit(1);
        }

        strcpy(pathEntrada, dirEntrada);
        strcat(pathEntrada, arqE);
    }

    else if(dirEntrada[strlen(dirEntrada) - 1] == '/' && arqE[0] == '.'){
        //printf("%ld", strlen(arqE));
        pathEntrada = (char *)malloc((strlen(dirEntrada) + strlen(arqE)) * sizeof(char));
        nomeArqE = (char *)malloc(strlen(arqE) + 1);
        if(pathEntrada == NULL || nomeArqE == NULL){
            printf("\nErro inesperado! Memoria insuficiente para salvar o caminho do arquivo .geo.");
            printf("\n---------------------------------------------------\n");
            exit(1);
        }

        strcpy(pathEntrada, dirEntrada);
        memcpy(nomeArqE, arqE + 2, strlen(arqE) - 1);
        strcat(pathEntrada, nomeArqE);
    }

    else if(dirEntrada[strlen(dirEntrada) - 1] != '/' && arqE[0] == '.'){
        pathEntrada = (char *)malloc(((strlen(dirEntrada) + strlen(arqE)) + 1) * sizeof(char));
        nomeArqE = (char *)malloc(strlen(arqE) + 1);
        if(pathEntrada == NULL || nomeArqE == NULL){
            printf("\nErro inesperado! Memoria insuficiente para salvar o caminho do arquivo .geo.");
            printf("\n---------------------------------------------------\n");
            exit(1);
        }

        strcpy(pathEntrada, dirEntrada);
        memcpy(nomeArqE, arqE + 1, strlen(arqE));
        strcat(pathEntrada, nomeArqE);
    } 
    free(nomeArqE);

    return pathEntrada;
}

char *trataStringTipo(char dirSaida[], char arqGeo[], char tipoArqE[], char tipoArqS[]){
    char *nomeSvg = NULL;
    char *pathSaida = NULL;

    if(dirSaida[strlen(dirSaida) - 1] == '/' && arqGeo[0] == '/'){ // -o geoFiles/ -f /hino-01.geo
        if(strcmp(tipoArqE, "geo") == 0){
            pathSaida = (char *)malloc(((strlen(dirSaida) + strlen(arqGeo)) + 1) * sizeof(char));
        }
        else{
            pathSaida = (char *)malloc(((strlen(dirSaida) + strlen(arqGeo)) + 3) * sizeof(char));
        }

        nomeSvg = (char *)malloc(strlen(arqGeo) + 1);
        if(pathSaida == NULL || nomeSvg == NULL){
            printf("\nErro inesperado! Memoria insuficiente para salvar o caminho do arquivo .geo.");
            printf("\n---------------------------------------------------\n");
            exit(1);
        }

        strcpy(pathSaida, dirSaida);
        strcpy(nomeSvg, arqGeo);
        pathSaida[strlen(pathSaida) - 1] = '\0';
        strncat(pathSaida, strrchr(nomeSvg, '/'), strlen(strrchr(nomeSvg, '/')) - 4);
    }

    else if(dirSaida[strlen(dirSaida) - 1] != '/' && arqGeo[0] != '/' && arqGeo[0] != '.'){
        if(strcmp(tipoArqE, "geo") == 0){
            pathSaida = (char *)malloc(((strlen(dirSaida) + strlen(arqGeo)) + 3) * sizeof(char));
        }
        else{
            pathSaida = (char *)malloc(((strlen(dirSaida) + strlen(arqGeo)) + 5) * sizeof(char));
        }

        nomeSvg = (char *)malloc(strlen(arqGeo) + 1);
        if(pathSaida == NULL || nomeSvg == NULL){
            printf("\nErro inesperado! Memoria insuficiente para salvar o caminho do arquivo .geo.");
            printf("\n---------------------------------------------------\n");
            exit(1);
        }

        strcpy(pathSaida, dirSaida);
        strcpy(nomeSvg, arqGeo);

        if(strrchr(nomeSvg, '/') == NULL){
            strcat(pathSaida, "/");
            strncat(pathSaida, arqGeo, strlen(arqGeo) - 4);
        }
        else{
            strncat(pathSaida, strrchr(nomeSvg, '/'), strlen(strrchr(nomeSvg, '/')) - 4);
        }
    } 
    
    else if((dirSaida[strlen(dirSaida) - 1] != '/' && arqGeo[0] == '/') || (dirSaida[strlen(dirSaida) - 1] == '/' && arqGeo[0] != '/' && arqGeo[0] != '.')){
        if(strcmp(tipoArqE, "geo") == 0){
            pathSaida = (char *)malloc((strlen(dirSaida) + strlen(arqGeo) + 2) * sizeof(char));
        }
        else{
            pathSaida = (char *)malloc((strlen(dirSaida) + strlen(arqGeo) + 4) * sizeof(char));
        }

        nomeSvg = (char *)malloc(strlen(arqGeo) + 1);
        if(pathSaida == NULL || nomeSvg == NULL){
            printf("\nErro inesperado! Memoria insuficiente para salvar o caminho do arquivo .geo.");
            printf("\n---------------------------------------------------\n");
            exit(1);
        }

        strcpy(pathSaida, dirSaida);
        strcpy(nomeSvg, arqGeo);

        if(strrchr(nomeSvg, '/') == NULL){ //no caso de: /arquivo.geo
            strncat(pathSaida, nomeSvg, strlen(nomeSvg) - 4);
        }
        else{ //no caso de: pasta/pastinha/arquivo.geo
            if(dirSaida[strlen(dirSaida) - 1] == '/'){
                pathSaida[strlen(pathSaida) - 1] = '\0';
            }
            strncat(pathSaida, strrchr(nomeSvg, '/'), strlen(strrchr(nomeSvg, '/')) - 4);
        }
    }

    else if(dirSaida[strlen(dirSaida) - 1] == '/' && arqGeo[0] == '.'){
        //printf("%ld", strlen(arqGeo));
        if(strcmp(tipoArqE, "geo") == 0){
            pathSaida = (char *)malloc((strlen(dirSaida) + strlen(arqGeo)) * sizeof(char));
        }
        else{
            pathSaida = (char *)malloc((strlen(dirSaida) + strlen(arqGeo) + 2) * sizeof(char));
        }

        nomeSvg = (char *)malloc(strlen(arqGeo) + 1);
        if(pathSaida == NULL || nomeSvg == NULL){
            printf("\nErro inesperado! Memoria insuficiente para salvar o caminho do arquivo .geo.");
            printf("\n---------------------------------------------------\n");
            exit(1);
        }

        strcpy(pathSaida, dirSaida);
        strcpy(nomeSvg, arqGeo);
        memcpy(nomeSvg, arqGeo + 2, strlen(arqGeo) - 1);

        if(strrchr(nomeSvg, '/') == NULL){
            strncat(pathSaida, nomeSvg, strlen(nomeSvg) - 4);
        }
        else{
            pathSaida[strlen(pathSaida) - 1] = '\0';
            strncat(pathSaida, strrchr(nomeSvg, '/'), strlen(strrchr(nomeSvg, '/')) - 4);
        }
    }
    
    else if(dirSaida[strlen(dirSaida) - 1] != '/' && arqGeo[0] == '.'){
        if(strcmp(tipoArqE, "geo") == 0){
            pathSaida = (char *)malloc(((strlen(dirSaida) + strlen(arqGeo)) + 1) * sizeof(char));
        }
        else{
            pathSaida = (char *)malloc(((strlen(dirSaida) + strlen(arqGeo)) + 3) * sizeof(char));
        }

        nomeSvg = (char *)malloc(strlen(arqGeo) + 1);
        if(pathSaida == NULL || nomeSvg == NULL){
            printf("\nErro inesperado! Memoria insuficiente para salvar o caminho do arquivo .geo.");
            printf("\n---------------------------------------------------\n");
            exit(1);
        }

        strcpy(pathSaida, dirSaida);
        memcpy(nomeSvg, arqGeo + 1, strlen(arqGeo)); //aqui nao poderia ser o arqGeo
        strncat(pathSaida, strrchr(nomeSvg, '/'), strlen(strrchr(nomeSvg, '/')) - 4);
    }

    if(strcmp(tipoArqE, "geo") == 0){
        strcat(pathSaida, ".svg");
    }
    else{
        if(strcmp(tipoArqS, "svg") == 0){
            strcat(pathSaida, "-q.svg");
        }
        else{
            strcat(pathSaida, "-q.txt");
        }
    }
    free(nomeSvg);

    return pathSaida;
}
