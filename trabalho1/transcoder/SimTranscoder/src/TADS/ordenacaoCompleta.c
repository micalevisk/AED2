//
// [ordencaoCompleta.c]
// Usando o princípio de fila inversa, i.e.,
// o elemento de maior prioridade está na última posição do vetor;
// isso implica numa remoção abstrata.
//
// Created by Micael Levi on 07/08/2016
// Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved.
//

#include "arrayDinamicoGenerico.h"
#include "../comparavel.h"
#include "ordenacaoFila.h"
#include <stdlib.h>

#define TAM 10

// A prioridade de 'a' é maior que a de 'b' ?
#define COMPARAR_PRIORIDADES(a,b) (comparar((a), (b)) > 0)

typedef struct{
  TArrayDinamico *vetorFila;

  int posPrimeiro;
  int posUltimo;

}TDadoTAD;

/* IMPLEMENTAÇÃO DOS MÉTODOS: */

// "Remove" o último e atualiza o ponteiro que indica a posição do último.
static void* _desenfileirar(TTAD* t){
  TDadoTAD *d = t->dado;
  return (d->posPrimeiro < 0) ?
    NULL :
    ((TArrayDinamico*)d->vetorFila)->acessar(d->vetorFila, d->posUltimo);
  /*
  if(d->posPrimeiro < 0) return NULL;

  TArrayDinamico *vet = d->vetorFila;
  int posElementoRemovido = --d->posUltimo;
  return vet->acessar(vet, posElementoRemovido);
  */
}

// Insere no final,
// verifica se o anterior tem prioridade menor que o inserido,
// se sim: swap
// senão: pára.
static short _enfileirar(TTAD* t, void* elemento){

  // if(!elemento) return 0;

  TDadoTAD *d = t->dado;
  printf("\t;enfileirar1;\n");
  int posInsercao = d->posUltimo + 1, i;
  printf("\t;enfileirar2;\n");
  void* aux;
  TArrayDinamico *vet = d->vetorFila;

  printf("\t;enfileirar3; %d\n", posInsercao);
  d->posUltimo = posInsercao;

  if(!posInsercao){
    d->posPrimeiro = posInsercao;
    vet->atualizar(vet, posInsercao, elemento);
  }
  else{
    unsigned tam = tamanhoDoArray(vet);
    if(posInsercao >= tam) ajustarArray(vet, tam * 2);

    vet->atualizar(vet, posInsercao, elemento);
    // trocar enquanto o anterior tiver prioridade menor que o último inserido.
		// Utilizar função de comparação de acordo com o tipo de elemento.
		for(i=posInsercao; (i > 0)
    && COMPARAR_PRIORIDADES(vet->acessar(vet, i-1), vet->acessar(vet, i)); i--){
      aux = vet->acessar(vet, i);
      vet->atualizar(vet, i, vet->acessar(vet, i-1));
      vet->atualizar(vet, i-1, aux);
    }
  }
  t->movimentacoes_enfileirar = posInsercao - i;
  return 1;
}


/*-----------------------------------------*/

TDadoTAD* criarDadoTAD(){
  TDadoTAD *d = malloc(sizeof(TDadoTAD));
  TArrayDinamico *v = criarAD(TAM);
  d->vetorFila = v;
  d->posPrimeiro = d->posUltimo = -1;
  return d;
}


TTAD* construirTAD(){
  TTAD *t = malloc(sizeof(TTAD));
  t->dado = criarDadoTAD();

  t->movimentacoes_enfileirar = t->movimentacoes_desenfileirar = 0;
  t->enfileirar     = _enfileirar;
  t->desenfileirar  = _desenfileirar;
}

void destruirTAD(TTAD* t){
  // TDadoTAD *d = t->dado;
  // destruirAD(d->vetorFila);
  free(t->dado);
  free(t);
  t=NULL;
}
