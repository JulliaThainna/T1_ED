#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "svg.h"
#include "lista.h"
#include "trataString.h"
#include "criaArquivo.h"

No *desenhaSvg(No *inicio, char pathSaida[]){
    FILE *arqSvg = NULL;

    arqSvg = fopen(pathSaida, "w");
    if(arqSvg == NULL){
        printf("\n\tErro inesperado! Nao foi possivel criar arquivo .svg.");
        printf("\n---------------------------------------------------\n");
        exit(1);
    }
    fprintf(arqSvg, "<svg>");

    No *aux = inicio;
    while(aux != NULL){
        if(aux->fig != NULL){

            if(aux->tipo == 'c'){
                fprintf(arqSvg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"%s\" fill=\"%s\"/>", aux->fig->crl.x, aux->fig->crl.y, aux->fig->crl.r, aux->fig->crl.corb, aux->fig->crl.corp);
            }

            else if(aux->tipo == 'r'){
                if(aux->id <= 0){
                    if(aux->fig->ret.trac == 1){ // <rect width="300" height="100" style=" fill:yellow; stroke:blue; stroke-dasharray: 10 10; stroke-width:4px" />
                        fprintf(arqSvg, "\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:%s;stroke:%s;stroke-dasharray: 3 3 3;fill-opacity:0.0;stroke-width:0.5\"/>", aux->fig->ret.x, aux->fig->ret.y, aux->fig->ret.w, aux->fig->ret.h, aux->fig->ret.corb, aux->fig->ret.corp); 
                    }
                    else{
                        fprintf(arqSvg, "\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:%s;stroke:%s;fill-opacity:0.0;stroke-width:0.5\"/>", aux->fig->ret.x, aux->fig->ret.y, aux->fig->ret.w, aux->fig->ret.h, aux->fig->ret.corb, aux->fig->ret.corp);
                    }
                }
                else{
                    fprintf(arqSvg, "\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:%s;stroke:%s\"/>", aux->fig->ret.x, aux->fig->ret.y, aux->fig->ret.w, aux->fig->ret.h, aux->fig->ret.corb, aux->fig->ret.corp);
                }
            }

            else if(aux->tipo == 't'){ 
                fprintf(arqSvg, "\n\t<text x=\"%f\" y=\"%f\" fill=\"%s\" stroke=\"%s\" stroke-width=\"0.5\">%s</text>", aux->fig->texto.x, aux->fig->texto.y, aux->fig->texto.corp, aux->fig->texto.corb, aux->fig->texto.texto);
            }

            else if(aux->tipo == 'l'){
                fprintf(arqSvg, "\n\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" style=\"stroke:%s;stroke-width:2\"/>", aux->fig->linha.x1, aux->fig->linha.y1, aux->fig->linha.x2, aux->fig->linha.y2, aux->fig->linha.corp);
            }
        }
        aux = aux->prox;
    }
    fprintf(arqSvg, "\n</svg>");
    fclose(arqSvg);
    printf("\n\tElementos .geo adicionados no .svg com sucesso!");

    return inicio;
}
