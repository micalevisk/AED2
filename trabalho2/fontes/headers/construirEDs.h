#ifndef CONSTRUIREDS_H
#define CONSTRUIREDS_H


#include "contarOcorrencias.h"
#include "dicionarioDinamico.h"
#include "elementoDicionarios.h"
#include "vetorDinamico.h"
#include "wordToInt.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define ESTIMAR(x) ((x)/2)  // tamanho inicial de um dicionário de palavras, onde x = quantidade de palavras do arquivo tratado
#define ID_PAG "PA"         // identificador de nova página



// [1] CRIAR ESTRUTURAS QUE POSSUEM AS INFORMAÇÕES NECESSÁRIAS PARA O CÁLCULO DO TF-IDF DE CADA PALAVRA EM CADA PÁGINA:
short construirEstruturasInformativas(FILE* fd_arqTratado, TDicionarioDinamico** dPalavras, TVetorDinamico** vPaginas, unsigned nPalavras, unsigned nPaginas);



#endif
