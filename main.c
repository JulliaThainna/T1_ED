#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lista.h"
#include "leitura.h"
#include "consulta.h"
#include "svg.h"
#include "criaArquivo.h"
#include "parametros.h"


int main(int argc, char *argv[]){

    No *lista = NULL;
    char *dirEntrada = NULL;
    char *arqGeo = NULL;
    char *arqQry = NULL;
    char *dirSaida = NULL;
    char *pathSaida = NULL;

    printf("\n\t---------------------------------------------------\n");
    for(int i = 1; argc > i; i++){    //argc 
        if(strcmp(argv[i], "-e") == 0){     
            dirEntrada = buscaParametros(argv, i);
            i++; 
        }
        else if(strcmp(argv[i], "-f") == 0){        
            arqGeo = buscaParametros(argv, i);
            i++; 
        }
        else if(strcmp(argv[i], "-q") == 0){       
            arqQry = buscaParametros(argv, i);
            i++; 
        }
        else if(strcmp(argv[i], "-o") == 0){     
            dirSaida = buscaParametros(argv, i);
            i++; 
        }
        else if(strcmp(argv[1], "H") == 0){     
            buscaParametros(argv, i);
            exit(1);
        }
    }
    
    if((arqGeo == NULL || dirSaida == NULL) && strcmp(argv[1], "H") != 0){ 
        printf("\nParametros essenciais nao foram inseridos!");
        printf("\n\t---------------------------------------------------\n");
        exit(1);
    }
    printf("\n\t---------------------------------------------------\n");

    lista = abreGeo(lista, dirEntrada, arqGeo);
    printf("\n\t---------------------------------------------------\n");
    pathSaida = criaArqSaida(dirSaida, arqGeo, "geo", "svg");
    desenhaSvg(lista, pathSaida);
    free(pathSaida);
    printf("\n\t---------------------------------------------------\n");
    lista = imprimeLista(lista);
    printf("\n\t---------------------------------------------------\n");

    if(arqQry != NULL){
        pathSaida = criaArqSaida(dirSaida, arqGeo, "qry", "txt");
        printf("\n\t---------------------------------------------------\n");
        abreQry(lista, dirEntrada, arqQry, pathSaida);
        free(pathSaida);
        printf("\n\t---------------------------------------------------\n");
        pathSaida = criaArqSaida(dirSaida, arqGeo, "qry", "svg"); 
        printf("\n\t---------------------------------------------------\n");
        lista = imprimeLista(lista);
        printf("\n\t---------------------------------------------------\n");
        desenhaSvg(lista, pathSaida); 
    }
    printf("\n\t---------------------------------------------------\n");

    //Libera o espaco alocado para as variaveis
    lista = deletaLista(lista);
    free(dirEntrada);
    free(arqGeo);
    free(arqQry);
    free(dirSaida);
    free(pathSaida);
    printf("\n\t\tMemoria desalocada com sucesso!");
    printf("\n\t\tPROCESSO CONCLUIDO COM SUCESSO!\n");
    
    return 0;
}

//No *abreGeo, No *comandoGeo
//No *abreQry, No *comandoQry
//Por que no primeiro tem que ser No* senao a lista se perde e no segundo pode ser void?