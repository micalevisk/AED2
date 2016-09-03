//
// [ordencaoCompleta.c]
// Usando o princípio de fila inversa, i.e.,
// o elemento de maior prioridade está na última posição do vetor;
// isso implica numa remoção abstrata.
//
// Created by Micael Levi on 07/08/2016
// Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved.
//

#include "ordenacaoFila.h"
#include <stdlib.h>


typedef struct{
  TArrayDinamico *vetorFila;

  int posPrimeiro;
  int posUltimo;

}TDadoTAD;

/* ---------------- IMPLEMENTAÇÃO DOS MÉTODOS: -------------------------- */

// "Remove" o último e atualiza o ponteiro que indica a posição do último.
// isso implica em zero movimentações ao desenfileirar.
static void* _desenfileirar(TTAD* t){
  TDadoTAD *d = t->dado;
  TArrayDinamico *vet = d->vetorFila;

  if(d->posUltimo < 0) return NULL;
  void* ultimoElemento = vet->acessar(vet, d->posUltimo);
  d->posUltimo--;

  return ultimoElemento;
}

// Insere no final,
// verifica se o anterior tem prioridade maior que o inserido,
// se sim: swap
// senão: pára.
static short _enfileirar(TTAD* t, void* elemento){
  TDadoTAD *d = t->dado;
  if(!elemento || !d) return 0;

  int posInsercao = d->posUltimo + 1, i;
  TArrayDinamico *vet = d->vetorFila;

  d->posUltimo = posInsercao;

  if(!posInsercao){
    d->posPrimeiro = posInsercao;
    vet->atualizar(vet, posInsercao, elemento);
  }
  else{
    unsigned tam = vet->tamanho(vet);
    if(posInsercao >= tam){
       ajustarAD(vet, tam * 2);
       t->sobrecarga++;
    }

    vet->atualizar(vet, posInsercao, elemento);

		for(i=posInsercao; (i > 0)
      && COMPARAR_PRIORIDADES(vet->acessar(vet, i-1), elemento); i--){
        vet->atualizar(vet, i, vet->acessar(vet, i-1));
        vet->atualizar(vet, i-1, elemento);
    }

    t->movimentacoes_enfileirar += posInsercao - i;
  }

  return 1;
}


/*-----------------------------------------*/

TDadoTAD* criarDadoTAD(){
  TDadoTAD *d = malloc(sizeof(TDadoTAD));

  d->vetorFila = construirAD(TAM);
  d->posPrimeiro = d->posUltimo = -1;
  return d;
}


TTAD* construirTAD(){
  TTAD *t = malloc(sizeof(TTAD));
  t->dado = criarDadoTAD();

  t->movimentacoes_enfileirar = t->movimentacoes_desenfileirar = t->sobrecarga = 0;
  t->enfileirar     = _enfileirar;
  t->desenfileirar  = _desenfileirar;
}

void destruirTAD(TTAD* t){
  TDadoTAD *d = t->dado;
  destruirAD(d->vetorFila);
  free(d);
  free(t);
  t=NULL;
}
