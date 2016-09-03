//
//  [calcularTFIDF.c]
//  Created by Micael Levi on 08/12/2016
//  Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved.
//

#include "headers/calcularTFIDF.h"

static unsigned n_containing(char* palavra, TDicionarioDinamico* dPalavras){
    if(!dPalavras || !palavra) return 0;
    TElemento elementoBuscado_aux = { .palavra = palavra };
    TElemento* elementoBuscado = dPalavras->buscar(dPalavras, &elementoBuscado_aux);
    if(!elementoBuscado) return 0;
    return elementoBuscado->info;
}


static float tf(TDicionarioDinamico* dVetorPaginas, TElemento* elemento){
    if(!dVetorPaginas || !elemento) return 0;
    unsigned qtdOcorrencias = elemento->info;
    unsigned nTotalPalavras = dVetorPaginas->ocupacao;
    return (qtdOcorrencias /(float)nTotalPalavras);
}


static float idf(char* palavra,TVetorDinamico* vetorPaginas, TDicionarioDinamico* dPalavras){
  if(!dPalavras || !vetorPaginas || !palavra) return 0.0;
  unsigned nTotalPaginas = vetorPaginas->ocupacao(vetorPaginas);
  unsigned nPaginasQuePossuemPalavra = n_containing(palavra, dPalavras) + 1;
  return log10((nTotalPaginas/(float)nPaginasQuePossuemPalavra));
}


float TFIDF(TElemento* elemento, TDicionarioDinamico* dPalavras, TDicionarioDinamico* dVetorPaginas, TVetorDinamico* vetorPaginas){
  if(!elemento || !dPalavras || !dVetorPaginas || !vetorPaginas) return 0;
  return (tf(dVetorPaginas, elemento) * idf(elemento->palavra, vetorPaginas, dPalavras));
}
