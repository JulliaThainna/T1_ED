#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "svg.h"
#include "lista.h"
#include "trataString.h"

No *desenhaSvg(No *inicio, char arqGeo[], char dirSaida[]){
    FILE *arqSvg = NULL;
    char *pathSaida = NULL;

    printf("\n\t\tABRINDO ARQUIVO .svg . . . ");
    pathSaida = trataStringTipo(dirSaida, arqGeo, 'g', 's'); //svg gerado pelo .geo
    printf("\n\t> Arquivo .svg: %s", pathSaida);
    arqSvg = fopen(pathSaida, "w");
    if(arqSvg == NULL){
        printf("\nErro inesperado! Nao foi possivel criar arquivo .svg.");
        exit(1);
    }
    printf("\n\tArquivo .svg aberto com sucesso!");
    printf("\n\t---------------------------------------------------\n");

    No *aux = inicio;
    printf("\n\t\tLENDO ARQUIVO .svg . . . ");
    printf("\n\tEXPORTANDO ELEMENTOS PARA O ARQUIVO .svg . . . ");
    //inicio = viewBoxSvg(inicio, arqSvg);

    fprintf(arqSvg, "<svg>");
    while (aux != NULL){
        if (aux->fig != NULL){
            if (aux->tipo == 'c'){ // <circle cx="50" cy="50" r="40" stroke="green" stroke-width="4" fill="yellow" />
                fprintf(arqSvg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"%s\" fill=\"%s\"/>", aux->fig->crl.x, aux->fig->crl.y, aux->fig->crl.r, aux->fig->crl.corb, aux->fig->crl.corp);
            }
            else if (aux->tipo == 'r'){ //<rect width="300" height="100" style="fill:rgb(0,0,255);stroke-width:3;stroke:rgb(0,0,0)" />
                fprintf(arqSvg, "\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:%s;stroke:%s\"/>", aux->fig->ret.x, aux->fig->ret.y, aux->fig->ret.w, aux->fig->ret.h, aux->fig->ret.corb, aux->fig->ret.corp);
            }
            else if (aux->tipo == 't'){ //<text x="0" y="15" fill="red">I love SVG!</text>
                fprintf(arqSvg, "\n\t<text x=\"%f\" y=\"%f\" fill=\"%s\" stroke=\"%s\" stroke-width=\"0.5\">%s</text>", aux->fig->texto.x, aux->fig->texto.y, aux->fig->texto.corp, aux->fig->texto.corb, aux->fig->texto.texto);
            }
        }
        aux = aux->prox;
    }

    fprintf(arqSvg, "\n</svg>");
    fclose(arqSvg);
    printf("\n\tElementos .geo adicionados no .svg com sucesso!");
    free(pathSaida);
    
    return inicio;
}
