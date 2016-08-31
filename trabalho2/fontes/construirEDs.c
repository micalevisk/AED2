//
//  [construirEDs.c]
//  Created by Micael Levi on 08/11/2016
//  Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved.
//

#include "headers/construirEDs.h"
#define ALOCAR_PALAVRA (char*)malloc( sizeof(char)*MAX_N_CARACTERES_LINHA )
// #define ERROR(number, fileBaseName, functionName) { fprintf(stderr, "\e[1;49;3%hhum" "ERRO%hhu: %s.c => %s()" "\e[0m\n", number, number, fileBaseName, functionName); exit(2); }


// [1.1] Inserir nos Dicionários de Palavas (simples e do vetor de páginas)
static short inserirNosDicionariosDePalavras(TDicionarioDinamico** _dVetorPaginas, TDicionarioDinamico** _dPalavras, TElemento* elementoASerInserido){
  TDicionarioDinamico* dVetorPaginas = *_dVetorPaginas;
  TDicionarioDinamico* dPalavras = *_dPalavras;
  if(!elementoASerInserido || !dPalavras || !dVetorPaginas) return 0;

  unsigned nOcorrencias = ++(elementoASerInserido->info);
  dVetorPaginas->inserir(dVetorPaginas, elementoASerInserido);

  #ifdef ERROR
  if( !(dVetorPaginas->buscar(dVetorPaginas, elementoASerInserido)) )
    ERROR(2, "construirEDs", "inserirNosDicionariosDePalavras");
  #endif

  if(nOcorrencias == 1){
    // primeira ocorrência da palavra na página
    TElemento* elementoBuscado = dPalavras->buscar(dPalavras, elementoASerInserido);
    if(!elementoBuscado) dPalavras->inserir(dPalavras, elementoASerInserido);
    else ++(elementoBuscado->info);
  }

  return 1;
}


void imprimir(void* elemento){
  if(!elemento) return;
  TElemento* E = elemento;
  printf("%s\n", E->palavra);
}


// [1] CRIAR ESTRUTURAS QUE POSSUEM AS INFORMAÇÕES NECESSÁRIAS PARA O CÁLCULO DO TF-IDF DE CADA PALAVRA EM CADA PÁGINA:
short construirEstruturasInformativas(FILE* fd_arqTratado, TDicionarioDinamico** dPalavras, TVetorDinamico** vPaginas, unsigned nPalavras, unsigned nPaginas){
  if(!fd_arqTratado || !nPalavras || !nPaginas) return 0;

  TDicionarioDinamico* dicionarioPalavras = criarDicionarioDinamico(ESTIMAR(nPalavras), converterParaNumero, cmpElementos); // guardará uma palavra associada à quantidade de páginas em que ela aparece
  TVetorDinamico* vetorPaginas = criarVetorDinamico(nPaginas);
  unsigned indice; // para percorrer o vetor de páginas, indice = número da página corrente - 1;

  // [1.2] Criar e Preencher Dicionários de Palavras do Vetor de Páginas e do Dicionário Simples de Palavras:
  char* formatacaoLeituraPalavra = (char*)malloc( sizeof(char)*(MAX_N_CARACTERES_LINHA+strlen("%%s")) );
  sprintf(formatacaoLeituraPalavra, "%%%us", MAX_N_CARACTERES_LINHA);
  char* palavraCorrente;

  short novaPagina=0;


  char flag=0;
  char* buff;


  rewind(fd_arqTratado);
  for(indice=-1, palavraCorrente=ALOCAR_PALAVRA; (fscanf(fd_arqTratado, formatacaoLeituraPalavra, palavraCorrente))!=EOF; palavraCorrente=ALOCAR_PALAVRA){
    TDicionarioDinamico* dicionarioPagCorrente = NULL;
    // compondo elemento relacionado à palavra corrente
    TElemento* elementoCorrente = malloc(sizeof(TElemento));
    elementoCorrente->palavra = palavraCorrente;
    elementoCorrente->info = 0;

    // printf("(%s)\n", palavraCorrente);
    if(!compararPalavras(ID_PAG, palavraCorrente)){
      novaPagina = 1;
      ++indice;
      // printf("PAGINA CORRENTE: %u\n", indice+1);
      continue;
    }

    else if(novaPagina){
      dicionarioPagCorrente = criarDicionarioDinamico(ESTIMAR(nPalavras), converterParaNumero, cmpElementos); // inicializa o dicionário de palavras para a página corrente
      vetorPaginas->inserir(vetorPaginas, indice, dicionarioPagCorrente);
      inserirNosDicionariosDePalavras(&dicionarioPagCorrente, &dicionarioPalavras,  elementoCorrente);
      novaPagina = 0;

      #ifdef ERROR
      TDicionarioDinamico* teste = vetorPaginas->elemento(vetorPaginas, indice);
      if(!teste->buscar(teste, elementoCorrente))
        ERROR(1, "construirEDs", "construirEstruturasInformativas");
      #endif

    }
    else{
      dicionarioPagCorrente = vetorPaginas->elemento(vetorPaginas, indice);
      TElemento* elementoBuscado = dicionarioPagCorrente->buscar(dicionarioPagCorrente, elementoCorrente);
      if(elementoBuscado) elementoCorrente = elementoBuscado;
      inserirNosDicionariosDePalavras(&dicionarioPagCorrente, &dicionarioPalavras, elementoCorrente);
    }
  }

  *dPalavras = dicionarioPalavras;
  *vPaginas  = vetorPaginas;

  #ifdef ERROR
    // printf("ocupacao vetor de páginas = número de páginas                                    : %u\n", (*vPaginas)->ocupacao(*vPaginas));
    // printf("ocupacao dicionario de palavras = número de palavras (não-páginas&sem-repetiçoes): %u\n", (*dPalavras)->ocupacao);
    TElemento elementoCorrente_aux = { .palavra = "original", .info = 0 };
    TDicionarioDinamico* d1 = vetorPaginas->elemento(vetorPaginas, 0);

    // d1->percorrer(d1, imprimir);
    if( !(d1->buscar(d1, &elementoCorrente_aux)) )
      ERROR(3, "construirEDs", "construirEstruturasInformativas");
  #endif

  return 1;
}
