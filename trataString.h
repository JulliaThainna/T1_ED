#ifndef tratastring_H_
#define tratastring_H_


//Registros

/*Trata o caminho do arquivo de entrada (geo ou qry) para conseguir o caminho e abri-lo 
Parametros: char dirEntrada[] - diretorio .geo e .qry passado pelo argumento do comando '-e' no siguel
            char arqE[] - arquivo de entrada ("geo" ou "qry")*/
char *trataStringCaminho(char dirEntrada[], char arqE[]);

/*Trata a extensao do arquivo de saida (.svg , -q.svg ou .txt)
Parametros: char dirEntrada[] - diretorio .geo e .qry passado pelo argumento do comando '-e' no siguel
            char arqGeo[] - arquivo .geo passado pelo argumento do comando '-f' no siguel
            char tipoArqE[] - tipo do arquivo de entrada ("geo" ou "qry")
            char tipoArqS[] - tipo do arquivo de saida ("txt" ou "svg")*/
char *trataStringTipo(char dirSaida[], char arqGeo[], char tipoArqE[], char tipoArqS[]);

#endif
