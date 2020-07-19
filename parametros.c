#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *buscaParametros(char *argv[], int i){
        char *parametro = NULL;

        if(strcmp(argv[i], "-e") == 0){     
            i++; 
            if(argv[i] == NULL){
                return NULL;
            }

            printf("\n\t\t> Diretorio de Entrada: %s", argv[i]);
            parametro = (char *)malloc((strlen(argv[i]) + 1) * sizeof(char)); 
            if(parametro == NULL){
                printf("\nErro inesperado! Memoria insuficiente para alocar o nome do diretorio de entrada.");
                printf("\n---------------------------------------------------\n");
                exit(1);
            }

            strcpy(parametro, argv[i]); 
        }

        else if(strcmp(argv[i], "-f") == 0){   
            i++;     
            if(argv[i] == NULL){
                return NULL;
            }

            printf("\n\t\t> Arquivo .geo: %s", argv[i]);
            parametro = (char *)malloc((strlen(argv[i]) + 1) * sizeof(char));
            if(parametro == NULL){
                printf("\nErro inesperado! Memoria insuficiente para alocar o nome do arquivo .geo.");
                printf("\n---------------------------------------------------\n");
                exit(1);
            }
            strcpy(parametro, argv[i]);
        }

        else if(strcmp(argv[i], "-q") == 0){       
            i++; 
            if(argv[i] == NULL){
                return NULL;
            }

            printf("\n\t\t> Arquivo .qry: %s", argv[i]);
            parametro = (char *)malloc((strlen(argv[i]) + 1) * sizeof(char));
            if(parametro == NULL){
                printf("\nErro inesperado! Memoria insuficiente para alocar o nome do arquivo .qry.");
                printf("\n---------------------------------------------------\n");
                exit(1);
            }
            strcpy(parametro, argv[i]);
        }

        else if(strcmp(argv[i], "-o") == 0){  
            i++;    
            if(argv[i] == NULL){
                return NULL;
            }
            
            printf("\n\t\t> Diretorio de Saida: %s", argv[i]);
            parametro = (char *)malloc((strlen(argv[i]) + 1) * sizeof(char));
            if(parametro == NULL){
                printf("\nErro inesperado! Memoria insuficiente para alocar o nome do diretorio de saida.");
                printf("\n---------------------------------------------------\n");
                exit(1);
            }
            strcpy(parametro, argv[i]);
        }

        else if(strcmp(argv[1], "H") == 0){  
            printf("\t\t\tLISTA DE COMANDOS: ");

            printf("\n\n\tTERMINAL:");
            printf("\n\t-e - DIRETORIO DE ENTRADA");
            printf("\n\t-f - ARQUIVO .geo");
            printf("\n\t-q - ARQUIVO .qry");
            printf("\n\t-o - DIRETORIO DE SAIDA");

            printf("\n\n\tARQUIVO .geo: ");
            printf("\n\tnx - NUMERO MAXIMO DE ELEMENTOS");
            printf("\n\tc - ELEMENTO DO TIPO CIRCULO");
            printf("\n\tr - ELEMENTO DO TIPO RETANGULO");
            printf("\n\tt - ELEMENTO DO TIPO TEXTO");

            printf("\n\n\tARQUIVO .qry: ");
            printf("\n\to? - VERIFICA SOBREPOSICAO");
            printf("\n\ti? - VERIFICA SE X,Y E INTERNO AO ELEMENTO");
            printf("\n\tpnt - MUDA A COR DO ELEMENTO");
            printf("\n\tpnt* - MUDA AS CORES DOS ELEMENTOS");
            printf("\n\tdelf - DELETA O ELEMENTO");
            printf("\n\tdelf* - DELETA OS ELEMENTOS");

            printf("\n\t---------------------------------------------------\n");
        }
        
        else{
            printf("\nComando siguel inexistente!\nDigite H para obter lista de comandos");
            printf("\n\t---------------------------------------------------\n");
            exit(1);           
        }

    return parametro;
}
