// heapD.c
// Created by Micael Levi on 07/03/2016
// Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved.

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#include "comparavel.h"
#include "heap.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TAM 2

#define TIPOSTATS unsigned long long
#define DIRETIVASTATS "%llu\n"

#define PAI(i) (((i)-1)/2)

// prioridade de 'a' é menor que a de 'b'
#define COMPARAR_PRIORIDADES(a,b) (comparar((a), (b)) < 0)

typedef struct{
	TIPOSTATS inseriu;
	TIPOSTATS removeu;
	TIPOSTATS movimentou;
	TIPOSTATS sobrecarregou;
} TStatsFila;

typedef struct{
	void** fila;
	unsigned tamanho;

  int ocupacao;

	TStatsFila stats;
} TDadoFila;



// Heapify:
// Garante a manutenção da propriedade ordem do Heap; complexidade O(log n)
void ajustarHeap(TDadoFila* d, int pai, int posUltimo){
	void *aux;
	int esq, dir, posAtual;

  esq = 2*pai + 1;
  dir = esq + 1;
	posAtual = pai;

	if((esq <= posUltimo) && COMPARAR_PRIORIDADES(d->fila[posAtual], d->fila[esq]))	posAtual = esq;
	if((dir <= posUltimo) && COMPARAR_PRIORIDADES(d->fila[posAtual], d->fila[dir]))	posAtual = dir;

	if(posAtual != pai){
		aux				     			= d->fila[pai];
		d->fila[pai]				= d->fila[posAtual];
		d->fila[posAtual] 	= aux;

    //atualiza estatísticas
    d->stats.movimentou++;

		ajustarHeap(d, posAtual, posUltimo);
	}
}


static void ajustarFila(TFila *f, unsigned novoTamanho){
	TDadoFila *d = f->dado;
	size_t bytes = sizeof(void*) * novoTamanho;

	d->fila = realloc(d->fila, bytes);
	d->tamanho = novoTamanho;

	// Atualiza estatística
	d->stats.sobrecarregou++;
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
	TDadoFila *d = f->dado;
  int i=d->ocupacao, posAncestral;
	void *aux;

	if(i >= d->tamanho) ajustarFila(f, pow(2.0, floor(log2(i))+1));

  d->fila[i] = elemento;
  d->ocupacao++;

  posAncestral = PAI(i);
  while( (i > 0) && (COMPARAR_PRIORIDADES(d->fila[posAncestral],d->fila[i])) ){
    aux 				          =	d->fila[posAncestral];
    d->fila[posAncestral] = d->fila[i];
    d->fila[i]            = aux;

    //atualiza estatísticas
    d->stats.movimentou++;

    i = posAncestral;
		posAncestral = PAI(i);
  }


	// Atualiza estatística
	d->stats.inseriu++;

	return 1;
}


static short Vazia(TFila *f){
	return !(((TDadoFila*)f->dado)->ocupacao);
}


static void Analytics(TFila *f){
	TDadoFila *d = f->dado;
	printf("\n");
	printf(ANSI_COLOR_GREEN " inserções : " DIRETIVASTATS ANSI_COLOR_RESET, d->stats.inseriu);
	printf(ANSI_COLOR_RED " removeu   : " DIRETIVASTATS ANSI_COLOR_RESET, d->stats.removeu);
	printf(ANSI_COLOR_YELLOW " movimentou: " DIRETIVASTATS ANSI_COLOR_RESET, d->stats.movimentou);
	printf(ANSI_COLOR_CYAN " sobrecarga: " DIRETIVASTATS ANSI_COLOR_RESET, d->stats.sobrecarregou);
}


TDadoFila* criarDadoFila(){
	TDadoFila *d = malloc(sizeof(TDadoFila));
	d->fila = malloc(sizeof(void*)*TAM);
	d->tamanho = TAM;
	d->ocupacao=0;
	d->stats.inseriu = 0;
	d->stats.removeu = 0;
	d->stats.movimentou = 0;
	d->stats.sobrecarregou = 0;
}


TFila* criarFila(){
	TFila *f = malloc(sizeof(TFila));
	TDadoFila *d = criarDadoFila();

  f->dado = d;
	f->desenfileirar = Desenfileirar;
	f->enfileirar = Enfileirar;
	f->vazia = Vazia;
	f->analytics = Analytics;

	return f;
}

void destruirFila(TFila *f){
	free(((TDadoFila*)f->dado)->fila);
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

	Analytics(minhaFila);
  percorrer(minhaFila, imprimir);
}
*/
