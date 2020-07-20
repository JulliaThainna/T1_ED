#ifndef consulta_H_
#define consulta_H_

#include <stdbool.h>
#include "lista.h"

/*Abre o arquivo .qry a partir do caminho que o usuario passou no siguel, e se houver o comando '-e', tratado na funcao
trataStringCaminho
Parametros: No* inicio - inicio da lista
            char dirEntrada[] - o argumento comando '-e' passado pelo usuario como argumento do siguel
            char arqQry[] - o argumento comando '-q' passado pelo usuario como argumento do siguel
            char pathSaida[] - Arquivo criado pela funcao criaArquivo na main, caminho do .txt*/
void abreQry(No *inicio, char dirEntrada[], char arqQry[], char pathSaida[]);

/*Le os comandos do arquivo .qry e a assim, chama as funcoes relativas as consultas desejadas pelo usuario
Parametros: No *inicio - inicio da lista
            FILE *qry - o caminho do arquivo .qry estabelecido na funcao trataStringCaminho dentro da funcao abreQry
            char pathSaida[] - Arquivo criado pela funcao criaArquivo na main, caminho do .txt*/
void comandoQry(No *inicio, FILE *qry, char pathSaida[]);

/*As proximas quatro funcoes sao relativas aos comandos do .qry: o?, i?, pnt, pnt* respectivamente.
obs: delf e delf* estao no lista.h, pois, decidi organanizar de forma que, as operacoes voltadas para listas
ficassem no mesmo arquivo*/ 

/*Verifica se os elementos j e k se sobrepoem (obs: apenas circulos e retangulos)
Parametros: No *inicio - inicio da lista
            int j - id do elemento j lido do arquivo .qry (> 0)
            int k - id do elemento k lido do arquivo .qry (> 0)
*/
int sobrepoe(No *inicio, int j, int k); 


/*Verifica se a coordenada x,y esta dentro do elemento j (obs: apenas circulos e retangulos)
Parametros: No *inicio - inicio da lista
            int j - id do elemento j lido do arquivo .qry (> 0)
            float x - coordenada x lida do arquivo .qry
            float y - coordenada y lida do arquivo .qry
*/
int ponto(No *inicio, int j, float x, float y);

/*Muda as cores da borda e do preenchimento do elemento j
Parametros: No *inicio - inicio da lista
            int j - id do elemento j lido do arquivo .qry (> 0)
            char corb[] - cor da borda lida do arquivo .qry
            char corp[] - cor do preenchimento lido do arquivo .qry*/
int mudaCorj(No *inicio, int j, char corb[], char corp[]);

/*Muda as cores da borda e do preenchimento dos elemento j ate k (incluindo os mesmos)
Parametros: No *inicio - inicio da lista
            int j - id do elemento j lido do arquivo .qry (> 0)
            int k - id do elemento k lido do arquivo .qry (> 0)
            char corb[] - cor da borda lida do arquivo .qry
            char corp[] - cor do preenchimento lido do arquivo .qry*/
int mudaCorjk(No *inicio, int j, int k, char corb[], char corp[]);

/*Gera as coordenadas referentes aos comando o? i?. Quando ha um arquivo .qry, um novo svg e gerado, portanto, no o? 
sua saida gera um retangulo tracejado em volta das figuras que nao se sobrepoem e um retangulo com linha cheia envolta 
das figuras que se sobrepoem. O i? gera na saida, um ponto (pequeno circulo) nas coordenadas x,y e uma linha que liga
x,y ate o centro de massa da figura, azul se o ponto for interno e magenta se for externo.
Parametros: No *inicio - inicio da lista
            int j - id do elemento j lido do arquivo .qry (existe em: o? e i?)(> 0)
            int k - id do elemento j lido do arquivo.qry (existe em: o?) (> 0)
            char comando[] - comando lido do arquivo .qry (i? ou o?)
            int retorno - retorno que a funcao sobrepoe/ponto retorna (1 - sobrepoe/interno | 0 - nao sobrepoe/externo)
            int id - id gerado pelo comandoQry para os novos elementos que serao adicionados a lista (vulgo, circulos
            retangulos e linhas) necessario para que gere valores <= 0 e nao conflitem com a lista atual (<= 0)*/
void geraCoordenadas(No *inicio, int j, int k, float x, float y, char comando[], int retorno, int id);

#endif
