// filaD.c
// Created by Micael Levi on 07/03/2016
// Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved.

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#include "comparavel.h"
#include "fila.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NaN NULL
#define TAM 2

// prioridade de 'a' é menor que a de 'b'
#define COMPARAR_PRIORIDADES(a,b) (comparar((a), (b)) < 0)

typedef struct{
	unsigned inseriu;
	unsigned removeu;
	unsigned movimentou;
	unsigned sobrecarregou;
} TStatsFila;

typedef struct{
	void** fila;
	unsigned tamanho;

	int primeiro;
	int ultimo;
	TStatsFila stats;
} TDadoFila;



static void ajustarFila(TFila *f, unsigned novoTamanho){
	TDadoFila *d = f->dado;
	size_t bytes = sizeof(void*) * novoTamanho;
	void **novoVetor = malloc(bytes);
	memcpy(novoVetor, d->fila, bytes);

	free(d->fila);
	d->tamanho = novoTamanho;
	d->fila   = novoVetor;

	// Atualiza estatística
	d->stats.sobrecarregou++;
}


/** Remove o primeiro elemento da fila. Para a fila passada, o primeiro elemento será removido se ele existir.
 * No caso da fila vazia, a operação não é realizada e um NaN é retornado.
 *
 * Pré-cond: Fila criada.
 *
 * Pós-cond: Elemento removido, se fila não estiver vazia.
 */
static void* Desenfileirar(TFila *f){
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
}

/** Insere um novo elemento na fila. Para uma fila criada
 * a função irá inserir o elemento passado
 * considerando a ocupação da fila. o retorno indica se a
 * operação foi realizada com sucesso.
 *
 * Pré-cond: fila criada, e elemento a ser inserido.
 *
 * Pós-Cond: elemento inserido na fila, se houver espaço.
 */
static short Enfileirar(TFila *f, void *elemento){
	TDadoFila *d = f->dado;

	int posInsercao = d->ultimo+1, i;
	void* aux; // auxilia na troca de endereços.

	if(d->primeiro == -1){
		d->primeiro = d->ultimo = 0;
		d->fila[d->primeiro] = elemento;
	}else{
		// se o vetor estiver cheio, então cria outro com o dobro do tamanho inicial.
		if(posInsercao >= d->tamanho) ajustarFila(f, pow(2.0, floor(log2(posInsercao))+1));

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

	// Atualiza estatística
	d->stats.inseriu++;

	return 1;
}

/**Verifica a ocupação da fila. Para uma fila criada, verifica se ela tem UM elemento, pelo menos. Caso haja elementos o status retornado é de que a fila NÃO está vazia, caso contrário tem-se a indicação de fila vazia.
 *
 *Pré-cond: Fila criada.
 *
 *Pós-cond: Fila inalterada.
 */
static short Vazia(TFila *f){
	TDadoFila *d = f->dado;
	return (d->primeiro == -1);
}

/** Analisa e imprime estatísticas da fila. Para uma fila criada, imprime as estatísticas coletadas ao longo da execução do programa que usou a fila. São consideradas operações de inserção e remoção na fila e os custos de movimentação de elementos.
 *
 * Pré-cond: Fila criada
 *
 * Pós-cond: Estatísticas geradas e apresentadas.
 */
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
	d->fila = malloc(sizeof(void*)*TAM);
	d->tamanho = TAM;
	d->primeiro = d->ultimo = -1;
	// d->fila = calloc(TAM,sizeof(void*));


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
		int i=d->primeiro;
		for(; i <= d->ultimo; i++) acao(d->fila[i]);
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
	int i, nLinhas;

	scanf("%d",&nLinhas); // primeira linha

	for(i=0; i < nLinhas; i++){
		INTEIRO* aux = malloc(sizeof(INTEIRO));
		aux->compara = comparaINTEIROS;

		int *aux1 = malloc(sizeof(int));
		scanf("%d", aux1);

		aux->dado = aux1;
		minhaFila->enfileirar(minhaFila, aux);
	}

	Analytics(minhaFila);
	percorrer(minhaFila, imprimir);
}
*/
