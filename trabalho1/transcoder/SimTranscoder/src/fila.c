//
// fila.c
// Created by Micael Levi on 07/08/2016
// Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved.
//

#include "TADS/ordenacaoFila.h"

#include "fila.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TIPOSTATS unsigned long long
#define DIRETIVASTATS "%llu\n"

typedef struct{
	TIPOSTATS inseriu;
	TIPOSTATS removeu;
	TIPOSTATS movimentou;
	TIPOSTATS sobrecarregou;
} TStatsFila;

typedef struct{
  TTAD *fila;

	unsigned numElementos;
	TStatsFila stats;
} TDadoFila;


/* MÉTODOS */

static void* Desenfileirar(TFila *f){
  TDadoFila *d = f->dado;
  TTAD *minhaFila = d->fila;

  void* elementoRemovido = minhaFila->desenfileirar(minhaFila);

	if(elementoRemovido){
		// Atualiza remoções e número de elementos:
		d->stats.removeu++;
		d->numElementos--;
	}
	return elementoRemovido;
}


static short Enfileirar(TFila *f, void *elemento){
	TDadoFila *d = f->dado;
  TTAD *minhaFila = d->fila;

	d->numElementos += minhaFila->enfileirar(minhaFila, elemento);

	// Atualiza inserções:
	d->stats.inseriu++;

	return 1;
}


static short Vazia(TFila *f){
	TDadoFila *d = f->dado;
	return (!d->numElementos);
}


static void Analytics(TFila *f){
	TDadoFila *d = f->dado;
	TTAD *minhaFila = d->fila;

	// Atualiza estatísticas:
	d->stats.movimentou = minhaFila->movimentacoes_enfileirar;
	d->stats.movimentou += minhaFila->movimentacoes_desenfileirar;
	d->stats.sobrecarregou = minhaFila->sobrecarga;

	printf( "inserções : " DIRETIVASTATS , d->stats.inseriu);
	printf( "removeu   : " DIRETIVASTATS , d->stats.removeu);
	printf( "movimentou: " DIRETIVASTATS , d->stats.movimentou);
	printf( "sobrecarga: " DIRETIVASTATS , d->stats.sobrecarregou);
}

/*--------------------------------------------------------------*/

TDadoFila* criarDadoFila(){
	TDadoFila *d = malloc(sizeof(TDadoFila));

  d->fila = construirTAD();
  d->numElementos = 0;

	d->stats.inseriu = 0;
	d->stats.removeu = 0;
	d->stats.movimentou = 0;
	d->stats.sobrecarregou = 0;
}

TFila* construirFila(){
	TFila *f = malloc(sizeof(TFila));
	TDadoFila *d = criarDadoFila();
	if(!f || !d) return NULL;

	f->dado = d;
	f->desenfileirar= Desenfileirar;
	f->enfileirar 	= Enfileirar;
	f->vazia 				= Vazia;
	f->analytics 		= Analytics;

	return f;
}

void destruirFila(TFila *f){
  TDadoFila *d = f->dado;
  destruirTAD(d->fila);
	free(d);
	free(f);
}
