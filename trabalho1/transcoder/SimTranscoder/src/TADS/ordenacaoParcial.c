//
// [ordencaoParcial.c]
// Usando o princípio de Heap de máxima, i.e.,
// o elemento de maior prioridade está na primeira posição do vetor (e é chamado de raiz);
// a remoção é feita tratando o vetor como árvore binária completa e de prioridade.
//
// Created by Micael Levi on 07/09/2016
// Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved.
//

#include "ordenacaoFila.h"
#include <stdlib.h>

#define PAI(i) (((i)-1)/2)

typedef struct{
  TArrayDinamico *vetorFila;

  int ocupacao;

}TDadoTAD;


/* ------------------------ AUXILIAR: --------------------------------- */

// Heapify:
// Garante a manutenção da propriedade ordem do Heap; complexidade O(log n)
void ajustarHeap(TTAD* t, int pai, int posUltimo){
  TDadoTAD *d = t->dado;
  TArrayDinamico *vet = d->vetorFila;
  void *aux;
  int esq, dir, posAtual;

  esq = 2*pai + 1;
  dir = esq + 1;
  posAtual = pai;

  // o filho esquerdo tem prioridade maior que o seu pai?
  if( (esq <= posUltimo)
    && COMPARAR_PRIORIDADES(vet->acessar(vet, esq), vet->acessar(vet, posAtual)) )
    posAtual = esq;
  // o filho direito tem prioridade maior que o filho/pai que está na posição posAtual?
  if( (dir <= posUltimo)
    && COMPARAR_PRIORIDADES(vet->acessar(vet, dir), vet->acessar(vet, posAtual)) )
    posAtual = dir;

  if(posAtual != pai){
    aux = vet->acessar(vet, pai);
    vet->atualizar(vet, pai, vet->acessar(vet, posAtual));
    vet->atualizar(vet, posAtual, aux);

    t->movimentacoes_desenfileirar++;
    ajustarHeap(t, posAtual, posUltimo);
  }

}



/* ---------------- IMPLEMENTAÇÃO DOS MÉTODOS: -------------------------- */

// Se tiver mais de 1 elementos:
// - swap entre a raiz (que será removido por ter maior prioridade) e o último;
// depois ajusta o vetor para obedecer a propriedade de ordem do Heap:
// - "desce" o elemento da raiz enquanto seus filhos tiverem maior prioridade.
static void* _desenfileirar(TTAD* t){
  TDadoTAD *d = t->dado;
  int posUltimo = d->ocupacao - 1;
  void *raiz = NULL;
  TArrayDinamico *vet = d->vetorFila;

  if(posUltimo >= 0){
      raiz = vet->acessar(vet, 0);
      vet->atualizar(vet, 0, vet->acessar(vet, posUltimo));
      vet->atualizar(vet, posUltimo, raiz);

      t->movimentacoes_desenfileirar++;
      posUltimo = (--d->ocupacao) - 1;
      // d->ocupacao--;
      // posUltimo = d->ocupacao - 1;
      if(posUltimo > 0) ajustarHeap(t, 0, posUltimo);
  }

  return raiz;
}

// Insere no final,
// verifica se o ancestral tem prioridade menor que o inserido,
// se sim: swap
// senão: pára.
static short _enfileirar(TTAD* t, void* elemento){
  TDadoTAD *d = t->dado;
  if(!elemento || !d) return 0;

  int posInsercao = d->ocupacao, i;
  int posAncestral = PAI(posInsercao);
  void *elementoAncestral;

  TArrayDinamico *vet = d->vetorFila;
  unsigned tam = vet->tamanho(vet);

  if(posInsercao >= tam){
    ajustarAD(vet, tam * 2);
    t->sobrecarga++;
  }

  vet->atualizar(vet, posInsercao, elemento);
  d->ocupacao++;

  for(i=posInsercao; (i > 0)
    && COMPARAR_PRIORIDADES(elemento, vet->acessar(vet,posAncestral)); ){
      vet->atualizar(vet, i, vet->acessar(vet, posAncestral));
      vet->atualizar(vet, posAncestral, elemento);

      // elementoAncestral = vet->acessar(vet, posAncestral);
      // vet->atualizar(vet, posAncestral, elemento);
      // vet->atualizar(vet, i, elementoAncestral);

      t->movimentacoes_enfileirar++;
      i = posAncestral;
      posAncestral = PAI(i);
  }

  return 1;
}


/*-----------------------------------------*/

TDadoTAD* criarDadoTAD(){
  TDadoTAD *d = malloc(sizeof(TDadoTAD));
  d->vetorFila = construirAD(TAM);
  d->ocupacao = 0;
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
