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

  return minhaFila->desenfileirar(minhaFila);
  /*
	void* elemento=NULL;
	TDadoFila *d = f->dado;
	//printf("P:%d U:%d\n", d->primeiro, d->ultimo);
	if (d->primeiro == -1){
		elemento = NULL;
	}else{
		elemento  = d->fila[d->primeiro];
		if (d->primeiro == d->ultimo){
			d->primeiro = d->ultimo = -1;
		}else{
			int i;
			for(i=d->primeiro; i < d->ultimo; i++){
				d->fila[i] = d->fila[i+1];
			}
			d->ultimo--;
		}
		//atualiza estatísticas
		d->stats.removeu++;
		d->stats.movimentou += (d->ultimo-d->primeiro)+(d->primeiro==-1?0:1);
	}
	return elemento;
  */
}


static short Enfileirar(TFila *f, void *elemento){
	TDadoFila *d = f->dado;
  TTAD *minhaFila = d->fila;

  minhaFila->enfileirar(minhaFila, elemento);
	d->numElementos++;
  /*
	int posInsercao = d->ultimo+1, i;
	void *aux;

	if(d->primeiro == -1){
		d->primeiro = d->ultimo = 0;
		d->fila[d->primeiro] = elemento;
	}else{
		// se o vetor estiver cheio, então cria outro com o dobro do tamanho inicial.
		if(posInsercao >= d->tamanho) ajustarFila(f, posInsercao*2);

		d->ultimo = posInsercao;
		d->fila[posInsercao] = elemento;

		// trocar enquanto o anterior tiver prioridade menor que o último inserido.
		// Utilizar função de comparação de acordo com o tipo de elemento.
		for(i=posInsercao; (i > 0) && COMPARAR_PRIORIDADES(d->fila[i-1], d->fila[i]); i--){ //
			aux 				=	d->fila[i];
			d->fila[i] 	= d->fila[i-1];
			d->fila[i-1]= aux;
			d->stats.movimentou++;
		}
	}
  */
	// Atualiza estatística

	d->stats.movimentou = minhaFila->movimentacoes_enfileirar;
	d->stats.sobrecarregou = minhaFila->sobrecarga;
	d->stats.inseriu++;

	return 1;
}


static short Vazia(TFila *f){
	TDadoFila *d = f->dado;
	return (!d->numElementos);
}


static void Analytics(TFila *f){
	TDadoFila *d = f->dado;
	printf("\n");
	printf( " inserções : " DIRETIVASTATS , d->stats.inseriu);
	printf( " removeu   : " DIRETIVASTATS , d->stats.removeu);
	printf( " movimentou: " DIRETIVASTATS , d->stats.movimentou);
	printf( " sobrecarga: " DIRETIVASTATS , d->stats.sobrecarregou);
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

TFila* criarFila(){
	TFila *f = malloc(sizeof(TFila));
	TDadoFila *d = criarDadoFila();

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
