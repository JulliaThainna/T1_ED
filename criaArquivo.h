#ifndef criaArquivo_H_
#define criaArquivo_H_

/*Cria os arquivos de saida (.svg , -q.svg e .txt)
Parametros: char arqGeo[] - arquivo .geo passado pelo argumento do comando '-f' no siguel
            char dirSaida[] - diretorio de saida passado pelo argumento do comando '-o' no siguel
            char tipoArqE[] - tipo do arquivo de entrada ("geo" ou "qry")
            char tipoArqS[] - tipo do arquivo de saida ("svg" ou "txt")*/
char *criaArqSaida(char dirSaida[], char arqGeo[], char tipoArqE[], char tipoArqS[]);

#endif
