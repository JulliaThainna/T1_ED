#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista.h"
#include "leitura.h"
#include "consulta.h"
#include "trataString.h"



No *abreGeo(char dirEntrada[], char arqGeo[], No *inicio){
    FILE *geo = NULL;
    char *pathEntrada = NULL;

    printf("\n\t\tABRINDO ARQUIVO .geo . . . ");
    if(dirEntrada == NULL){
        printf("\n\t\t > Arquivo .geo: %s", arqGeo);
        geo = fopen(arqGeo, "r");
        if(!geo){
           printf("\nErro inesperado! Nao foi possivel abrir o arquivo. Arquivo inexistente.");
           exit(1);
        }
    }
    
    else{
        pathEntrada = trataStringCaminho(dirEntrada, arqGeo);
        printf("\n\t > Arquivo .geo: %s", pathEntrada);
        geo = fopen(pathEntrada, "r");
        if(!geo){
            printf("\nErro inesperado! Nao foi possivel abrir o arquivo. Diretorio ou arquivo inexistente.");
            exit(1);
        }
    }
    printf("\n\t Arquivo .geo aberto com sucesso!");
    printf("\n\t---------------------------------------------------\n");

    inicio = comandoGeo(geo, inicio);

    fclose(geo);
    free(pathEntrada);

    return inicio;
}

No *comandoGeo(FILE *geo, No *inicio){
    int defaultNumMax = 1000, id, i = 0, buffer_size = 0;
    float r, x, y, w, h;
    char *texto = NULL;
    char comando[3] = {'\0', '\0', '\0'}, corb[22], corp[22], buffer;

    printf("\n\t\tLENDO ARQUIVO .geo . . . ");
    while(i < defaultNumMax){
        fscanf(geo, "%s", comando);
        if(feof(geo)){
            break;
        }
        if(strcmp(comando, "nx") == 0){
            fscanf(geo, "%d", &defaultNumMax);
            printf("\n\n\t> Numero maximo de elementos: %d", defaultNumMax);
        }
        else if(strcmp("c", comando) == 0){
            fscanf(geo, "%d %f %f %f %s %s", &id, &r, &x, &y, corb, corp);
            inicio = adicionaElemento(inicio, id, 'c');
            inicio = adicionaCirculo(inicio, id, r, x, y, corb, corp);
        }
        else if(strcmp("r", comando) == 0){
            fscanf(geo, "%d %f %f %f %f %s %s", &id, &w, &h, &x, &y, corb, corp);
            inicio = adicionaElemento(inicio, id, 'r');
            inicio = adicionaRetangulo(inicio, id, w, h, x, y, corb, corp);
        }
        else if(strcmp("t", comando) == 0){
            fscanf(geo, "%d %f %f %s %s", &id, &x, &y, corb, corp);
            buffer = getc(geo);
            while(!feof(geo) && buffer != '\n'){ 
                /*v ou v - executa
                v ou f - executa
                f ou v - executa
                f ou f - não executa
                
                f e f - não executa
                v e f - não executa
                f e v - não executa
                v e v - executa*/
                buffer = getc(geo);
                buffer_size++;
            }
            buffer_size++;
            fseek(geo, -buffer_size, SEEK_CUR);
            buffer = getc(geo);
            texto = (char *)malloc(sizeof(char) * (buffer_size + 1));
            if(texto == NULL){
                printf("\nErro inesperado! Memoria insuficiente para salvar o texto do elemento texto.");
                exit(1);
            }
            fscanf(geo, "%[^\n]s", texto);
            inicio = adicionaElemento(inicio, id, 't');
            inicio = adicionaTexto(inicio, id, x, y, texto, corb, corp, buffer_size);
            buffer_size = 0;
            free(texto);
        }
        i++;
    }

    printf("\n\n\tLeitura do arquivo .geo finalizada com sucesso!");
    return inicio;
}
