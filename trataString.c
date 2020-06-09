#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trataString.h"
#include "lista.h"

char *trataStringGeo(char dirEntrada[], char arqGeo[], char pathEntrada[], char nomeGeo[]){
    if(dirEntrada[strlen(dirEntrada) - 1] == '/' && arqGeo[0] == '/'){
        //printf("\n%d", (strlen(dirEntrada) + strlen(arqGeo)) - 1);
        pathEntrada = (char *)malloc(((strlen(dirEntrada) + strlen(arqGeo)) + 1) * sizeof(char));
        if (pathEntrada == NULL){
            printf("Erro inesperado! Memoria insuficiente para salvar o caminho do arquivo .geo.");
            exit(1);
        }
        strncpy(pathEntrada, dirEntrada, strlen(dirEntrada) + 1);
        nomeGeo = (char *)malloc(strlen(arqGeo) + 1);
        if (nomeGeo == NULL)
        {
            printf("Erro inesperado! Memoria insuficiente para salvar o caminho do arquivo .geo.");
            exit(1);
        }
        memcpy(nomeGeo, arqGeo + 1, strlen(arqGeo));
        strcat(pathEntrada, nomeGeo);
    }
    else if(dirEntrada[strlen(dirEntrada) - 1] != '/' && arqGeo[0] != '/' && arqGeo[0] != '.'){
        pathEntrada = (char *)malloc(((strlen(dirEntrada) + strlen(arqGeo)) + 3) * sizeof(char));
        if (pathEntrada == NULL)
        {
            printf("Erro inesperado! Memoria insuficiente para salvar o caminho do arquivo .geo.");
            exit(1);
        }
        strncpy(pathEntrada, dirEntrada, strlen(dirEntrada) + 1);
        strcat(pathEntrada, "/");
        strcat(pathEntrada, arqGeo);
    }
    else if((dirEntrada[strlen(dirEntrada) - 1] != '/' && arqGeo[0] == '/') || (dirEntrada[strlen(dirEntrada) - 1] == '/' && arqGeo[0] != '/' && arqGeo[0] != '.')){
        pathEntrada = (char *)malloc((strlen(dirEntrada) + strlen(arqGeo) + 2) * sizeof(char));
        if (pathEntrada == NULL)
        {
            printf("Erro inesperado! Memoria insuficiente para salvar o caminho do arquivo .geo.");
            exit(1);
        }
        strcpy(pathEntrada, dirEntrada);
        strcat(pathEntrada, arqGeo);
    }
    else if(dirEntrada[strlen(dirEntrada) - 1] == '/' && arqGeo[0] == '.'){
        //printf("%ld", strlen(arqGeo));
        pathEntrada = (char *)malloc((strlen(dirEntrada) + strlen(arqGeo)) * sizeof(char));
        if (pathEntrada == NULL)
        {
            printf("Erro inesperado! Memoria insuficiente para salvar o caminho do arquivo .geo.");
            exit(1);
        }
        strcpy(pathEntrada, dirEntrada);
        nomeGeo = (char *)malloc(strlen(arqGeo) + 1);
        if (nomeGeo == NULL)
        {
            printf("Erro inesperado! Memoria insuficiente para salvar o caminho do arquivo .geo.");
            exit(1);
        }
        memcpy(nomeGeo, arqGeo + 2, strlen(arqGeo) - 1);
        //printf("%ld",strlen(arqGeo));
        strcat(pathEntrada, nomeGeo);
    }
    else if(dirEntrada[strlen(dirEntrada) - 1] != '/' && arqGeo[0] == '.'){
        pathEntrada = (char *)malloc(((strlen(dirEntrada) + strlen(arqGeo)) + 1) * sizeof(char));
        if (pathEntrada == NULL)
        {
            printf("Erro inesperado! Memoria insuficiente para salvar o caminho do arquivo .geo.");
            exit(1);
        }
        strcpy(pathEntrada, dirEntrada);
        nomeGeo = (char *)malloc(strlen(arqGeo) + 1);
        if (nomeGeo == NULL)
        {
            printf("Erro inesperado! Memoria insuficiente para salvar o caminho do arquivo .geo.");
            exit(1);
        }
        memcpy(nomeGeo, arqGeo + 1, strlen(arqGeo));
        strcat(pathEntrada, nomeGeo);
    }
    free(nomeGeo);
    return pathEntrada;
}

char *trataStringSvg(char dirSaida[], char arqGeo[], char pathSaida[], char nomeSvg[]){
    if (dirSaida[strlen(dirSaida) - 1] == '/' && arqGeo[0] == '/'){
        //printf("\n%d", (strlen(dirSaida) + strlen(arqGeo)) - 1);
        pathSaida = (char *)malloc(((strlen(dirSaida) + strlen(arqGeo)) + 1) * sizeof(char));
        if (pathSaida == NULL){
            printf("Erro inesperado! Memoria insuficiente para salvar o caminho do arquivo .geo.");
            exit(1);
        }
        strcpy(pathSaida, dirSaida);
        nomeSvg = (char *)malloc(strlen(arqGeo) + 1);
        if (nomeSvg == NULL){
            printf("Erro inesperado! Memoria insuficiente para salvar o caminho do arquivo .geo.");
            exit(1);
        }
        strcpy(nomeSvg, arqGeo);
        //memcpy(nomeSvg, arqGeo + 1, strlen(arqGeo));
        pathSaida[strlen(pathSaida) - 1] = '\0';
        strncat(pathSaida, strrchr(nomeSvg, '/'), strlen(strrchr(nomeSvg, '/')) - 4);
        strcat(pathSaida, ".svg");
    }
    else if (dirSaida[strlen(dirSaida) - 1] != '/' && arqGeo[0] != '/' && arqGeo[0] != '.'){
        pathSaida = (char *)malloc(((strlen(dirSaida) + strlen(arqGeo)) + 3) * sizeof(char));
        if (pathSaida == NULL){
            printf("Erro inesperado! Memoria insuficiente para salvar o caminho do arquivo .geo.");
            exit(1);
        }
        strcpy(pathSaida, dirSaida);
        nomeSvg = (char *)malloc(strlen(arqGeo) + 1);
        if (nomeSvg == NULL){
            printf("Erro inesperado! Memoria insuficiente para salvar o caminho do arquivo .geo.");
            exit(1);
        }
        strcpy(nomeSvg, arqGeo);
        if (strrchr(nomeSvg, '/') == NULL){
            strcat(pathSaida, "/");
            strncat(pathSaida, arqGeo, strlen(arqGeo) - 4);
        }
        else{
            strncat(pathSaida, strrchr(nomeSvg, '/'), strlen(strrchr(nomeSvg, '/')) - 4);
        }
        strcat(pathSaida, ".svg");
    }
    else if ((dirSaida[strlen(dirSaida) - 1] != '/' && arqGeo[0] == '/') || (dirSaida[strlen(dirSaida) - 1] == '/' && arqGeo[0] != '/' && arqGeo[0] != '.')){
        pathSaida = (char *)malloc((strlen(dirSaida) + strlen(arqGeo) + 2) * sizeof(char));
        if (pathSaida == NULL){
            printf("Erro inesperado! Memoria insuficiente para salvar o caminho do arquivo .geo.");
            exit(1);
        }
        strcpy(pathSaida, dirSaida);
        nomeSvg = (char *)malloc(strlen(arqGeo) + 1);
        if (nomeSvg == NULL){
            printf("Erro inesperado! Memoria insuficiente para salvar o caminho do arquivo .geo.");
            exit(1);
        }
        strcpy(nomeSvg, arqGeo);
        if (strrchr(nomeSvg, '/') == NULL){
            strncat(pathSaida, nomeSvg, strlen(nomeSvg) - 4);
        }
        else{
            if(dirSaida[strlen(dirSaida) - 1] == '/'){
                pathSaida[strlen(pathSaida) - 1] = '\0';
            }
            strncat(pathSaida, strrchr(nomeSvg, '/'), strlen(strrchr(nomeSvg, '/')) - 4);
        }
        strcat(pathSaida, ".svg");
    }
    else if (dirSaida[strlen(dirSaida) - 1] == '/' && arqGeo[0] == '.'){
        //printf("%ld", strlen(arqGeo));
        pathSaida = (char *)malloc((strlen(dirSaida) + strlen(arqGeo)) * sizeof(char));
        if (pathSaida == NULL){
            printf("Erro inesperado! Memoria insuficiente para salvar o caminho do arquivo .geo.");
            exit(1);
        }
        strcpy(pathSaida, dirSaida);
        nomeSvg = (char *)malloc(strlen(arqGeo) + 1);
        if (nomeSvg == NULL){
            printf("Erro inesperado! Memoria insuficiente para salvar o caminho do arquivo .geo.");
            exit(1);
        }
        strcpy(nomeSvg, arqGeo);
        memcpy(nomeSvg, arqGeo + 2, strlen(arqGeo) - 1);
        if(strrchr(nomeSvg, '/') == NULL){
            strncat(pathSaida, nomeSvg, strlen(nomeSvg) - 4);
        }
        else{
            pathSaida[strlen(pathSaida) - 1] = '\0';
            strncat(pathSaida, strrchr(nomeSvg, '/'), strlen(strrchr(nomeSvg, '/')) - 4);
        }
        strcat(pathSaida, ".svg");

    }
    else if (dirSaida[strlen(dirSaida) - 1] != '/' && arqGeo[0] == '.'){
        pathSaida = (char *)malloc(((strlen(dirSaida) + strlen(arqGeo)) + 1) * sizeof(char));
        if (pathSaida == NULL){
            printf("Erro inesperado! Memoria insuficiente para salvar o caminho do arquivo .geo.");
            exit(1);
        }
        strcpy(pathSaida, dirSaida);
        nomeSvg = (char *)malloc(strlen(arqGeo) + 1);
        if (nomeSvg == NULL){
            printf("Erro inesperado! Memoria insuficiente para salvar o caminho do arquivo .geo.");
            exit(1);
        }
        strcpy(nomeSvg, arqGeo);
        // if (strrchr(nomeSvg, '/') == NULL){
        //     printf("aqui");
        //     memcpy(nomeSvg, arqGeo + 1, strlen(arqGeo));
        //     strncat(pathSaida, nomeSvg, strlen(nomeSvg) - 4);
        //     strcat(pathSaida, ".svg");
        // }
        memcpy(nomeSvg, nomeSvg + 1, strlen(arqGeo));
        strncat(pathSaida, strrchr(nomeSvg, '/'), strlen(strrchr(nomeSvg, '/')) - 4);
        strcat(pathSaida, ".svg");
    }
    free(nomeSvg);
    return pathSaida;
}

