//
//  [construirEDs.c]
//  Created by Micael Levi on 08/11/2016
//  Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved.
//

#include "headers/construirEDs.h"
#define ALOCAR_PALAVRA (char*)malloc( sizeof(char)*MAX_N_CARACTERES_LINHA )


// [1.1] Inserir nos Dicionários de Palavas (simples e do vetor de páginas)
static short inserirNosDicionariosDePalavras(TDicionarioDinamico** _dVetorPaginas, TDicionarioDinamico** _dPalavras, TElemento* elementoASerInserido){
  TDicionarioDinamico* dVetorPaginas = *_dVetorPaginas;
  TDicionarioDinamico* dPalavras = *_dPalavras;
  if(!elementoASerInserido || !dPalavras || !dVetorPaginas) return 0;

  unsigned nOcorrencias = ++(elementoASerInserido->info);
  dVetorPaginas->inserir(dVetorPaginas, elementoASerInserido);

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

  TDicionarioDinamico* dicionarioPalavras = criarDicionarioDinamico(ESTIMAR(nPalavras), converterParaNumero, cmpElementos);
  TVetorDinamico* vetorPaginas = criarVetorDinamico(nPaginas);
  unsigned indice;

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

    TElemento* elementoCorrente = malloc(sizeof(TElemento));
    elementoCorrente->palavra = palavraCorrente;
    elementoCorrente->info = 0;

    if(!compararPalavras(ID_PAG, palavraCorrente)){
      novaPagina = 1;
      ++indice;
      continue;
    }

    else if(novaPagina){
      dicionarioPagCorrente = criarDicionarioDinamico(ESTIMAR(nPalavras), converterParaNumero, cmpElementos);
      vetorPaginas->inserir(vetorPaginas, indice, dicionarioPagCorrente);
      inserirNosDicionariosDePalavras(&dicionarioPagCorrente, &dicionarioPalavras,  elementoCorrente);
      novaPagina = 0;
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

  return 1;
}
