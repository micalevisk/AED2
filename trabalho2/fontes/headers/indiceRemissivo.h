#ifndef INDICEREMISSIVO_H
#define INDICEREMISSIVO_H

#include "contarOcorrencias.h"
#include "dicionarioDinamico.h"
#include "preProcesso.h"
#include "wordToInt.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TAMANHO_TABELA 100

// Elemento que estará no nó da lista que é um elemento do vetor principal que representa a tabela Hash
typedef struct{
  char* palavra;
  TVetorDinamico* vetorPaginas;
}TElementoIndice;

TDicionarioDinamico* gerarIndiceRemissivo(const char* path_livro);
void imprimirElementosDoVetor(TVetorDinamico* v);

#endif
