#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trataString.h"
#include "lista.h"

char *trataStringCaminho(char dirEntrada[], char arqGeo[], char pathEntrada[], char nomeGeo[]){
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

char *trataStringTipo(char dirSaida[], char arqGeo[], char pathSaida[], char nomeSvg[], char tipo){
    if (dirSaida[strlen(dirSaida) - 1] == '/' && arqGeo[0] == '/'){ // -o geoFiles/ -f /hino-01.geo
        //printf("\n%d", (strlen(dirSaida) + strlen(arqGeo)) - 1);
        if(tipo == 's'){
            pathSaida = (char *)malloc(((strlen(dirSaida) + strlen(arqGeo)) + 1) * sizeof(char));
        }
        else{
            pathSaida = (char *)malloc(((strlen(dirSaida) + strlen(arqGeo)) + 3) * sizeof(char));
        }
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
        if(tipo == 's'){
            strcat(pathSaida, ".svg");
        }
        else{
            strcat(pathSaida, "-q.txt");
        }
    }
    else if (dirSaida[strlen(dirSaida) - 1] != '/' && arqGeo[0] != '/' && arqGeo[0] != '.'){
        if(tipo == 's'){
            pathSaida = (char *)malloc(((strlen(dirSaida) + strlen(arqGeo)) + 3) * sizeof(char));
        }
        else{
            pathSaida = (char *)malloc(((strlen(dirSaida) + strlen(arqGeo)) + 5) * sizeof(char));
        }
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
        if(tipo == 's'){
            strcat(pathSaida, ".svg");
        }
        else{
            strcat(pathSaida, "-q.txt");
        }
    }
    else if ((dirSaida[strlen(dirSaida) - 1] != '/' && arqGeo[0] == '/') || (dirSaida[strlen(dirSaida) - 1] == '/' && arqGeo[0] != '/' && arqGeo[0] != '.')){
        if(tipo == 's'){
            pathSaida = (char *)malloc((strlen(dirSaida) + strlen(arqGeo) + 2) * sizeof(char));
        }
        else{
            pathSaida = (char *)malloc((strlen(dirSaida) + strlen(arqGeo) + 4) * sizeof(char));
        }
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
        if (strrchr(nomeSvg, '/') == NULL){ //no caso de: /arquivo.geo
            strncat(pathSaida, nomeSvg, strlen(nomeSvg) - 4);
        }
        else{ //no caso de: pasta/pastinha/arquivo.geo
            if(dirSaida[strlen(dirSaida) - 1] == '/'){
                pathSaida[strlen(pathSaida) - 1] = '\0';
            }
            strncat(pathSaida, strrchr(nomeSvg, '/'), strlen(strrchr(nomeSvg, '/')) - 4);
        }
        if(tipo == 's'){
            strcat(pathSaida, ".svg");
        }
        else{
            strcat(pathSaida, "-q.txt");
        }
    }
    else if (dirSaida[strlen(dirSaida) - 1] == '/' && arqGeo[0] == '.'){
        //printf("%ld", strlen(arqGeo));
        if(tipo == 's'){
            pathSaida = (char *)malloc((strlen(dirSaida) + strlen(arqGeo)) * sizeof(char));
        }
        else{
            pathSaida = (char *)malloc((strlen(dirSaida) + strlen(arqGeo) + 2) * sizeof(char));
        }
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
        if(tipo == 's'){
            strcat(pathSaida, ".svg");
        }
        else{
            strcat(pathSaida, "-q.txt");
        }

    }
    else if (dirSaida[strlen(dirSaida) - 1] != '/' && arqGeo[0] == '.'){
        if(tipo == 's'){
            pathSaida = (char *)malloc(((strlen(dirSaida) + strlen(arqGeo)) + 1) * sizeof(char));
        }
        else{
            pathSaida = (char *)malloc(((strlen(dirSaida) + strlen(arqGeo)) + 3) * sizeof(char));
        }
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
        //strcpy(nomeSvg, arqGeo);
        // if (strrchr(nomeSvg, '/') == NULL){
        //     printf("aqui");
        //     memcpy(nomeSvg, arqGeo + 1, strlen(arqGeo));
        //     strncat(pathSaida, nomeSvg, strlen(nomeSvg) - 4);
        //     strcat(pathSaida, ".svg");
        // }
        memcpy(nomeSvg, arqGeo + 1, strlen(arqGeo)); //aqui não poderia ser o arqGeo
        strncat(pathSaida, strrchr(nomeSvg, '/'), strlen(strrchr(nomeSvg, '/')) - 4);
        if(tipo == 's'){
            strcat(pathSaida, ".svg");
        }
        else{
            strcat(pathSaida, "-q.txt");
        }
    }
    free(nomeSvg);
    return pathSaida;
}

