#ifndef PREPROCESSO_H
#define PREPROCESSO_H

#include "calcularTFIDF.h"
#include "construirEDs.h"
#include "contarOcorrencias.h"
#include "dicionarioDinamico.h"
#include "elementoDicionarios.h"
#include "tratarTexto.h"
#include "vetorDinamico.h"
#include "wordToInt.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// OBS: O PROGRAMA EXECUTÁVEL DEVE ESTAR NA PASTA RAIZ "trabalho2" (ou uma pasta antes da pasta "fontes")
#define DIRETORIO_SCRIPTTRATADOR ""
#define NOMEARQUIVO_SCRIPTTRATADOR "tratarTexto.sh"

#define ALOCAR_PALAVRA (char*)malloc( sizeof(char)*MAX_N_CARACTERES_LINHA )

// $ sort -r -t: -k2 [filename] -o [filename]
#define ORDENAR_PELO_TFIDF "sort -r -t: -k2 -u " // início do comando a ser executado para ordenar o arquivo de informações importantes


// [3] CRIAR/CONSTRUIR ARQUIVO COM INFORMAÇÕES AS INFORMAÇÕES NECESSÁRIAS PARA O ÍNDICE REMISSIVO
char* preProcessar(const char* path_doc);



#endif
