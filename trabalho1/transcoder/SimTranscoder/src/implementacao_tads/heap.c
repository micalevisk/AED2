// heap.c
// Created by Micael Levi on 07/02/2016
// Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved.

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#include "fila.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define NaN NULL
#define TAM 10

#define ESQ(i) (2*(i)+1)
#define DIR(i) (2*(i)+2)
#define PAI(i) (((i)-1)/2)

// prioridade de 'a' é menor que a de 'b'
#define COMPARAR_PRIORIDADES(a,b) (comparar((a), (b)) < 0)

typedef struct{
	unsigned inseriu;
	unsigned removeu;
	unsigned movimentou;
	unsigned sobrecarregou;
} TStatsFila;

typedef struct{
	void* fila[TAM];
  int ocupacao;

	TStatsFila stats;
} TDadoFila;

short comparar(void* a, void* b){
	TComparavel* A = a;
	TComparavel* B = b;
	return A->compara(A, B);
}

// Heapify:
// Garante a manutenção da propriedade ordem do Heap; complexidade O(log n)
void ajustarHeap(TDadoFila* d, int pai, int posUltimo){
	void* aux;
	int esq, dir, posAtual;

  esq = ESQ(pai);
  dir = DIR(pai);
	posAtual = pai;

	if((esq <= posUltimo) && COMPARAR_PRIORIDADES(d->fila[posAtual], d->fila[esq]))	posAtual = esq;
	if((dir <= posUltimo) && COMPARAR_PRIORIDADES(d->fila[posAtual], d->fila[dir]))	posAtual = dir;

	if(posAtual != pai){
		aux				     = d->fila[pai];
		d->fila[pai]	 = d->fila[posAtual];
		d->fila[posAtual] = aux;

    //atualiza estatísticas
    d->stats.movimentou++;

		ajustarHeap(d, posAtual, posUltimo);
	}
}


static void* Desenfileirar(TFila *f){
	TDadoFila *d = f->dado;

  void *raiz = NULL;
  int posUltimo = d->ocupacao - 1;

  if(posUltimo > 0){
    raiz               = d->fila[0];
    d->fila[0]         = d->fila[posUltimo];
    d->fila[posUltimo] = raiz;

    //atualiza estatísticas
    d->stats.movimentou++;

    d->ocupacao--;
    posUltimo = d->ocupacao-1;

    if(posUltimo > 0) ajustarHeap(d, 0, posUltimo);
  }

	//atualiza estatísticas
	d->stats.removeu++;

	return raiz;
}


static short Enfileirar(TFila *f, void *elemento){
	short status = 1; // verdade (vai dar tudo certo)
	TDadoFila *d = f->dado;
  int i=d->ocupacao, posAncestral;
	void* aux; // auxilia na troca de endereços.

  if(i >= TAM) status=0;
  else{
      d->fila[i] = elemento;
      d->ocupacao++;

      posAncestral = PAI(i);
      for(; (i > 0) && (COMPARAR_PRIORIDADES(d->fila[posAncestral],d->fila[i])); posAncestral = PAI(i)){
        aux 				          =	d->fila[posAncestral];
        d->fila[posAncestral] = d->fila[i];
        d->fila[i]            = aux;

        //atualiza estatísticas
        d->stats.movimentou++;

        i = posAncestral;
      }
  }

	// Atualiza estatística
	d->stats.inseriu += status;
	d->stats.sobrecarregou += !status;

	return status;
}


static short Vazia(TFila *f){
	return !(((TDadoFila*)f->dado)->ocupacao);
}


static void Analytics(TFila *f){
	TDadoFila *d = f->dado;
	printf("\n");
	printf(ANSI_COLOR_GREEN " inserções : %u" ANSI_COLOR_RESET, d->stats.inseriu); printf("\n");
	printf(ANSI_COLOR_RED " removeu   : %u" ANSI_COLOR_RESET, d->stats.removeu); printf("\n");
	printf(ANSI_COLOR_YELLOW " movimentou: %u" ANSI_COLOR_RESET, d->stats.movimentou); printf("\n");
	printf(ANSI_COLOR_CYAN " sobrecarga: %u" ANSI_COLOR_RESET, d->stats.sobrecarregou); printf("\n");
}



TFila* criarFila(){
	TFila *f = malloc(sizeof(TFila));

	TDadoFila *d = malloc(sizeof(TDadoFila));
	d->ocupacao=0;

  f->dado = d;
	f->desenfileirar = Desenfileirar;
	f->enfileirar = Enfileirar;
	f->vazia = Vazia;
	f->analytics = Analytics;

	return f;
}

void destruirFila(TFila *f){
	free(f->dado);
	free(f);
}

void percorrer(TFila* f, void (*acao)(void*)){
	if(!Vazia(f)){
		TDadoFila* d = f->dado;
		int i=0;
		for(; i < d->ocupacao; i++) acao(d->fila[i]);
	}
}



/////////////////////// [ AFIM DE TESTES ] ////////////////////////////////////
/*
typedef struct tint INTEIRO;
struct tint{
	int *dado;
	int (*compara)(INTEIRO*,INTEIRO*);
};

int comparaINTEIROS(INTEIRO* a, INTEIRO* b){
	if(*(a->dado) > *(b->dado)) return 1;
	if(*(a->dado) < *(b->dado)) return -1;
	return 0;
}

void imprimir(void* e){
	INTEIRO* E = e;
	printf("%d, ", *(E->dado));
}

int main(){
	TFila* minhaFila = criarFila();

	int i, argc;
	scanf("%d",&argc); // primeira linha

	for(i=0; i < argc; i++){
		INTEIRO* aux = malloc(sizeof(INTEIRO));
		aux->compara = comparaINTEIROS;

		int *aux1 = malloc(sizeof(int));
		scanf("%d", aux1);

		aux->dado = aux1;
		// printf("%d ", *(aux->dado));
		minhaFila->enfileirar(minhaFila, aux);
	}

	percorrer(minhaFila, imprimir);
  printf("\n\n");
  minhaFila->desenfileirar(minhaFila);
  percorrer(minhaFila, imprimir);


  Analytics(minhaFila);
}
*/
